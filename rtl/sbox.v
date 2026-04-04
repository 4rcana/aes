// ----------------------------------------------------------------
//                  Generic single block substitution
// ----------------------------------------------------------------
module sub_bytes_generic #(
    parameter SBOX_IMPL = "LUT",      // "LUT", "GF4", "GF2"
    parameter DIRECTION = "FORWARD"   // "FORWARD", "INVERSE", "SHARED"
)(
    input  wire [127:0] in,
    input  wire         mode,         // 0:FORWARD, 1:INVERSE
    output wire [127:0] out
);
    genvar i;
    generate
        for (i = 0; i < 16; i = i + 1) begin : sbox_loop
            sbox_generic #(.SBOX_IMPL(SBOX_IMPL), .DIRECTION(DIRECTION)) u_sb (
                .in  (in [127 - i*8 -: 8]),
                .mode(mode),
                .out (out[127 - i*8 -: 8])
            );
        end
    endgenerate
endmodule

// ----------------------------------------------------------------
//                  Generic single word substitution
// ----------------------------------------------------------------
module sub_word_generic #(
    parameter SBOX_IMPL = "LUT",      // "LUT", "GF4", "GF2"
    parameter DIRECTION = "FORWARD"   // "FORWARD", "INVERSE", "SHARED"
)(
    input  wire [31:0] in,
    input  wire        mode,          // 0:FORWARD, 1:INVERSE
    output wire [31:0] out
);
    genvar i;
    generate
        for (i = 0; i < 4; i = i + 1) begin : sbox_loop
            sbox_generic #(.SBOX_IMPL(SBOX_IMPL), .DIRECTION(DIRECTION)) u_sw (
                .in  (in [31 - i*8 -: 8]),
                .mode(mode),
                .out (out[31 - i*8 -: 8])
            );
        end
    endgenerate
endmodule

// ----------------------------------------------------------------
//                  Generic single byte SBOX
// ----------------------------------------------------------------
module sbox_generic #(
    parameter SBOX_IMPL = "LUT",      // "LUT", "GF4", "GF2"
    parameter DIRECTION = "FORWARD"   // "FORWARD", "INVERSE", "SHARED"
)(
    input  wire [7:0] in,
    input  wire       mode,           // 0:FORWARD, 1:INVERSE
    output wire [7:0] out
);
    wire _unused = &{1'b0, mode, 1'b0};

    generate
        if (SBOX_IMPL == "LUT") begin : ARCH_LUT
            wire [7:0] fwd_res, inv_res;
            if (DIRECTION != "INVERSE") sbox_lut     u_fwd (.in(in), .out(fwd_res));
            if (DIRECTION != "FORWARD") inv_sbox_lut u_inv (.in(in), .out(inv_res));

            if      (DIRECTION == "FORWARD") assign out = fwd_res;
            else if (DIRECTION == "INVERSE") assign out = inv_res;
            else                             assign out = mode ? inv_res : fwd_res;
        end 
        else if (SBOX_IMPL == "GF4") begin : ARCH_GF4
            sbox_logic_gf4 u_logic (.in(in), .mode(mode), .out(out));
        end
        else begin : ARCH_GF2
            sbox_logic_gf2 #(.DIRECTION(DIRECTION)) u_logic (.in(in), .mode(mode), .out(out));
        end
    endgenerate
endmodule

// ----------------------------------------------------------------
//                          SBOX Logic GF4
// ----------------------------------------------------------------
module sbox_logic_gf4 (
    input  wire [7:0] in,
    input  wire       mode,      // 0:FORWARD, 1:INVERSE
    output wire [7:0] out
);
    wire [7:0] inv_aff_out, math_in, math_out, fwd_aff_out;

    // INVERSE path (Decryption): Affine-Inverse happens BEFORE Inversion
    inv_sbox_affine u_iaff (.in(in), .out(inv_aff_out));

    // MUX: If Decrypt, feed processed byte. If Encrypt, feed raw byte.
    assign math_in = mode ? inv_aff_out : in;

    // Shared 1/x logic
    gf8_inv_gf4 u_inv_engine (.in(math_in), .out(math_out));

    // FORWARD path (Encryption): Affine happens AFTER Inversion
    sbox_affine u_faff (.in(math_out), .out(fwd_aff_out));

    // Final Selection: Encrypt results in fwd_aff_out, Decrypt results in math_out
    assign out = mode ? math_out : fwd_aff_out;
endmodule

