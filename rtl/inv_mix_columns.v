module inv_mix_columns (
    input  wire [127:0] in,
    output wire [127:0] out
);

    genvar c;
    generate
        for (c = 0; c < 4; c = c + 1) begin : imc_col
            inv_mix_single_col u_col (
                .in  (in  [127 - c*32 -: 32]),
                .out (out [127 - c*32 -: 32])
            );
        end
    endgenerate

endmodule

module inv_mix_single_col (
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

    function [7:0] mul_e; // Multiply by 0e (14) = 8 + 4 + 2
        input [7:0] b;
        reg [7:0] x2, x4, x8;
        begin
            x2 = xtime(b);
            x4 = xtime(x2);
            x8 = xtime(x4);
            mul_e = x8 ^ x4 ^ x2;
        end
    endfunction

    function [7:0] mul_b; // Multiply by 0b (11) = 8 + 2 + 1
        input [7:0] b;
        reg [7:0] x2, x4, x8;
        begin
            x2 = xtime(b);
            x4 = xtime(x2);
            x8 = xtime(x4);
            mul_b = x8 ^ x2 ^ b;
        end
    endfunction

    function [7:0] mul_d; // Multiply by 0d (13) = 8 + 4 + 1
        input [7:0] b;
        reg [7:0] x2, x4, x8;
        begin
            x2 = xtime(b);
            x4 = xtime(x2);
            x8 = xtime(x4);
            mul_d = x8 ^ x4 ^ b;
        end
    endfunction

    function [7:0] mul_9; // Multiply by 09 (9) = 8 + 1
        input [7:0] b;
        reg [7:0] x2, x4, x8;
        begin
            x2 = xtime(b);
            x4 = xtime(x2);
            x8 = xtime(x4);
            mul_9 = x8 ^ b;
        end
    endfunction

    // Inverse MixColumns matrix: [0e, 0b, 0d, 09 / 09, 0e, 0b, 0d /
    //                             0d, 09, 0e, 0b / 0b, 0d, 09, 0e ]
    assign out[31:24] = mul_e(s0) ^ mul_b(s1) ^ mul_d(s2) ^ mul_9(s3);
    assign out[23:16] = mul_9(s0) ^ mul_e(s1) ^ mul_b(s2) ^ mul_d(s3);
    assign out[15:8]  = mul_d(s0) ^ mul_9(s1) ^ mul_e(s2) ^ mul_b(s3);
    assign out[7:0]   = mul_b(s0) ^ mul_d(s1) ^ mul_9(s2) ^ mul_e(s3);

endmodule
