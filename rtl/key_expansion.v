module key_expansion #(
    parameter WORDS_IN_KEY = 8
)(
    input   wire                    clk,
    input   wire                    rst_n,
    input   wire                    start,
    input   wire    [KEY_SIZE-1:0]  secret_key,
    output  reg     [127:0]         round_key,
    output  reg                     valid
);



endmodule