// ----------------------------------------------------------------
//                          SBOX Logic GF2
// ----------------------------------------------------------------
module sbox_logic_gf2 #(
    parameter DIRECTION = "FORWARD"
)(
    input  wire [7:0] in,
    input  wire       mode,      // 0:FORWARD, 1:INVERSE
    output wire [7:0] out
);
    wire [7:0] inv_aff_out, math_in, math_out, fwd_aff_out;

    inv_sbox_affine u_iaff (.in(in), .out(inv_aff_out));

    assign math_in = (DIRECTION == "SHARED")  ? (mode ? inv_aff_out : in) :
                     (DIRECTION == "INVERSE") ? inv_aff_out : in;

    gf8_inv_gf2 u_math (.in(math_in), .out(math_out));

    sbox_affine u_faff (.in(math_out), .out(fwd_aff_out));

    if (DIRECTION == "SHARED")       assign out = mode ? math_out : fwd_aff_out;
    else if (DIRECTION == "INVERSE") assign out = math_out;
    else                             assign out = fwd_aff_out;
endmodule

// ----------------------------------------------------------------
//                        SBOX Forward Affine
// ----------------------------------------------------------------
module sbox_affine (
    input  wire [7:0] in,
    output wire [7:0] out
);
    // Standard AES Forward Affine: out = M*in + 63
    assign out[0] = ~(in[0] ^ in[4] ^ in[5] ^ in[6] ^ in[7]);
    assign out[1] = ~(in[1] ^ in[5] ^ in[6] ^ in[7] ^ in[0]);
    assign out[2] =  (in[2] ^ in[6] ^ in[7] ^ in[0] ^ in[1]);
    assign out[3] =  (in[3] ^ in[7] ^ in[0] ^ in[1] ^ in[2]);
    assign out[4] =  (in[4] ^ in[0] ^ in[1] ^ in[2] ^ in[3]);
    assign out[5] = ~(in[5] ^ in[1] ^ in[2] ^ in[3] ^ in[4]);
    assign out[6] = ~(in[6] ^ in[2] ^ in[3] ^ in[4] ^ in[5]);
    assign out[7] =  (in[7] ^ in[3] ^ in[4] ^ in[5] ^ in[6]);
endmodule

// ----------------------------------------------------------------
//                        SBOX Inverse Affine
// ----------------------------------------------------------------
module inv_sbox_affine (
    input  wire [7:0] in,
    output wire [7:0] out
);
    // Standard AES Inverse Affine: out = M_inv*(in + 63)
    // This combines matrix multiplication and the 0x05 constant
    wire [7:0] x = in ^ 8'h63;
    assign out[0] = x[2] ^ x[5] ^ x[7];
    assign out[1] = x[0] ^ x[3] ^ x[6];
    assign out[2] = x[1] ^ x[4] ^ x[7];
    assign out[3] = x[0] ^ x[2] ^ x[5];
    assign out[4] = x[1] ^ x[3] ^ x[6];
    assign out[5] = x[2] ^ x[4] ^ x[7];
    assign out[6] = x[0] ^ x[3] ^ x[5];
    assign out[7] = x[1] ^ x[4] ^ x[6];
endmodule

