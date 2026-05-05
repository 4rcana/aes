import crypto_pkg::*;

// ----------------------------------------------------------------
//                      Generic MixColumns Hub
// ----------------------------------------------------------------
module mix_columns_generic #(
    parameter crypto_pkg::round_dir_t DIRECTION = DIR_FORWARD
)(
    input  wire [127:0] in,
    input  wire         mode,              // 0:FORWARD, 1:INVERSE
    output wire [127:0] out
);
    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : col_loop
            mix_single_col_generic #(.DIRECTION(DIRECTION)) u_col (
                .in  (in [127 - i*32 -: 32]),
                .mode(mode),
                .out (out[127 - i*32 -: 32])
            );
        end
    endgenerate
endmodule

// ----------------------------------------------------------------
//                  Generic Single Column Logic
// ----------------------------------------------------------------
module mix_single_col_generic #(
    parameter crypto_pkg::round_dir_t DIRECTION = DIR_FORWARD
)(
    input  wire [31:0] in,
    input  wire        mode,
    output wire [31:0] out
);

    wire _unused = &{1'b0, mode, 1'b0};

    wire [7:0] s0 = in[31:24], s1 = in[23:16], s2 = in[15:8], s3 = in[7:0];

    function [7:0] xtime(input [7:0] b);
        xtime = (b[7] ? (b << 1) ^ 8'h1b : b << 1);
    endfunction

    generate
        // --- 1. SPECIALIZED FORWARD (Encryption Lane) ---
        if (DIRECTION == DIR_FORWARD) begin : GEN_FORWARD
            assign out[31:24] = xtime(s0) ^ (xtime(s1) ^ s1) ^ s2 ^ s3;
            assign out[23:16] = s0 ^ xtime(s1) ^ (xtime(s2) ^ s2) ^ s3;
            assign out[15:8]  = s0 ^ s1 ^ xtime(s2) ^ (xtime(s3) ^ s3);
            assign out[7:0]   = (xtime(s0) ^ s0) ^ s1 ^ s2 ^ xtime(s3);
        end

        // --- 2. SPECIALIZED INVERSE (Decryption Lane) ---
        else if (DIRECTION == DIR_INVERSE) begin : GEN_INVERSE
            // Helper for 0e, 0b, 0d, 09
            function [7:0] mul(input [7:0] b, input [3:0] f);
                reg [7:0] x2, x4, x8;
                begin
                    x2 = xtime(b); x4 = xtime(x2); x8 = xtime(x4);
                    case(f)
                        4'h9: mul = x8 ^ b;
                        4'hb: mul = x8 ^ x2 ^ b;
                        4'hd: mul = x8 ^ x4 ^ b;
                        4'he: mul = x8 ^ x4 ^ x2;
                        default: mul = b;
                    endcase
                end
            endfunction

            assign out[31:24] = mul(s0,4'he) ^ mul(s1,4'hb) ^ mul(s2,4'hd) ^ mul(s3,4'h9);
            assign out[23:16] = mul(s0,4'h9) ^ mul(s1,4'he) ^ mul(s2,4'hb) ^ mul(s3,4'hd);
            assign out[15:8]  = mul(s0,4'hd) ^ mul(s1,4'h9) ^ mul(s2,4'he) ^ mul(s3,4'hb);
            assign out[7:0]   = mul(s0,4'hb) ^ mul(s1,4'hd) ^ mul(s2,4'h9) ^ mul(s3,4'he);
        end

        // --- 3. OPTIMIZED SHARED (Half-Duplex Lane) ---
        else begin : GEN_SHARED
            // Forward base logic
            wire [7:0] f0 = xtime(s0) ^ (xtime(s1) ^ s1) ^ s2 ^ s3;
            wire [7:0] f1 = s0 ^ xtime(s1) ^ (xtime(s2) ^ s2) ^ s3;
            wire [7:0] f2 = s0 ^ s1 ^ xtime(s2) ^ (xtime(s3) ^ s3);
            wire [7:0] f3 = (xtime(s0) ^ s0) ^ s1 ^ s2 ^ xtime(s3);

            // Hadjicostis Inverse Correction (0x0e = 0x02 ^ 0x0c, etc)
            wire [7:0] s02 = s0 ^ s2;
            wire [7:0] s13 = s1 ^ s3;
            wire [7:0] x4_02 = xtime(xtime(s02));
            wire [7:0] x4_13 = xtime(xtime(s13));
            wire [7:0] x8_02 = xtime(x4_02);
            wire [7:0] x8_13 = xtime(x4_13);

            wire [7:0] diff02 = (x8_02 ^ x4_02) ^ (x8_13);         // 0x0c and 0x08
            wire [7:0] diff13 = (x8_02)         ^ (x8_13 ^ x4_13); // 0x08 and 0x0c

            assign out[31:24] = mode ? (f0 ^ diff02) : f0;
            assign out[23:16] = mode ? (f1 ^ diff13) : f1;
            assign out[15:8]  = mode ? (f2 ^ diff02) : f2;
            assign out[7:0]   = mode ? (f3 ^ diff13) : f3;
        end
    endgenerate
endmodule
