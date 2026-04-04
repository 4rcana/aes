module aes_enc_round #(
    parameter KEY_BITS  = 128,    // 128, 192, or 256
    parameter SBOX_IMPL = "LUT"
)(
    input  wire [3:0]   round_num,
    input  wire [127:0] state_in,
    input  wire [127:0] round_key,
    output wire [127:0] state_out
);

    localparam [3:0] Nr = 4'((KEY_BITS / 32) + 6);    // 10 / 12 / 14

    wire last_round = (round_num == Nr);

    wire [127:0] after_sub;
    wire [127:0] after_shift;
    wire [127:0] after_mix;

    // Purely combinational datapath
    sub_bytes_generic # (.SBOX_IMPL(SBOX_IMPL), .DIRECTION("FORWARD"))
                u_sub   (.in(state_in), .mode(1'b0), .out(after_sub));
    shift_rows  u_shift (.in(after_sub),    .out(after_shift));
    mix_columns u_mix   (.in(after_shift),  .out(after_mix));

    // Add round key, last round skips MixColumns
    assign state_out = (last_round ? after_shift : after_mix) ^ round_key;

endmodule

// ------------------------------------------------------------------------
//                          Inverse Round
// ------------------------------------------------------------------------

module aes_dec_round #(
    parameter KEY_BITS  = 128,    // 128, 192, or 256
    parameter SBOX_IMPL = "LUT"
)(
    input  wire [3:0]   round_num,
    input  wire [127:0] state_in,
    input  wire [127:0] round_key,
    output wire [127:0] state_out
);

    localparam [3:0] Nr = 4'((KEY_BITS / 32) + 6);    // 10 / 12 / 14

    wire last_round = (round_num == Nr);

    wire [127:0] after_inv_sub;
    wire [127:0] after_inv_shift;
    wire [127:0] after_inv_mix;

    // Purely combinational datapath
    sub_bytes_generic # (.SBOX_IMPL(SBOX_IMPL), .DIRECTION("INVERSE")) 
                    u_inv_sub   (.in(state_in), .mode(1'b1), .out (after_inv_sub));
    inv_shift_rows  u_inv_shift (.in(after_inv_sub),   .out(after_inv_shift));
    inv_mix_columns u_inv_mix   (.in(after_inv_shift), .out(after_inv_mix));

    // Add transformed round key, last round skips MixColumns
    assign state_out = (last_round ? after_inv_shift : after_inv_mix) ^ round_key;

endmodule