// ----------------------------------------------------------------
//                          SBOX LUT
// ----------------------------------------------------------------
module sbox_lut (input [7:0] in, output reg [7:0] out);
    always @(*) begin
        case (in)
            8'h00: out = 8'h63; 8'h01: out = 8'h7c; 8'h02: out = 8'h77; 8'h03: out = 8'h7b;
            8'h04: out = 8'hf2; 8'h05: out = 8'h6b; 8'h06: out = 8'h6f; 8'h07: out = 8'hc5;
            8'h08: out = 8'h30; 8'h09: out = 8'h01; 8'h0a: out = 8'h67; 8'h0b: out = 8'h2b;
            8'h0c: out = 8'hfe; 8'h0d: out = 8'hd7; 8'h0e: out = 8'hab; 8'h0f: out = 8'h76;
            8'h10: out = 8'hca; 8'h11: out = 8'h82; 8'h12: out = 8'hc9; 8'h13: out = 8'h7d;
            8'h14: out = 8'hfa; 8'h15: out = 8'h59; 8'h16: out = 8'h47; 8'h17: out = 8'hf0;
            8'h18: out = 8'had; 8'h19: out = 8'hd4; 8'h1a: out = 8'ha2; 8'h1b: out = 8'haf;
            8'h1c: out = 8'h9c; 8'h1d: out = 8'ha4; 8'h1e: out = 8'h72; 8'h1f: out = 8'hc0;
            8'h20: out = 8'hb7; 8'h21: out = 8'hfd; 8'h22: out = 8'h93; 8'h23: out = 8'h26;
            8'h24: out = 8'h36; 8'h25: out = 8'h3f; 8'h26: out = 8'hf7; 8'h27: out = 8'hcc;
            8'h28: out = 8'h34; 8'h29: out = 8'ha5; 8'h2a: out = 8'he5; 8'h2b: out = 8'hf1;
            8'h2c: out = 8'h71; 8'h2d: out = 8'hd8; 8'h2e: out = 8'h31; 8'h2f: out = 8'h15;
            8'h30: out = 8'h04; 8'h31: out = 8'hc7; 8'h32: out = 8'h23; 8'h33: out = 8'hc3;
            8'h34: out = 8'h18; 8'h35: out = 8'h96; 8'h36: out = 8'h05; 8'h37: out = 8'h9a;
            8'h38: out = 8'h07; 8'h39: out = 8'h12; 8'h3a: out = 8'h80; 8'h3b: out = 8'he2;
            8'h3c: out = 8'heb; 8'h3d: out = 8'h27; 8'h3e: out = 8'hb2; 8'h3f: out = 8'h75;
            8'h40: out = 8'h09; 8'h41: out = 8'h83; 8'h42: out = 8'h2c; 8'h43: out = 8'h1a;
            8'h44: out = 8'h1b; 8'h45: out = 8'h6e; 8'h46: out = 8'h5a; 8'h47: out = 8'ha0;
            8'h48: out = 8'h52; 8'h49: out = 8'h3b; 8'h4a: out = 8'hd6; 8'h4b: out = 8'hb3;
            8'h4c: out = 8'h29; 8'h4d: out = 8'he3; 8'h4e: out = 8'h2f; 8'h4f: out = 8'h84;
            8'h50: out = 8'h53; 8'h51: out = 8'hd1; 8'h52: out = 8'h00; 8'h53: out = 8'hed;
            8'h54: out = 8'h20; 8'h55: out = 8'hfc; 8'h56: out = 8'hb1; 8'h57: out = 8'h5b;
            8'h58: out = 8'h6a; 8'h59: out = 8'hcb; 8'h5a: out = 8'hbe; 8'h5b: out = 8'h39;
            8'h5c: out = 8'h4a; 8'h5d: out = 8'h4c; 8'h5e: out = 8'h58; 8'h5f: out = 8'hcf;
            8'h60: out = 8'hd0; 8'h61: out = 8'hef; 8'h62: out = 8'haa; 8'h63: out = 8'hfb;
            8'h64: out = 8'h43; 8'h65: out = 8'h4d; 8'h66: out = 8'h33; 8'h67: out = 8'h85;
            8'h68: out = 8'h45; 8'h69: out = 8'hf9; 8'h6a: out = 8'h02; 8'h6b: out = 8'h7f;
            8'h6c: out = 8'h50; 8'h6d: out = 8'h3c; 8'h6e: out = 8'h9f; 8'h6f: out = 8'ha8;
            8'h70: out = 8'h51; 8'h71: out = 8'ha3; 8'h72: out = 8'h40; 8'h73: out = 8'h8f;
            8'h74: out = 8'h92; 8'h75: out = 8'h9d; 8'h76: out = 8'h38; 8'h77: out = 8'hf5;
            8'h78: out = 8'hbc; 8'h79: out = 8'hb6; 8'h7a: out = 8'hda; 8'h7b: out = 8'h21;
            8'h7c: out = 8'h10; 8'h7d: out = 8'hff; 8'h7e: out = 8'hf3; 8'h7f: out = 8'hd2;
            8'h80: out = 8'hcd; 8'h81: out = 8'h0c; 8'h82: out = 8'h13; 8'h83: out = 8'hec;
            8'h84: out = 8'h5f; 8'h85: out = 8'h97; 8'h86: out = 8'h44; 8'h87: out = 8'h17;
            8'h88: out = 8'hc4; 8'h89: out = 8'ha7; 8'h8a: out = 8'h7e; 8'h8b: out = 8'h3d;
            8'h8c: out = 8'h64; 8'h8d: out = 8'h5d; 8'h8e: out = 8'h19; 8'h8f: out = 8'h73;
            8'h90: out = 8'h60; 8'h91: out = 8'h81; 8'h92: out = 8'h4f; 8'h93: out = 8'hdc;
            8'h94: out = 8'h22; 8'h95: out = 8'h2a; 8'h96: out = 8'h90; 8'h97: out = 8'h88;
            8'h98: out = 8'h46; 8'h99: out = 8'hee; 8'h9a: out = 8'hb8; 8'h9b: out = 8'h14;
            8'h9c: out = 8'hde; 8'h9d: out = 8'h5e; 8'h9e: out = 8'h0b; 8'h9f: out = 8'hdb;
            8'ha0: out = 8'he0; 8'ha1: out = 8'h32; 8'ha2: out = 8'h3a; 8'ha3: out = 8'h0a;
            8'ha4: out = 8'h49; 8'ha5: out = 8'h06; 8'ha6: out = 8'h24; 8'ha7: out = 8'h5c;
            8'ha8: out = 8'hc2; 8'ha9: out = 8'hd3; 8'haa: out = 8'hac; 8'hab: out = 8'h62;
            8'hac: out = 8'h91; 8'had: out = 8'h95; 8'hae: out = 8'he4; 8'haf: out = 8'h79;
            8'hb0: out = 8'he7; 8'hb1: out = 8'hc8; 8'hb2: out = 8'h37; 8'hb3: out = 8'h6d;
            8'hb4: out = 8'h8d; 8'hb5: out = 8'hd5; 8'hb6: out = 8'h4e; 8'hb7: out = 8'ha9;
            8'hb8: out = 8'h6c; 8'hb9: out = 8'h56; 8'hba: out = 8'hf4; 8'hbb: out = 8'hea;
            8'hbc: out = 8'h65; 8'hbd: out = 8'h7a; 8'hbe: out = 8'hae; 8'hbf: out = 8'h08;
            8'hc0: out = 8'hba; 8'hc1: out = 8'h78; 8'hc2: out = 8'h25; 8'hc3: out = 8'h2e;
            8'hc4: out = 8'h1c; 8'hc5: out = 8'ha6; 8'hc6: out = 8'hb4; 8'hc7: out = 8'hc6;
            8'hc8: out = 8'he8; 8'hc9: out = 8'hdd; 8'hca: out = 8'h74; 8'hcb: out = 8'h1f;
            8'hcc: out = 8'h4b; 8'hcd: out = 8'hbd; 8'hce: out = 8'h8b; 8'hcf: out = 8'h8a;
            8'hd0: out = 8'h70; 8'hd1: out = 8'h3e; 8'hd2: out = 8'hb5; 8'hd3: out = 8'h66;
            8'hd4: out = 8'h48; 8'hd5: out = 8'h03; 8'hd6: out = 8'hf6; 8'hd7: out = 8'h0e;
            8'hd8: out = 8'h61; 8'hd9: out = 8'h35; 8'hda: out = 8'h57; 8'hdb: out = 8'hb9;
            8'hdc: out = 8'h86; 8'hdd: out = 8'hc1; 8'hde: out = 8'h1d; 8'hdf: out = 8'h9e;
            8'he0: out = 8'he1; 8'he1: out = 8'hf8; 8'he2: out = 8'h98; 8'he3: out = 8'h11;
            8'he4: out = 8'h69; 8'he5: out = 8'hd9; 8'he6: out = 8'h8e; 8'he7: out = 8'h94;
            8'he8: out = 8'h9b; 8'he9: out = 8'h1e; 8'hea: out = 8'h87; 8'heb: out = 8'he9;
            8'hec: out = 8'hce; 8'hed: out = 8'h55; 8'hee: out = 8'h28; 8'hef: out = 8'hdf;
            8'hf0: out = 8'h8c; 8'hf1: out = 8'ha1; 8'hf2: out = 8'h89; 8'hf3: out = 8'h0d;
            8'hf4: out = 8'hbf; 8'hf5: out = 8'he6; 8'hf6: out = 8'h42; 8'hf7: out = 8'h68;
            8'hf8: out = 8'h41; 8'hf9: out = 8'h99; 8'hfa: out = 8'h2d; 8'hfb: out = 8'h0f;
            8'hfc: out = 8'hb0; 8'hfd: out = 8'h54; 8'hfe: out = 8'hbb; 8'hff: out = 8'h16;
            default: out = 8'h00;
        endcase
    end
