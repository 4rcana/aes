import crypto_pkg::*;

// ----------------------------------------------------------------
//                  Generic ShiftRows (Transposition)
// ----------------------------------------------------------------
module shift_rows_generic #(
    parameter crypto_pkg::round_dir_t DIRECTION = DIR_FORWARD
)(
    input  wire [127:0] in,
    input  wire         mode,              // 0:FORWARD, 1:INVERSE
    output wire [127:0] out
);

    wire _unused = &{1'b0, mode, 1'b0};

    // State is column-major: bytes [127:120] = row0col0, [119:112] = row1col0 ...
    
    wire [127:0] fwd_wire;
    wire [127:0] inv_wire;

    generate
        // ---------------------------------------------------------
        // 1. Forward ShiftRows Logic (Encryption)
        // ---------------------------------------------------------
        if (DIRECTION == DIR_FORWARD || DIRECTION == DIR_SHARED) begin : GEN_FWD
            logic [127:0] fwd_wire;
            
            // Row 0: No shift
            assign fwd_wire[127:120] = in[127:120];
            assign fwd_wire[95:88]   = in[95:88];
            assign fwd_wire[63:56]   = in[63:56];
            assign fwd_wire[31:24]   = in[31:24];
            // Row 1: Left shift 1 (R1C0 = R1C1, R1C1 = R1C2, R1C2 = R1C3, R1C3 = R1C0)
            assign fwd_wire[119:112] = in[87:80];
            assign fwd_wire[87:80]   = in[55:48];
            assign fwd_wire[55:48]   = in[23:16];
            assign fwd_wire[23:16]   = in[119:112];
            // Row 2: Left shift 2
            assign fwd_wire[111:104] = in[47:40];
            assign fwd_wire[79:72]   = in[15:8];
            assign fwd_wire[47:40]   = in[111:104];
            assign fwd_wire[15:8]    = in[79:72];
            // Row 3: Left shift 3
            assign fwd_wire[103:96]  = in[7:0];
            assign fwd_wire[71:64]   = in[103:96];
            assign fwd_wire[39:32]   = in[71:64];
            assign fwd_wire[7:0]     = in[39:32];
        end

        // ---------------------------------------------------------
        // 2. Inverse ShiftRows Logic (Decryption)
        // ---------------------------------------------------------
        if (DIRECTION == DIR_INVERSE || DIRECTION == DIR_SHARED) begin : GEN_INV
            logic [127:0] inv_wire;
            
            // Row 0: No shift
            assign inv_wire[127:120] = in[127:120];
            assign inv_wire[95:88]   = in[95:88];
            assign inv_wire[63:56]   = in[63:56];
            assign inv_wire[31:24]   = in[31:24];
            // Row 1: Right shift 1 (R1C0 = R1C3, R1C3 = R1C2, R1C2 = R1C1, R1C1 = R1C0)
            assign inv_wire[119:112] = in[23:16];
            assign inv_wire[87:80]   = in[119:112];
            assign inv_wire[55:48]   = in[87:80];
            assign inv_wire[23:16]   = in[55:48];
            // Row 2: Right shift 2
            assign inv_wire[111:104] = in[47:40];
            assign inv_wire[79:72]   = in[15:8];
            assign inv_wire[47:40]   = in[111:104];
            assign inv_wire[15:8]    = in[79:72];
            // Row 3: Right shift 3
            assign inv_wire[103:96]  = in[71:64];
            assign inv_wire[71:64]   = in[39:32];
            assign inv_wire[39:32]   = in[7:0];
            assign inv_wire[7:0]     = in[103:96];
        end

        // ---------------------------------------------------------
        // 3. Final Output Selection
        // ---------------------------------------------------------
        if (DIRECTION == DIR_FORWARD) begin
            assign out = GEN_FWD.fwd_wire;
        end else if (DIRECTION == DIR_INVERSE) begin
            assign out = GEN_INV.inv_wire;
        end else begin // DIR_SHARED
            assign out = mode ? GEN_INV.inv_wire : GEN_FWD.fwd_wire;
        end
    endgenerate

endmodule
