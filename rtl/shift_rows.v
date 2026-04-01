module shift_rows (
    input  wire [127:0] in,
    output wire [127:0] out
);
    // State is column-major: bytes [127:120] = row0col0, [119:112] = row1col0 ...
    //
    // Row 0: no shift
    assign out[127:120] = in[127:120];
    assign out[95:88]   = in[95:88];
    assign out[63:56]   = in[63:56];
    assign out[31:24]   = in[31:24];
    // Row 1: shift left by 1
    assign out[119:112] = in[87:80];
    assign out[87:80]   = in[55:48];
    assign out[55:48]   = in[23:16];
    assign out[23:16]   = in[119:112];
    // Row 2: shift left by 2
    assign out[111:104] = in[47:40];
    assign out[79:72]   = in[15:8];
    assign out[47:40]   = in[111:104];
    assign out[15:8]    = in[79:72];
    // Row 3: shift left by 3
    assign out[103:96]  = in[7:0];
    assign out[71:64]   = in[103:96];
    assign out[39:32]   = in[71:64];
    assign out[7:0]     = in[39:32];

endmodule

// -----------------------------------------------
//                  Inverse Shift
// -----------------------------------------------

module inv_shift_rows (
    input  wire [127:0] in,
    output wire [127:0] out
);
    // State is column-major: bytes [127:120] = row0col0, [119:112] = row1col0 ...

    // Row 0: no shift
    assign out[127:120] = in[127:120];
    assign out[95:88]   = in[95:88];
    assign out[63:56]   = in[63:56];
    assign out[31:24]   = in[31:24];

    // Row 1: shift right by 1 (Col0 takes from Col3)
    assign out[119:112] = in[23:16];
    assign out[87:80]   = in[119:112];
    assign out[55:48]   = in[87:80];
    assign out[23:16]   = in[55:48];

    // Row 2: shift right by 2 (Col0 takes from Col2)
    assign out[111:104] = in[47:40];
    assign out[79:72]   = in[15:8];
    assign out[47:40]   = in[111:104];
    assign out[15:8]    = in[79:72];

    // Row 3: shift right by 3 (Col0 takes from Col1)
    assign out[103:96]  = in[71:64];
    assign out[71:64]   = in[39:32];
    assign out[39:32]   = in[7:0];
    assign out[7:0]     = in[103:96];

endmodule
