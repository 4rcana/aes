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

    // Galois Field Multiplications
    function [7:0] mul(input [7:0] b, input [3:0] factor);
        reg [7:0] x2;
        begin
            x2 = xtime(b);
            case(factor)
                4'h2: mul = x2;               // 0010
                4'h3: mul = x2 ^ b;           // 0011
                default: mul = b;
            endcase
        end
    endfunction

    // MixColumns matrix: [2,3,1,1 / 1,2,3,1 / 1,1,2,3 / 3,1,1,2]
    assign out[31:24] = mul(s0, 4'h2) ^ mul(s1, 4'h3) ^ s2 ^ s3;
    assign out[23:16] = s0 ^ mul(s1, 4'h2) ^ mul(s2, 4'h3) ^ s3;
    assign out[15:8]  = s0 ^ s1 ^ mul(s2, 4'h2) ^ mul(s3, 4'h3);
    assign out[7:0]   = mul(s0, 4'h3) ^ s1 ^ s2 ^ mul(s3, 4'h2);

endmodule

// --------------------------------------------------------------
//                          Inverse Mix
// --------------------------------------------------------------

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

    // Galois Field Multiplications
    function [7:0] mul(input [7:0] b, input [3:0] factor);
        reg [7:0] x2, x4, x8;
        begin
            x2 = xtime(b);
            x4 = xtime(x2);
            x8 = xtime(x4);
            case(factor)
                4'h9: mul = x8 ^ b;               // 1001
                4'hb: mul = x8 ^ x2 ^ b;          // 1011
                4'hd: mul = x8 ^ x4 ^ b;          // 1101
                4'he: mul = x8 ^ x4 ^ x2;         // 1110
                default: mul = b;
            endcase
        end
    endfunction

    // Inverse MixColumns matrix: [0e, 0b, 0d, 09 / 09, 0e, 0b, 0d /
    //                             0d, 09, 0e, 0b / 0b, 0d, 09, 0e ]
    assign out[31:24] = mul(s0, 4'he) ^ mul(s1, 4'hb) ^ mul(s2, 4'hd) ^ mul(s3, 4'h9);
    assign out[23:16] = mul(s0, 4'h9) ^ mul(s1, 4'he) ^ mul(s2, 4'hb) ^ mul(s3, 4'hd);
    assign out[15:8]  = mul(s0, 4'hd) ^ mul(s1, 4'h9) ^ mul(s2, 4'he) ^ mul(s3, 4'hb);
    assign out[7:0]   = mul(s0, 4'hb) ^ mul(s1, 4'hd) ^ mul(s2, 4'h9) ^ mul(s3, 4'he);

endmodule
