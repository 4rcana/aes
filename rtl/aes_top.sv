import crypto_pkg::*;

module aes_top #(
    parameter crypto_pkg::sbox_arch_t SBOX_ARCH  = SBOX_LUT,       // SBOX_LUT, SBOX_CANRIGHT. 
    parameter crypto_pkg::duplex_t    DUPLEX     = DUPLEX_HALF,    // DUPLEX_HALF, DUPLEX_FULL.
    parameter crypto_pkg::aes_mode_t  MODE       = AES_ECB,        // AES_ECB, AES_CBC.
    parameter integer                 KEY_BITS   = 128,            // 128, 192, 256.
    parameter integer                 PIPE_DEPTH = 1               // PIPELINED DESIGN NOT YET ARCHEMENTED.
)(
    input  wire                clk,
    input  wire                rst_n,

    // Key Interface
    input  wire                key_load,
    input  wire [KEY_BITS-1:0] key_in,

    // IV Interface
    input  wire                iv_load,
    input  wire [127:0]        iv_in,

    // Specific Status Flags
    output wire                key_ready,
    output wire                iv_ready,
    //output wire                core_idle,

    // Unified Handshake    
    //output wire                ready_to_start,

    // Encryption Lane
    input  wire                enc_start,
    input  wire [127:0]        i_plaintext,
    output wire [127:0]        o_ciphertext,
    output wire                enc_done,

    // Decryption Lane
    input  wire                dec_start,
    input  wire [127:0]        i_ciphertext,
    output wire [127:0]        o_plaintext,
    output wire                dec_done
);

    // --- Core Interconnect Wires ---
    wire [127:0] core_i_pt;  // Data going into core encryption
    wire [127:0] core_o_ct;  // Data coming out of core encryption
    wire [127:0] core_i_ct;  // Data going into core decryption
    wire [127:0] core_o_pt;  // Data coming out of core decryption

    // ----------------------------------------------------------------
    // 1. MODE LOGIC: XORs and Feedback Registers
    // ----------------------------------------------------------------
    generate
        if (MODE == AES_CBC) begin : GEN_MODE_CBC
            reg [127:0] enc_feedback;
            reg [127:0] dec_feedback;
            reg [127:0] dec_buffer;
            reg         iv_ready_reg;

            assign iv_ready = iv_ready_reg;

            wire [127:0] active_enc_fb = iv_load  ? iv_in        : // Priority 1: New IV
                                         enc_done ? o_ciphertext : // Priority 2: Back-to-back Forwarding
                                         enc_feedback;             // Priority 3: Stored Memory

            // 2. For Decryption: Same logic for the IV load.
            wire [127:0] active_dec_fb = iv_load ? iv_in : dec_feedback;

            // --- Path Assignments ---
            assign core_i_pt    = i_plaintext ^ active_enc_fb;
            assign o_ciphertext = core_o_ct;

            assign core_i_ct    = i_ciphertext;
            assign o_plaintext  = core_o_pt ^ active_dec_fb;

            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    enc_feedback       <= 128'h0;
                    dec_feedback       <= 128'h0;
                    dec_buffer         <= 128'h0;
                    iv_ready_reg       <= 1'b0;
                end else if (iv_load) begin
                    enc_feedback       <= iv_in;
                    dec_feedback       <= iv_in;
                    iv_ready_reg       <= 1'b1;
                end else begin
                    // Update registered feedback for the next-next block
                    if (enc_done)  enc_feedback <= o_ciphertext;
                    
                    if (dec_start) dec_buffer   <= i_ciphertext;
                    if (dec_done)  dec_feedback <= dec_buffer;
                end
            end
        end 

        else begin : GEN_MODE_ECB
            // Physical Passthrough (No registers or XORs created)
            assign core_i_pt    = i_plaintext;
            assign o_ciphertext = core_o_ct;
            assign core_i_ct    = i_ciphertext;
            assign o_plaintext  = core_o_pt;

            assign iv_ready     = 1'b1;

            // Suppress unused signal warnings
            wire _unused = &{1'b0, iv_in, iv_load, 1'b0};
        end
    endgenerate

    // ----------------------------------------------------------------
    // 2. ARCHITECTURE SELECTION: Iterative vs Pipelined
    // ----------------------------------------------------------------
    generate
        if (PIPE_DEPTH == 1) begin : ARCH_ITERATIVE
            aes_core_iterative #(
                .SBOX_ARCH (SBOX_ARCH),
                .KEY_BITS  (KEY_BITS),
                .DUPLEX    (DUPLEX)
            ) u_core (
                .clk          (clk),
                .rst_n        (rst_n),
                .key_load     (key_load),
                .key_in       (key_in),
                .key_ready    (key_ready),
                // Encryption Lane
                .enc_start    (enc_start),
                .i_plaintext  (core_i_pt),
                .o_ciphertext (core_o_ct),
                .enc_done     (enc_done),
                // Decryption Lane
                .dec_start    (dec_start),
                .i_ciphertext (core_i_ct),
                .o_plaintext  (core_o_pt),
                .dec_done     (dec_done)
            );
        end
        else begin : ARCH_PIPELINED
            // Future high-performance implementation
            // aes_core_pipelined #(.KEY_BITS(KEY_BITS)...) u_core (...)
        end
    endgenerate

endmodule
