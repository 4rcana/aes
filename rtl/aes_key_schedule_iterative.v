module aes_key_schedule_iterative #(
    parameter KEY_BITS = 128
)(
    input  wire                  clk,
    input  wire                  rst_n,
    input  wire                  load,
    input  wire [KEY_BITS-1:0]   key_in,
    input  wire [3:0]            enc_round_num,
    input  wire [3:0]            dec_round_num,
    output wire [127:0]          enc_round_key,
    output wire [127:0]          dec_round_key,
    output reg                   key_ready
);

localparam [3:0] Nk      = 4'(KEY_BITS / 32);
localparam [3:0] Nr      = Nk + 6;
localparam [5:0] TOTAL_W = ({2'b00, Nr} + 1) * 4;

// ---------------------------------------------------------------
// Rcon — function is fine here, pure LUT with no module deps
// ---------------------------------------------------------------
function [31:0] rcon;
    input [3:0] i;
    reg [7:0] rc;
    begin
        case (i)
            4'd1: rc=8'h01; 4'd2: rc=8'h02; 4'd3: rc=8'h04;
            4'd4: rc=8'h08; 4'd5: rc=8'h10; 4'd6: rc=8'h20;
            4'd7: rc=8'h40; 4'd8: rc=8'h80; 4'd9: rc=8'h1b;
            4'd10:rc=8'h36;
            default: rc=8'h00;
        endcase
        rcon = { rc, 24'h000000 };
    end
endfunction

// ---------------------------------------------------------------
// Word storage
// ---------------------------------------------------------------
reg [31:0]  w_enc      [0:TOTAL_W-1];
reg [31:0]  w_dec      [0:TOTAL_W-1];
reg [5:0]   word_idx;
reg         expanding;

// ---------------------------------------------------------------
// Input Selection 
// ---------------------------------------------------------------
// For word_idx < Nk, we use the input key directly.
// For word_idx >= Nk, we use the generated 'new_word'.
wire [31:0] key_in_slice = key_in[KEY_BITS-1 - word_idx*32 -: 32];
wire [31:0] current_raw_word = (word_idx < {2'b00, Nk}) ? key_in_slice : new_word;

// ---------------------------------------------------------------
// sub_word instance — single shared instance, driven by sw_in
// ---------------------------------------------------------------
reg  [31:0] sw_in;
wire [31:0] sw_out;

sub_word u_sw (
    .word_in  (sw_in),
    .word_out (sw_out)
);

// ---------------------------------------------------------------
// Combinational logic 
//
// Three cases, driven by word_idx position within the Nk group:
//   idx % Nk == 0  →  RotWord → SubWord → XOR Rcon → XOR w_nk
//   idx % Nk == 4  →  SubWord only → XOR w_nk        (AES-256 only)
//   otherwise      →  w_prev XOR w_nk, S-Box unused
//
// rot_word is a wire — no logic, just byte reorder of w[word_idx-1]
// ---------------------------------------------------------------
wire [31:0] w_prev     = expanding ? w_enc[word_idx - 1]  : 32'h0;
wire [31:0] w_nk       = expanding ? w_enc[word_idx - {2'b00, Nk}] : 32'h0;
wire [31:0] w_prev_rot = { w_prev[23:0], w_prev[31:24] };

// These two signals select which branch we're on
wire        is_nk_boundary = (word_idx % {2'b00, Nk} == 0);
wire        is_nk_midpoint = (KEY_BITS == 256) && (word_idx % {2'b00, Nk} == 4);

reg  [31:0] new_word;

always @(*) begin
    // Drive the S-Box input:
    //   boundary → feed rotated word (RotWord before SubWord)
    //   midpoint → feed w_prev directly (SubWord only)
    //   other    → don't care, new_word won't use sw_out
    if (is_nk_boundary)
        sw_in = w_prev_rot;
    else
        sw_in = w_prev;  // covers midpoint and don't-care cases

    // Compute new_word from the appropriate branch
    if (is_nk_boundary)
        new_word = w_nk ^ sw_out ^ rcon(4'(word_idx / Nk));
    else if (is_nk_midpoint)
        new_word = w_nk ^ sw_out;
    else
        new_word = w_nk ^ w_prev;
end

// ---------------------------------------------------------------
// inv_mix_single_col instance — single shared instance, driven by new_word
// ---------------------------------------------------------------
wire [31:0] transformed_word;

inv_mix_single_col u_inv_msc (
    .in(current_raw_word),
    .out(transformed_word)
);

// Equivalent Inverse Cipher Rule:
// Round 0 (words 0-3) and Round Nr (last 4 words) stay RAW.
// Intermediate rounds (words 4 to Nr*4 - 1) are TRANSFORMED.
wire is_first_key = (word_idx < 6'd4);
wire is_last_key  = (word_idx >= ({2'b00, Nr} << 2));
wire is_raw_zone  = is_first_key || is_last_key;

// ---------------------------------------------------------------
// Sequential logic — one word generated per clock cycle
// ---------------------------------------------------------------
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        word_idx  <= 0;
        expanding <= 0;
        key_ready <= 0;
    end
    else if (load) begin
        word_idx    <= 0;
        expanding   <= 1;
        key_ready   <= 0;
    end
    else if (expanding) begin
        w_enc[word_idx] <= current_raw_word;
        w_dec[word_idx] <= is_raw_zone ? current_raw_word : transformed_word;

        if (word_idx == TOTAL_W - 1) begin
            expanding <= 0;
            key_ready <= 1;
        end else
            word_idx <= word_idx + 1;
    end
end

// multiply by 4 = left shift by 2, no multiplier inferred
wire [5:0] enc_rk_base = { enc_round_num, 2'b00 };
// round key order should be reversed for decryption
wire [5:0] dec_rk_base = { Nr - dec_round_num, 2'b00 };

assign enc_round_key = { w_enc[enc_rk_base],   w_enc[enc_rk_base+1],
                         w_enc[enc_rk_base+2], w_enc[enc_rk_base+3] };

assign dec_round_key = { w_dec[dec_rk_base],   w_dec[dec_rk_base+1],
                         w_dec[dec_rk_base+2], w_dec[dec_rk_base+3] };

endmodule
