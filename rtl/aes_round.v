// ------------------------------------------------------------------------
//                          Generic AES Round
// ------------------------------------------------------------------------
module aes_round_generic #(
    parameter        KEY_BITS  = 128,      // 128, 192, or 256
    parameter [63:0] SBOX_IMPL = "LUT",    // "LUT", "CANRIGHT"
    parameter [63:0] DIRECTION = "FORWARD" // "FORWARD", "INVERSE", or "SHARED"
)(
    input  wire [3:0]   round_num,
    input  wire [127:0] in,
    input  wire [127:0] round_key,
    input  wire         mode,       // 0: FORWARD, 1: INVERSE (Used if DIRECTION == "SHARED")
    output wire [127:0] out
);

    localparam [3:0] Nk = 4'(KEY_BITS / 32);
    localparam [3:0] Nr = (Nk + 4'd6);
    wire is_last_round = (round_num == Nr);

    // Stop Verilator "unused port" warnings if not in SHARED mode
    wire _unused = &{1'b0, mode, 1'b0};

    // --------------------------------------------------------------------
    // 1. Substitution (SubBytes)
    // --------------------------------------------------------------------
    wire [127:0] after_sub;

    sub_generic #(.SBOX_IMPL(SBOX_IMPL), .DIRECTION(DIRECTION), .WIDTH(32'd128))
    u_sub (.in(in), .mode(mode), .out (after_sub));

    // --------------------------------------------------------------------
    // 2. Transposition (ShiftRows)
    // --------------------------------------------------------------------
    wire [127:0] after_shift;

    shift_rows_generic #(.DIRECTION(DIRECTION)) 
    u_shift (.in(after_sub), .mode(mode), .out(after_shift));

    // --------------------------------------------------------------------
    // 3. Linear Mixing (MixColumns)
    // --------------------------------------------------------------------
    wire [127:0] after_mix;

    mix_columns_generic #(.DIRECTION(DIRECTION))
    u_mix (.in  (after_shift), .mode(mode), .out (after_mix));

    // --------------------------------------------------------------------
    // 4. Final selection: Last round skips Mix stage
    // --------------------------------------------------------------------
    assign out = (is_last_round ? after_shift : after_mix) ^ round_key;

endmodule
