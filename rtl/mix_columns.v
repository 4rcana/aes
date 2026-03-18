module mix_columns (
    input  wire [127:0] in,
    output wire [127:0] out
);

    genvar c;
    generate
        for (c = 0; c < 4; c = c + 1) begin : mc_col
            mix_single_col u_col (
                .in  (in  [127 - c*32 -: 32]),
                .out (out [127 - c*32 -: 32])
            );
        end
    endgenerate

endmodule

module mix_single_col (
    input  wire [31:0] in,
    output wire [31:0] out
);

    wire [7:0] s0 = in[31:24], s1 = in[23:16],
               s2 = in[15:8],  s3 = in[7:0];

    // xtime = multiply by 2 in GF(2^8)
    function [7:0] xtime;
        input [7:0] b;
        xtime = (b[7] ? (b << 1) ^ 8'h1b : b << 1);
    endfunction

    // MixColumns matrix: [2,3,1,1 / 1,2,3,1 / 1,1,2,3 / 3,1,1,2]
    assign out[31:24] = xtime(s0) ^ (xtime(s1) ^ s1) ^ s2 ^ s3;
    assign out[23:16] = s0 ^ xtime(s1) ^ (xtime(s2) ^ s2) ^ s3;
    assign out[15:8]  = s0 ^ s1 ^ xtime(s2) ^ (xtime(s3) ^ s3);
    assign out[7:0]   = (xtime(s0) ^ s0) ^ s1 ^ s2 ^ xtime(s3);

endmodule
