module aes_top #(
    parameter KEY_SIZE = 256;
    parameter PIPE_DEPTH = 1 // 1 <= PIPE_DEPTH <= NR 
)(
    input   wire                    clk,
    input   wire                    rst_n,
    input   wire    [KEY_SIZE-1:0]  secret_key,
    input   wire    [DATA_SIZE-1:0] data_in,
    output  wire    [DATA_SIZE-1:0] data_out
);

localparam ROUNDS = (KEY_SIZE==128) ? 10 : (KEY_SIZE==192) ? 12 : 14;
localparam WORDS_IN_KEY = KEY_SIZE/32;

    key_expansion #(
        .WORDS_IN_KEY(WORDS_IN_KEY)
    ) keygen (
        .clk(clk),
        .rst_n(rst_n),
        .start(start),
        .secret_key(secret_key),
        .round_key(round_key),
        .valid(valid)
    )

endmodule
