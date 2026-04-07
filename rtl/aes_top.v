module aes_top #(
    parameter [63:0] SBOX_IMPL  = "LUT",       // LUT, CANRIGHT. 
    parameter        KEY_BITS   = 128,         // 128, 192, 256.
    parameter        PIPE_DEPTH = 1,           // PIPELINED DESIGN NOT YET IMPLEMENTED.
    parameter [63:0] DUPLEX     = "HALF",      // HALF, FULL
    parameter [63:0] MODE       = "ECB"        // DIFFERENT MODES NOT YET IMPLEMENTED.
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
    output wire [127:0]        o_ciphertext,
    output wire                enc_done,

    // Decryption Lane
    input  wire                dec_start,
    input  wire [127:0]        i_ciphertext,
    output wire [127:0]        o_plain_text,
    output wire                dec_done
);

    generate
        if (PIPE_DEPTH == 1) begin : ARCH_ITERATIVE
            aes_core_iterative #(
                .SBOX_IMPL(SBOX_IMPL),
                .KEY_BITS(KEY_BITS),
                .DUPLEX(DUPLEX)
            ) u_core (
                .clk(clk), .rst_n(rst_n),
                .key_load(key_load), .key_in(key_in), .key_ready(key_ready),
                .enc_start(enc_start), .i_plaintext(i_plaintext), 
                .o_ciphertext(o_ciphertext), .enc_done(enc_done),
                .dec_start(dec_start), .i_ciphertext(i_ciphertext), 
                .o_plain_text(o_plain_text), .dec_done(dec_done)
            );
        end
        else begin : ARCH_PIPELINED
            // We will build this next!
            // aes_core_pipelined #(.KEY_BITS(KEY_BITS)) u_core (...)
        end
    endgenerate

endmodule