endmodule

// ----------------------------------------------------------------
//                      Inverse SBOX LUT
// ----------------------------------------------------------------
module inv_sbox_lut (input [7:0] in, output reg [7:0] out);
    always @(*) begin
        case (in)
            8'h00: out = 8'h52; 8'h01: out = 8'h09; 8'h02: out = 8'h6a; 8'h03: out = 8'hd5;
            8'h04: out = 8'h30; 8'h05: out = 8'h36; 8'h06: out = 8'ha5; 8'h07: out = 8'h38;
            8'h08: out = 8'hbf; 8'h09: out = 8'h40; 8'h0a: out = 8'ha3; 8'h0b: out = 8'h9e;
            8'h0c: out = 8'h81; 8'h0d: out = 8'hf3; 8'h0e: out = 8'hd7; 8'h0f: out = 8'hfb;
            8'h10: out = 8'h7c; 8'h11: out = 8'he3; 8'h12: out = 8'h39; 8'h13: out = 8'h82;
            8'h14: out = 8'h9b; 8'h15: out = 8'h2f; 8'h16: out = 8'hff; 8'h17: out = 8'h87;
            8'h18: out = 8'h34; 8'h19: out = 8'h8e; 8'h1a: out = 8'h43; 8'h1b: out = 8'h44;
            8'h1c: out = 8'hc4; 8'h1d: out = 8'hde; 8'h1e: out = 8'he9; 8'h1f: out = 8'hcb;
            8'h20: out = 8'h54; 8'h21: out = 8'h7b; 8'h22: out = 8'h94; 8'h23: out = 8'h32;
            8'h24: out = 8'ha6; 8'h25: out = 8'hc2; 8'h26: out = 8'h23; 8'h27: out = 8'h3d;
            8'h28: out = 8'hee; 8'h29: out = 8'h4c; 8'h2a: out = 8'h95; 8'h2b: out = 8'h0b;
            8'h2c: out = 8'h42; 8'h2d: out = 8'hfa; 8'h2e: out = 8'hc3; 8'h2f: out = 8'h4e;
            8'h30: out = 8'h08; 8'h31: out = 8'h2e; 8'h32: out = 8'ha1; 8'h33: out = 8'h66;
            8'h34: out = 8'h28; 8'h35: out = 8'hd9; 8'h36: out = 8'h24; 8'h37: out = 8'hb2;
            8'h38: out = 8'h76; 8'h39: out = 8'h5b; 8'h3a: out = 8'ha2; 8'h3b: out = 8'h49;
            8'h3c: out = 8'h6d; 8'h3d: out = 8'h8b; 8'h3e: out = 8'hd1; 8'h3f: out = 8'h25;
            8'h40: out = 8'h72; 8'h41: out = 8'hf8; 8'h42: out = 8'hf6; 8'h43: out = 8'h64;
            8'h44: out = 8'h86; 8'h45: out = 8'h68; 8'h46: out = 8'h98; 8'h47: out = 8'h16;
            8'h48: out = 8'hd4; 8'h49: out = 8'ha4; 8'h4a: out = 8'h5c; 8'h4b: out = 8'hcc;
            8'h4c: out = 8'h5d; 8'h4d: out = 8'h65; 8'h4e: out = 8'hb6; 8'h4f: out = 8'h92;
            8'h50: out = 8'h6c; 8'h51: out = 8'h70; 8'h52: out = 8'h48; 8'h53: out = 8'h50;
            8'h54: out = 8'hfd; 8'h55: out = 8'hed; 8'h56: out = 8'hb9; 8'h57: out = 8'hda;
            8'h58: out = 8'h5e; 8'h59: out = 8'h15; 8'h5a: out = 8'h46; 8'h5b: out = 8'h57;
            8'h5c: out = 8'ha7; 8'h5d: out = 8'h8d; 8'h5e: out = 8'h9d; 8'h5f: out = 8'h84;
            8'h60: out = 8'h90; 8'h61: out = 8'hd8; 8'h62: out = 8'hab; 8'h63: out = 8'h00;
            8'h64: out = 8'h8c; 8'h65: out = 8'hbc; 8'h66: out = 8'hd3; 8'h67: out = 8'h0a;
            8'h68: out = 8'hf7; 8'h69: out = 8'he4; 8'h6a: out = 8'h58; 8'h6b: out = 8'h05;
            8'h6c: out = 8'hb8; 8'h6d: out = 8'hb3; 8'h6e: out = 8'h45; 8'h6f: out = 8'h06;
            8'h70: out = 8'hd0; 8'h71: out = 8'h2c; 8'h72: out = 8'h1e; 8'h73: out = 8'h8f;
            8'h74: out = 8'hca; 8'h75: out = 8'h3f; 8'h76: out = 8'h0f; 8'h77: out = 8'h02;
            8'h78: out = 8'hc1; 8'h79: out = 8'haf; 8'h7a: out = 8'hbd; 8'h7b: out = 8'h03;
            8'h7c: out = 8'h01; 8'h7d: out = 8'h13; 8'h7e: out = 8'h8a; 8'h7f: out = 8'h6b;
            8'h80: out = 8'h3a; 8'h81: out = 8'h91; 8'h82: out = 8'h11; 8'h83: out = 8'h41;
            8'h84: out = 8'h4f; 8'h85: out = 8'h67; 8'h86: out = 8'hdc; 8'h87: out = 8'hea;
            8'h88: out = 8'h97; 8'h89: out = 8'hf2; 8'h8a: out = 8'hcf; 8'h8b: out = 8'hce;
            8'h8c: out = 8'hf0; 8'h8d: out = 8'hb4; 8'h8e: out = 8'he6; 8'h8f: out = 8'h73;
            8'h90: out = 8'h96; 8'h91: out = 8'hac; 8'h92: out = 8'h74; 8'h93: out = 8'h22;
            8'h94: out = 8'he7; 8'h95: out = 8'had; 8'h96: out = 8'h35; 8'h97: out = 8'h85;
            8'h98: out = 8'he2; 8'h99: out = 8'hf9; 8'h9a: out = 8'h37; 8'h9b: out = 8'he8;
            8'h9c: out = 8'h1c; 8'h9d: out = 8'h75; 8'h9e: out = 8'hdf; 8'h9f: out = 8'h6e;
            8'ha0: out = 8'h47; 8'ha1: out = 8'hf1; 8'ha2: out = 8'h1a; 8'ha3: out = 8'h71;
            8'ha4: out = 8'h1d; 8'ha5: out = 8'h29; 8'ha6: out = 8'hc5; 8'ha7: out = 8'h89;
            8'ha8: out = 8'h6f; 8'ha9: out = 8'hb7; 8'haa: out = 8'h62; 8'hab: out = 8'h0e;
            8'hac: out = 8'haa; 8'had: out = 8'h18; 8'hae: out = 8'hbe; 8'haf: out = 8'h1b;
            8'hb0: out = 8'hfc; 8'hb1: out = 8'h56; 8'hb2: out = 8'h3e; 8'hb3: out = 8'h4b;
            8'hb4: out = 8'hc6; 8'hb5: out = 8'hd2; 8'hb6: out = 8'h79; 8'hb7: out = 8'h20;
            8'hb8: out = 8'h9a; 8'hb9: out = 8'hdb; 8'hba: out = 8'hc0; 8'hbb: out = 8'hfe;
            8'hbc: out = 8'h78; 8'hbd: out = 8'hcd; 8'hbe: out = 8'h5a; 8'hbf: out = 8'hf4;
            8'hc0: out = 8'h1f; 8'hc1: out = 8'hdd; 8'hc2: out = 8'ha8; 8'hc3: out = 8'h33;
            8'hc4: out = 8'h88; 8'hc5: out = 8'h07; 8'hc6: out = 8'hc7; 8'hc7: out = 8'h31;
            8'hc8: out = 8'hb1; 8'hc9: out = 8'h12; 8'hca: out = 8'h10; 8'hcb: out = 8'h59;
            8'hcc: out = 8'h27; 8'hcd: out = 8'h80; 8'hce: out = 8'hec; 8'hcf: out = 8'h5f;
            8'hd0: out = 8'h60; 8'hd1: out = 8'h51; 8'hd2: out = 8'h7f; 8'hd3: out = 8'ha9;
            8'hd4: out = 8'h19; 8'hd5: out = 8'hb5; 8'hd6: out = 8'h4a; 8'hd7: out = 8'h0d;
            8'hd8: out = 8'h2d; 8'hd9: out = 8'he5; 8'hda: out = 8'h7a; 8'hdb: out = 8'h9f;
            8'hdc: out = 8'h93; 8'hdd: out = 8'hc9; 8'hde: out = 8'h9c; 8'hdf: out = 8'hef;
            8'he0: out = 8'ha0; 8'he1: out = 8'he0; 8'he2: out = 8'h3b; 8'he3: out = 8'h4d;
            8'he4: out = 8'hae; 8'he5: out = 8'h2a; 8'he6: out = 8'hf5; 8'he7: out = 8'hb0;
            8'he8: out = 8'hc8; 8'he9: out = 8'heb; 8'hea: out = 8'hbb; 8'heb: out = 8'h3c;
            8'hec: out = 8'h83; 8'hed: out = 8'h53; 8'hee: out = 8'h99; 8'hef: out = 8'h61;
            8'hf0: out = 8'h17; 8'hf1: out = 8'h2b; 8'hf2: out = 8'h04; 8'hf3: out = 8'h7e;
            8'hf4: out = 8'hba; 8'hf5: out = 8'h77; 8'hf6: out = 8'hd6; 8'hf7: out = 8'h26;
            8'hf8: out = 8'he1; 8'hf9: out = 8'h69; 8'hfa: out = 8'h14; 8'hfb: out = 8'h63;
            8'hfc: out = 8'h55; 8'hfd: out = 8'h21; 8'hfe: out = 8'h0c; 8'hff: out = 8'h7d;
            default: out = 8'h00;
        endcase
    end
