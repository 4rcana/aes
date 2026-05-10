import crypto_pkg::*;

// ----------------------------------------------------------------
//                  AES Unified Key Scheduler
// ----------------------------------------------------------------
// Supports AES-128, 192, and 256. 
// DUPLEX="FULL": 8 internal banks (Independent Enc/Dec lanes).
// DUPLEX="HALF": 4 internal banks (Shared lanes).
// ----------------------------------------------------------------
module aes_key_scheduler_iterative #(
    parameter integer                 KEY_BITS  = 128,
    parameter crypto_pkg::sbox_arch_t SBOX_ARCH = SBOX_LUT,
    parameter crypto_pkg::duplex_t    DUPLEX    = DUPLEX_FULL
)(
    input  wire                 clk,
    input  wire                 rst_n,

    // Key Interface
    input  wire                 key_load,
    input  wire [KEY_BITS-1:0]  key_in,
    output reg                  key_ready,

    // Lane A: Encryption (Full) or Shared (Half)
    input  wire [3:0]           round_num_a,
    input  wire                 mode_a,       // 0:FORWARD, 1:INVERSE
    output wire [127:0]         key_out_a,

    // Lane B: Decryption (Used only if DUPLEX == "FULL")
    input  wire [3:0]           round_num_b,
    output wire [127:0]         key_out_b
);

    localparam [3:0] Nk      = 4'(KEY_BITS / 32);
    localparam [3:0] Nr      = Nk + 4'd6;
    localparam [5:0] TOTAL_W = ({2'b00, Nr} + 6'd1) << 2;
    localparam [5:0] LAST_W  = TOTAL_W - 6'd1;

    // ---------------------------------------------------------------
    // 1. Expansion Logic (Shared for all modes)
    // ---------------------------------------------------------------
    reg [5:0]  idx;
    reg        expanding;
    reg [31:0] history [0:7];
    reg [31:0] new_word; 

    // Moving window wires
    wire [31:0] w_prev     = history[0];
    wire [31:0] w_nk       = (KEY_BITS == 128) ? history[3] :
                             (KEY_BITS == 192) ? history[5] : history[7];
    wire [31:0] w_prev_rot = { w_prev[23:0], w_prev[31:24] };

    // Unified Source: Initial key bits from bus, subsequent bits from expansion XORs
    wire [31:0] key_in_slice     = key_in[KEY_BITS-1 - idx*32 -: 32];
    wire [31:0] current_raw_word = (idx < {2'b00, Nk}) ? key_in_slice : new_word;

    // SubWord Generic Instance (Always FORWARD for expansion)
    reg  [31:0] sw_in;
    wire [31:0] sw_out;

    sub_generic #(
        .SBOX_ARCH(SBOX_ARCH),
        .DIRECTION(DIR_FORWARD),
        .WIDTH(32'd32)
    ) u_sw (
        .in(sw_in),
        .mode(1'b0),
        .out(sw_out)
    );

    // Boundary & Rcon Selection (Logic-based to avoid Modulo/Division)
    wire is_boundary;
    wire is_midpoint;
    reg  [3:0] rcon_idx;

    generate
        if (KEY_BITS == 128) begin : GEN_128_LOGIC
            assign is_boundary = (idx[1:0] == 2'b00); 
            assign is_midpoint = 1'b0;
            always @(*) rcon_idx = idx[5:2];
        end 
        else if (KEY_BITS == 256) begin : GEN_256_LOGIC
            assign is_boundary = (idx[2:0] == 3'b000);
            assign is_midpoint = (idx[2:0] == 3'b100);
            always @(*) rcon_idx = { 1'b0, idx[5:3] };
        end
        else begin : GEN_192_LOGIC
            assign is_boundary = (idx == 6'd0  || idx == 6'd6  || idx == 6'd12 || 
                                  idx == 6'd18 || idx == 6'd24 || idx == 6'd30 || 
                                  idx == 6'd36 || idx == 6'd42 || idx == 6'd48);
            assign is_midpoint = 1'b0;
            always @(*) begin
                if      (idx < 6'd6)  rcon_idx = 4'd0; else if (idx < 6'd12) rcon_idx = 4'd1;
                else if (idx < 6'd18) rcon_idx = 4'd2; else if (idx < 6'd24) rcon_idx = 4'd3;
                else if (idx < 6'd30) rcon_idx = 4'd4; else if (idx < 6'd36) rcon_idx = 4'd5;
                else if (idx < 6'd42) rcon_idx = 4'd6; else if (idx < 6'd48) rcon_idx = 4'd7;
                else                  rcon_idx = 4'd8;
            end
        end
    endgenerate

    always @(*) begin
        sw_in = is_boundary ? w_prev_rot : w_prev;
        if (is_boundary)      new_word = w_nk ^ sw_out ^ rcon(rcon_idx);
        else if (is_midpoint) new_word = w_nk ^ sw_out;
        else                  new_word = w_nk ^ w_prev;
    end

    // ---------------------------------------------------------------
    // 2. Storage Banks (Banked for Port Efficiency)
    // ---------------------------------------------------------------
    wire [31:0] out_a [0:3];
    wire [31:0] out_b [0:3];

    // Address translation: Reverse index if in Inverse mode
    wire [3:0] addr_r_a = (DUPLEX == DUPLEX_HALF && mode_a) ? (Nr - round_num_a) : round_num_a;
    wire [3:0] addr_r_b = (Nr - round_num_b);

    genvar k;
    generate
        for (k=0; k<4; k=k+1) begin : gen_banks
            // Set A (Mandatory)
            lutram_32x16 bank_a (
                .clk(clk), .we(expanding && (idx[1:0] == 2'(k))),
                .addr_w(idx[5:2]), .data_in(current_raw_word),
                .addr_r(addr_r_a), .data_out(out_a[k])
            );

            if (DUPLEX == DUPLEX_FULL) begin : ARCH_FULL
                // Set B (Shadow copy to resolve Full-Duplex port conflict)
                lutram_32x16 bank_b (
                    .clk(clk), .we(expanding && (idx[1:0] == 2'(k))),
                    .addr_w(idx[5:2]), .data_in(current_raw_word),
                    .addr_r(addr_r_b), .data_out(out_b[k])
                );
            end else begin : ARCH_HALF
                assign out_b[k] = 32'h0;
            end
        end
    endgenerate

    // ---------------------------------------------------------------
    // 3. Decryption Transformation (Equivalent Inverse Cipher)
    // ---------------------------------------------------------------
    wire [127:0] raw_a = {out_a[0], out_a[1], out_a[2], out_a[3]};
    wire [127:0] raw_b = {out_b[0], out_b[1], out_b[2], out_b[3]};
    wire [127:0] mixed_a, mixed_b;

    mix_columns_generic #(.DIRECTION(DIR_INVERSE))
    u_mcg_a (.in(raw_a), .mode(1'b1), .out(mixed_a));
    mix_columns_generic #(.DIRECTION(DIR_INVERSE))
    u_mcg_b (.in(raw_b), .mode(1'b1), .out(mixed_b));

    // Intermediate keys (1 to Nr-1) are transformed for Decryption
    wire a_needs_inv = (DUPLEX == DUPLEX_HALF) ? (mode_a && round_num_a > 4'd0 && round_num_a < Nr) : 1'b0;
    wire b_needs_inv = (round_num_b > 4'd0 && round_num_b < Nr);

    assign key_out_a = a_needs_inv ? mixed_a : raw_a;
    assign key_out_b = b_needs_inv ? mixed_b : raw_b;

    // ---------------------------------------------------------------
    // 4. Sequential Control
    // ---------------------------------------------------------------
    integer h;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            idx       <= 6'b0;
            expanding <= 1'b0;
            key_ready <= 1'b0;
            for(h=0; h<8; h=h+1)
                history[h] <= 32'h0;
        end else if (key_load) begin
            idx       <= 6'b0;
            expanding <= 1'b1;
            key_ready <= 1'b0;
        end else if (expanding) begin
            // Shift history window
            history[0] <= current_raw_word;
            history[1] <= history[0];
            history[2] <= history[1];
            history[3] <= history[2];
            history[4] <= history[3];
            history[5] <= history[4];
            history[6] <= history[5];
            history[7] <= history[6];

            if (idx == LAST_W) begin
                expanding <= 1'b0;
                key_ready <= 1'b1;
                idx       <= 6'b0;
            end else begin
                idx <= idx + 6'd1;
            end
        end
    end

    function [31:0] rcon(input [3:0] i);
        reg [7:0] rc;
        begin
            case (i)
                4'd1:rc=8'h01; 4'd2:rc=8'h02; 4'd3:rc=8'h04; 4'd4:rc=8'h08;
                4'd5:rc=8'h10; 4'd6:rc=8'h20; 4'd7:rc=8'h40; 4'd8:rc=8'h80;
                4'd9:rc=8'h1b; 4'd10:rc=8'h36; default:rc=8'h00;
            endcase
            rcon = { rc, 24'h000000 };
        end
    endfunction
endmodule

// ----------------------------------------------------------------
// Standard Simple Dual-Port LUTRAM (1 Write, 1 Read)
// ----------------------------------------------------------------
module lutram_32x16 (
    input  wire        clk,
    input  wire        we,
    input  wire [3:0]  addr_w,
    input  wire [31:0] data_in,
    input  wire [3:0]  addr_r,
    output wire [31:0] data_out
);
    (* ram_style = "distributed" *) reg [31:0] mem [0:15];
    always @(posedge clk) if (we) mem[addr_w] <= data_in;
    assign data_out = mem[addr_r];
endmodule
