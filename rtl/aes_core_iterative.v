// ----------------------------------------------------------------
//              AES Iterative Core (Full/Half Duplex)
// ----------------------------------------------------------------
module aes_core_iterative #(
    parameter [63:0] SBOX_IMPL = "LUT",    // "LUT", "CANRIGHT"
    parameter        KEY_BITS  = 128,      // 128, 192, 256
    parameter [63:0] DUPLEX    = "FULL"    // "FULL" or "HALF"
)(
    input  wire                clk,
    input  wire                rst_n,
    
    // Key Interface
    input  wire                key_load,
    input  wire [KEY_BITS-1:0] key_in,
    output wire                key_ready,

    // Encryption Lane
    input  wire                enc_start,
    input  wire [127:0]        i_plaintext,
    output reg  [127:0]        o_ciphertext,
    output reg                 enc_done,

    // Decryption Lane
    input  wire                dec_start,
    input  wire [127:0]        i_ciphertext,
    output reg  [127:0]        o_plaintext,
    output reg                 dec_done
);

    localparam [3:0] Nk = 4'(KEY_BITS / 32);
    localparam [3:0] Nr = Nk + 4'd6;

    generate
        if (DUPLEX == "FULL") begin : ARCH_FULL
            // Internal Registers
            reg  [127:0] enc_state, dec_state;
            
            // Control Wires
            wire [3:0]   enc_round_num,     dec_round_num;
            wire         enc_init,          dec_init;
            wire         enc_busy,          dec_busy;
            wire         enc_done_pulse,    dec_done_pulse;

            // Datapath Wires
            wire [127:0] enc_round_key,     dec_round_key;
            wire [127:0] enc_round_out,     dec_round_out;

            // Unified Scheduler in FULL mode
            aes_key_scheduler #(
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL),
                .DUPLEX(DUPLEX)
            ) u_ksi (
                .clk(clk),
                .rst_n(rst_n),
                .key_load(key_load),
                .key_in(key_in),
                .key_ready(key_ready),
                // Port A: Mapped to Encryption
                .round_num_a(enc_round_num), 
                .mode_a(1'b0),              // 0: FORWARD
                .key_out_a(enc_round_key),
                // Port B: Mapped to Decryption
                .round_num_b(dec_round_num), 
                .key_out_b(dec_round_key)
            );

            // Forward Round
            aes_round_generic #(
                .DIRECTION("FORWARD"),
                .KEY_BITS(KEY_BITS),
                .SBOX_IMPL(SBOX_IMPL)
            ) u_ernd (
                .round_num(enc_round_num), 
                .in(enc_state),
                .round_key(enc_round_key),
                .mode(1'b0),
                .out(enc_round_out)
            );

            aes_iterative_controller #(
                .DIRECTION ("FORWARD"),
                .KEY_BITS  (KEY_BITS) 
            ) ctrl_enc (
                .clk(clk),
                .rst_n(rst_n),
                .start(enc_start),
                .key_ready(key_ready),
                .round_num(enc_round_num),
                .init_cycle(enc_init),
                .busy(enc_busy),
                .done(enc_done_pulse)
            );

            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    enc_state    <= 128'b0;
                    o_ciphertext <= 128'b0;
                    enc_done     <= 1'b0;
                end else begin
                    if (enc_init)       enc_state <= i_plaintext ^ enc_round_key;
                    else if (enc_busy)  enc_state <= enc_round_out;
                    
                    if (enc_done_pulse) o_ciphertext <= enc_round_out;
                    enc_done <= enc_done_pulse; // Transmit pulse to port
                end
            end

            // Inverse Round
            aes_round_generic #(
                .DIRECTION("INVERSE"),
                .KEY_BITS(KEY_BITS),
                .SBOX_IMPL(SBOX_IMPL)
            ) u_drnd (
                .round_num(dec_round_num),
                .in(dec_state),
                .round_key(dec_round_key),
                .mode(1'b1),
                .out(dec_round_out)
            );

            aes_iterative_controller #(
                .DIRECTION ("INVERSE"),
                .KEY_BITS  (KEY_BITS)
            ) ctrl_dec (
                .clk(clk),
                .rst_n(rst_n),
                .start(dec_start),
                .key_ready(key_ready),
                .round_num(dec_round_num),
                .init_cycle(dec_init),
                .busy(dec_busy),
                .done(dec_done_pulse)
            );

            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    dec_state    <= 128'b0;
                    o_plaintext  <= 128'b0;
                    dec_done     <= 1'b0;
                end else begin
                    if (dec_init)       dec_state <= i_ciphertext ^ dec_round_key;
                    else if (dec_busy)  dec_state <= dec_round_out;
                    
                    if (dec_done_pulse) o_plaintext <= dec_round_out;
                    dec_done <= dec_done_pulse; // Transmit pulse to port
                end
            end
    end

        else begin : ARCH_HALF
            // Internal Registers
            reg [127:0]  shared_state;
            reg          mode_reg; 

            // Control Wires
            wire [3:0]   shared_round_num;
            wire         shared_init;
            wire         shared_busy;
            wire         shared_done_pulse;

            // Datapath Wires
            wire [127:0] shared_round_key;
            wire [127:0] shared_round_out;
            
            // Key Scheduler needs to know mode without delay
            wire current_op_mode = shared_busy ? mode_reg : dec_start;

            // Key Scheduler
            aes_key_scheduler #(
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL),
                .DUPLEX(DUPLEX)
            ) u_ksi (
                .clk(clk),
                .rst_n(rst_n),
                .key_load(key_load),
                .key_in(key_in),
                .key_ready(key_ready),
                .round_num_a(shared_round_num),
                .mode_a(current_op_mode),
                .key_out_a(shared_round_key),
                // Unused
                .round_num_b(4'd0), .key_out_b()
            );

            aes_iterative_controller #(
                .DIRECTION ("SHARED"),
                .KEY_BITS  (KEY_BITS)
            ) ctrl_shared (
                .clk(clk),
                .rst_n(rst_n),
                .start(enc_start || dec_start),
                .key_ready(key_ready),
                .round_num(shared_round_num),
                .init_cycle(shared_init),
                .busy(shared_busy),
                .done(shared_done_pulse)
            );

            // Round Logic (Round logic happens in cycles AFTER start, so mode_reg is fine)
            aes_round_generic #(
                .DIRECTION("SHARED"), 
                .KEY_BITS(KEY_BITS), 
                .SBOX_IMPL(SBOX_IMPL)
            ) u_shared_rnd (
                .round_num(shared_round_num), 
                .in(shared_state),
                .round_key(shared_round_key), 
                .mode(mode_reg),
                .out(shared_round_out)
            );

            always @(posedge clk or negedge rst_n) begin
                if (!rst_n) begin
                    shared_state <= 128'h0;
                    mode_reg     <= 1'b0;
                    o_ciphertext <= 128'h0;
                    o_plaintext  <= 128'h0;
                    enc_done     <= 1'b0;
                    dec_done     <= 1'b0;
                end else begin
                    // Initial Cycle (Round 0)
                    if (shared_init) begin
                        mode_reg     <= dec_start; 
                        shared_state <= (current_op_mode ? i_ciphertext : i_plaintext) ^ shared_round_key;
                        enc_done     <= 1'b0;
                        dec_done     <= 1'b0;
                    end 
                    // Iterative Processing (Rounds 1-Nr)
                    else if (shared_busy) begin
                        shared_state <= shared_round_out;
                    end

                    // Completion Logic (Latching Result and Pulsing Done)
                    if (shared_done_pulse) begin
                        if (mode_reg) begin
                            o_plaintext <= shared_round_out;
                            dec_done     <= 1'b1;
                        end else begin
                            o_ciphertext <= shared_round_out;
                            enc_done     <= 1'b1;
                        end
                    end else if (!shared_init) begin
                        // Clear done pulses if we aren't finishing or starting
                        enc_done <= 1'b0;
                        dec_done <= 1'b0;
                    end
                end
            end
        end
    endgenerate

endmodule
