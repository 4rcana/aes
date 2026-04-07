// ----------------------------------------------------------------
//              AES Iterative Core (Full/Half Duplex)
// ----------------------------------------------------------------
module aes_core_iterative #(
    parameter [63:0] SBOX_IMPL = "LUT",    // "LUT", "CANRIGHT"
    parameter        KEY_BITS  = 128,      // 128, 192, 256
    parameter [63:0] DUPLEX    = "FULL"    // "FULL" or "HALF"
)(
    input  wire                clk,
    input  wire                rst_n,
    
    // Key Interface
    input  wire                key_load,
    input  wire [KEY_BITS-1:0] key_in,
    output wire                key_ready,

    // Encryption Lane
    input  wire                enc_start,
    input  wire [127:0]        i_plaintext,
    output reg  [127:0]        o_ciphertext,
    output reg                 enc_done,

    // Decryption Lane
    input  wire                dec_start,
    input  wire [127:0]        i_ciphertext,
    output reg  [127:0]        o_plain_text,
    output reg                 dec_done
);

    localparam [3:0] Nk = 4'(KEY_BITS / 32);
    localparam [3:0] Nr = Nk + 4'd6;

    generate
        if (DUPLEX == "FULL") begin : ARCH_FULL
            reg  [3:0]   enc_round_num, dec_round_num;
            reg  [127:0] enc_state, dec_state;
            reg          enc_running, dec_running;
            
            wire [127:0] enc_round_key, dec_round_key;
            wire [127:0] enc_round_out, dec_round_out;

            // Unified Scheduler in FULL mode
            aes_key_scheduler #(
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL),
                .DUPLEX(DUPLEX)
            ) u_ksi (
                .clk(clk),
                .rst_n(rst_n),
                .key_load(key_load),
                .key_in(key_in),
                .key_ready(key_ready),
                // Port A: Mapped to Encryption
                .round_num_a(enc_round_num), 
                .mode_a(1'b0),              // 0: FORWARD
                .key_out_a(enc_round_key),
                // Port B: Mapped to Decryption
                .round_num_b(dec_round_num), 
                .key_out_b(dec_round_key)
            );

            // Forward Round
            aes_round_generic #(
                .DIRECTION("FORWARD"),
                .KEY_BITS(KEY_BITS),
                .SBOX_IMPL(SBOX_IMPL)
            ) u_ernd (
                .round_num(enc_round_num), 
                .in(enc_state),
                .round_key(enc_round_key),
                .mode(1'b0),
                .out(enc_round_out)
            );

            // Inverse Round
            aes_round_generic #(
                .DIRECTION("INVERSE"),
                .KEY_BITS(KEY_BITS),
                .SBOX_IMPL(SBOX_IMPL)
            ) u_drnd (
                .round_num(dec_round_num),
                .in(dec_state),
                .round_key(dec_round_key),
                .mode(1'b1),
                .out(dec_round_out)
            );

            // Encryption FSM
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    enc_round_num <= 4'd0;
                    enc_running   <= 1'b0;
                    enc_done      <= 1'b0;
                    o_ciphertext  <= 128'h0;
                end else if (enc_start && key_ready && !enc_running) begin
                    enc_state     <= i_plaintext ^ enc_round_key;
                    enc_round_num <= 4'd1;
                    enc_running   <= 1'b1;
                    enc_done      <= 1'b0;
                end else if (enc_running) begin
                    enc_state <= enc_round_out;
                    if (enc_round_num == Nr) begin
                        o_ciphertext  <= enc_round_out;
                        enc_done      <= 1'b1;
                        enc_running   <= 1'b0;
                        enc_round_num <= 4'd0;
                    end else enc_round_num <= enc_round_num + 4'd1;
                end else enc_done <= 1'b0;
            end

            // Decryption FSM
            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    dec_round_num <= 4'd0;
                    dec_running   <= 1'b0;
                    dec_done      <= 1'b0;
                    o_plain_text  <= 128'h0;
                end else if (dec_start && key_ready && !dec_running) begin
                    dec_state     <= i_ciphertext ^ dec_round_key;
                    dec_round_num <= 4'd1;
                    dec_running   <= 1'b1;
                    dec_done      <= 1'b0;
                end else if (dec_running) begin
                    dec_state <= dec_round_out;
                    if (dec_round_num == Nr) begin
                        o_plain_text  <= dec_round_out;
                        dec_done      <= 1'b1;
                        dec_running   <= 1'b0;
                        dec_round_num <= 4'd0;
                    end else dec_round_num <= dec_round_num + 4'd1;
                end else dec_done <= 1'b0;
            end
        end

        else begin : ARCH_HALF
            reg [3:0]   round_num;
            reg [127:0] state;
            reg         busy;
            reg         mode_reg; 
            
            // Key Scheduler and FSM needs to know mode without delay
            wire current_op_mode = busy ? mode_reg : dec_start;

            wire [127:0] round_key;
            wire [127:0] round_out;

            // Key Scheduler
            aes_key_scheduler #(
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL),
                .DUPLEX(DUPLEX)
            ) u_ksi (
                .clk(clk), .rst_n(rst_n),
                .key_load(key_load), .key_in(key_in), .key_ready(key_ready),
                .round_num_a(round_num), .mode_a(current_op_mode),
                .key_out_a(round_key),
                // Unused
                .round_num_b(4'd0), .key_out_b()
            );

            // Round Logic (Round logic happens in cycles AFTER start, so mode_reg is fine)
            aes_round_generic #(
                .DIRECTION("SHARED"), 
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL)
            ) u_shared_rnd (
                .round_num(round_num), 
                .in(state),
                .round_key(round_key), 
                .mode(mode_reg),
                .out(round_out)
            );

            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    round_num    <= 0;
                    busy         <= 0;
                    mode_reg     <= 0;
                    enc_done     <= 0;
                    dec_done     <= 0;
                    o_ciphertext <= 0;
                    o_plain_text <= 0;
                end 
                else if ((enc_start || dec_start) && key_ready && !busy) begin
                    busy      <= 1'b1;
                    mode_reg  <= dec_start; 
                    state     <= (current_op_mode ? i_ciphertext : i_plaintext) ^ round_key;
                    round_num <= 4'd1;
                    enc_done  <= 1'b0; 
                    dec_done  <= 1'b0;
                end 
                else if (busy) begin
                    state <= round_out;
                    if (round_num == Nr) begin
                        if (mode_reg) begin
                            o_plain_text <= round_out;
                            dec_done     <= 1'b1;
                        end
                        else begin
                            o_ciphertext <= round_out;
                            enc_done <= 1'b1;
                        end
                        busy      <= 0; 
                        round_num <= 0;
                    end else begin
                        round_num <= round_num + 4'd1;
                    end
                end else begin
                    enc_done <= 1'b0;
                    dec_done <= 1'b0;
                end
            end
        end
    endgenerate

endmodule