endmodule

// ----------------------------------------------------------------
//                      GF8 Inverter (GF4 Core)
// ----------------------------------------------------------------
module gf8_inv_gf4 (
    input  wire [7:0] in,
    output wire [7:0] out
);
    // 1. Isomorphism: Map GF(2^8) -> GF(2^4)^2 (Canright Basis)
    wire [3:0] a, b;
    assign a[3] = in[7] ^ in[5];
    assign a[2] = in[1] ^ in[0];
    assign a[1] = in[7] ^ in[5] ^ in[4] ^ in[3] ^ in[1];
    assign a[0] = in[6] ^ in[4] ^ in[1];
    assign b[3] = in[1] ^ in[0] ^ in[6];
    assign b[2] = in[2] ^ in[1];
    assign b[1] = in[7] ^ in[4] ^ in[1];
    assign b[0] = in[6] ^ in[1] ^ in[0] ^ in[3] ^ in[2];

    // 2. Inversion Math
    wire [3:0] a_sq, b_sq, ab, d, d_inv, q_h, q_l;

    // Square in GF(2^4)
    assign a_sq = {a[3], a[3]^a[2], a[1], a[1]^a[0]};
    assign b_sq = {b[3], b[3]^b[2], b[1], b[1]^b[0]};
    
    // Scale a_sq by Alpha (Constant for this basis)
    wire [3:0] a_sq_alpha = {a_sq[2]^a_sq[1]^a_sq[0], a_sq[3], a_sq[2], a_sq[1]};
    
    gf4_mul u_m0 (.a(a), .b(b), .q(ab));
    
    // Inversion Core
    assign d = a_sq_alpha ^ ab ^ b_sq;
    gf4_inv u_i0 (.in(d), .out(d_inv));

    gf4_mul u_m1 (.a(d_inv), .b(a),   .q(q_h));
    gf4_mul u_m2 (.a(d_inv), .b(a^b), .q(q_l));

    // 3. Inverse Isomorphism: Map GF(2^4)^2 -> GF(2^8)
    assign out[7] = q_h[3] ^ q_h[2];
    assign out[6] = q_h[2] ^ q_l[1];
    assign out[5] = q_h[3] ^ q_l[3];
    assign out[4] = q_h[2] ^ q_l[3];
    assign out[3] = q_h[2] ^ q_h[1] ^ q_h[0] ^ q_l[1];
    assign out[2] = q_h[1] ^ q_l[2];
    assign out[1] = q_h[0] ^ q_l[0];
    assign out[0] = q_h[3] ^ q_h[2] ^ q_h[1] ^ q_l[1];
