module aes_round #(
    parameter KEY_BITS = 128    // 128, 192, or 256
)(
    input  wire         clk,
    input  wire         rst_n,
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

    // purely combinational datapath
    sub_bytes   u_sub   (.in(state_in),    .out(after_sub));
    shift_rows  u_shift (.in(after_sub),   .out(after_shift));
    mix_columns u_mix   (.in(after_shift), .out(after_mix));

    // Add round key, last round skips MixColumns
    assign state_out = (last_round ? after_shift : after_mix) ^ round_key;

endmodule
