module aes_round (
    parameter KEY_BITS = 128    // 128, 192, or 256
)(
    input  wire         clk,
    input  wire         rst_n,
    input  wire [3:0]   round_cnt,
    input  wire [127:0] state_in,
    input  wire [127:0] round_key,
    output reg  [127:0] state_out
);

    localparam Nr = (KEY_BITS / 32) + 6;    // 10 / 12 / 14

    wire last_round = (round_cnt == Nr);

    wire [127:0] after_sub;
    wire [127:0] after_shift;
    wire [127:0] after_mix;
    wire [127:0] after_ark;

    // purely combinational datapath
    sub_bytes   u_sub   (.in(state_in),    .out(after_sub));
    shift_rows  u_shift (.in(after_sub),   .out(after_shift));
    mix_columns u_mix   (.in(after_shift), .out(after_mix));

    // last round skips MixColumns
    assign after_ark = (last_round ? after_shift : after_mix) ^ round_key;

    // register at the output — one cycle per round
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) state_out <= 128'b0;
        else        state_out <= after_ark;
    end

endmodule