endmodule

// ----------------------------------------------------------------
//                      GF8 Inverter (GF2)
// ----------------------------------------------------------------
module gf8_inv_gf2 (
    input  wire [7:0] in,
    output wire [7:0] out
);
    // 1. Isomorphism GF(2^8) -> GF(2^4)^2
    wire [3:0] a = {in[7]^in[5], in[7]^in[6]^in[4]^in[3], in[6]^in[5]^in[4], in[6]^in[2]};
    wire [3:0] b = {in[5]^in[4], in[5]^in[3], in[4]^in[1], in[0]};

    // 2. Inversion using the new GF2-based GF4 modules
    wire [3:0] a2 = {a[3], a[3]^a[2], a[2]^a[1], a[1]^a[0]}; 
    wire [3:0] ab, b2, combined, d_inv;

    gf4_mul_gf2 m0 (.in_a(a), .in_b(b), .out(ab));
    assign b2 = {b[3], b[3]^b[2], b[2]^b[1], b[1]^b[0]};
    
    // Scale a^2 by the GF(2^4) constant Phi (usually {1100} in this basis)
    // For this specific mapping, scaling a^2 is just a bit shuffle
    wire [3:0] a2_phi = {a2[1]^a2[0], a2[1], a2[1]^a2[2], a2[0]}; 

    assign combined = a2_phi ^ ab ^ b2;
    gf4_inv_gf2 i0 (.in(combined), .out(d_inv));

    wire [3:0] y_h, y_l;
    gf4_mul_gf2 m1 (.in_a(a),   .in_b(d_inv), .out(y_h));
    gf4_mul_gf2 m2 (.in_a(a^b), .in_b(d_inv), .out(y_l));

    // 3. Inverse Isomorphism (Same as before)
    assign out[7] = y_h[3]^y_h[2];
    assign out[6] = y_h[3];
    assign out[5] = y_h[3]^y_h[2]^y_l[3];
    assign out[4] = y_h[2]^y_l[3];
    assign out[3] = y_h[2]^y_l[2]^y_l[1];
    assign out[2] = y_h[3]^y_h[2]^y_l[3]^y_l[2];
    assign out[1] = y_h[3]^y_l[1];
    assign out[0] = y_h[2]^y_l[0];
