module sub_word (
    input  wire [31:0] word_in,
    output wire [31:0] word_out
);

    sbox u0 (.byte_in(word_in[31:24]), .byte_out(word_out[31:24]));
    sbox u1 (.byte_in(word_in[23:16]), .byte_out(word_out[23:16]));
    sbox u2 (.byte_in(word_in[15:8]),  .byte_out(word_out[15:8]));
    sbox u3 (.byte_in(word_in[7:0]),   .byte_out(word_out[7:0]));

endmodule