endmodule

// ----------------------------------------------------------------
//                          GF4 Multiplier
// ----------------------------------------------------------------
module gf4_mul (input [3:0] a, input [3:0] b, output [3:0] q);
    // Multiplies in GF(2^4) / GF(2^2)
    wire aH = a[3], aL = a[2], bH = b[3], bL = b[2];
    wire cH = a[1], cL = a[0], dH = b[1], dL = b[0];
    
    // Low level bit math to ensure basis consistency
    assign q[3] = aH&bH ^ aL&bH ^ aH&bL ^ aH&dH ^ aL&dH ^ aH&dL ^ cH&dH ^ cL&dH ^ cH&dL;
    assign q[2] = aL&bL ^ aL&dH ^ aH&dL ^ aL&dL ^ cL&dL ^ cH&dL ^ cL&dH;
    assign q[1] = aH&bH ^ aH&dH ^ aL&dH ^ aH&dL ^ cH&dH ^ cL&dH ^ cH&dL ^ cL&dL;
    assign q[0] = aL&bL ^ aL&dL ^ cL&dL;
endmodule

// ----------------------------------------------------------------
//                          GF4 Inverter
// ----------------------------------------------------------------
module gf4_inv (input [3:0] in, output [3:0] out);
    // 4-bit Inverter optimized for the Canright Basis
    assign out[3] = in[3] ^ in[3]&in[2]&in[1] ^ in[3]&in[0] ^ in[2];
    assign out[2] = in[3]&in[2]&in[1] ^ in[3]&in[2]&in[0] ^ in[3]&in[0] ^ in[2] ^ in[2]&in[1];
    assign out[1] = in[3] ^ in[3]&in[2]&in[1] ^ in[3]&in[1]&in[0] ^ in[2] ^ in[2]&in[0] ^ in[1];
    assign out[0] = in[3]&in[2]&in[1] ^ in[3]&in[2]&in[0] ^ in[3]&in[1] ^ in[3]&in[1]&in[0] ^ in[3]&in[0] ^ in[2] ^ in[2]&in[1] ^ in[2]&in[1]&in[0] ^ in[1] ^ in[0];
endmodule

// ----------------------------------------------------------------
//                      GF4 Multiplier (GF2)
// ----------------------------------------------------------------
module gf4_mul_gf2 (
    input  wire [3:0] in_a,
    input  wire [3:0] in_b,
    output wire [3:0] out
);
    wire [1:0] a_h = in_a[3:2], a_l = in_a[1:0];
    wire [1:0] b_h = in_b[3:2], b_l = in_b[1:0];
    wire [1:0] m_h, m_l, m_mid, scaled_h;

    gf2_mul u0 (.in_a(a_h),       .in_b(b_h),       .out(m_h));
    gf2_mul u1 (.in_a(a_l),       .in_b(b_l),       .out(m_l));
    gf2_mul u2 (.in_a(a_h ^ a_l), .in_b(b_h ^ b_l), .out(m_mid));
    
    gf2_scale_omega s0 (.in(m_h), .out(scaled_h));

    assign out = { (m_mid ^ m_l), (scaled_h ^ m_l) };
endmodule

// ----------------------------------------------------------------
//                      GF4 Inverter (GF2)
// ----------------------------------------------------------------
module gf4_inv_gf2 (
    input  wire [3:0] in,
    output wire [3:0] out
);
    wire [1:0] a_h = in[3:2], a_l = in[1:0];
    wire [1:0] a_h_sq = {a_h[1], a_h[1] ^ a_h[0]};
    wire [1:0] a_l_sq = {a_l[1], a_l[1] ^ a_l[0]};
    wire [1:0] a_hl, combined, d_inv;

    gf2_mul m0 (.in_a(a_h), .in_b(a_l), .out(a_hl));
    gf2_scale_omega s0 (.in(a_h_sq), .out(combined));
    
    gf2_inv i0 (.in(combined ^ a_hl ^ a_l_sq), .out(d_inv));

    gf2_mul m1 (.in_a(a_h),       .in_b(d_inv), .out(out[3:2]));
    gf2_mul m2 (.in_a(a_h ^ a_l), .in_b(d_inv), .out(out[1:0]));
endmodule

// ----------------------------------------------------------------
//                          GF2 Multiplier
// ----------------------------------------------------------------
module gf2_mul (
    input  wire [1:0] in_a,
    input  wire [1:0] in_b,
    output wire [1:0] out
);
    wire a0 = in_a[0], a1 = in_a[1];
    wire b0 = in_b[0], b1 = in_b[1];
    
    assign out[0] = (a0 & b0) ^ (a1 & b1);
    assign out[1] = (a1 & b0) ^ (a0 & b1) ^ (a1 & b1);
endmodule

// ----------------------------------------------------------------
//                          GF2 Inverter
// ----------------------------------------------------------------
module gf2_inv (
    input  wire [1:0] in,
    output wire [1:0] out
);
    assign out[0] = in[1] ^ in[0];
    assign out[1] = in[1];
endmodule

// ----------------------------------------------------------------
//                          GF2 Scale Omega
// ----------------------------------------------------------------
module gf2_scale_omega (
    input  wire [1:0] in,
    output wire [1:0] out
);
    assign out[0] = in[1] ^ in[0];
    assign out[1] = in[0];
endmodule
