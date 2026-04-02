module aes_top #(
    parameter TARGET = "FPGA",  // FPGA - uses SBOX LUT, ASIC - computes SBOX values on-the-go.
    parameter KEY_BITS = 128,   // 128, 192, 256.
    parameter PIPE_DEPTH = 1,   // PIPELINED DESIGN NOT YET IMPLEMENTED.
    parameter DUPLEX = "FULL"   // HALF-DUPLEX is slower but takes up alot less
                                // space, NOT YET IMPLEMENTED.
)(
    input  wire                clk,
    input  wire                rst_n,
    input  wire                key_load,
    input  wire [KEY_BITS-1:0] key_in,
    input  wire                enc_start,
    input  wire                dec_start,
    input  wire [127:0]        i_plaintext,
    input  wire [127:0]        i_ciphertext,
    output reg  [127:0]        o_plain_text,
    output reg  [127:0]        o_ciphertext,
    output wire                key_ready,
    output reg                 enc_done,
    output reg                 dec_done
);

	localparam [3:0] Nr = 4'((KEY_BITS / 32) + 6);

	wire [127:0] enc_round_key;
    wire [127:0] dec_round_key;
	wire [127:0] enc_round_out;
    wire [127:0] dec_round_out;
	reg  [127:0] enc_state;
    reg  [127:0] dec_state;
	reg  [3:0]   enc_round_num;
    reg  [3:0]   dec_round_num;
	reg          enc_running;
    reg          dec_running;

	aes_key_schedule_iterative #(.KEY_BITS(KEY_BITS)) u_ksi (
	    .clk            (clk),
	    .rst_n          (rst_n),
	    .load           (key_load),
	    .key_in         (key_in),
	    .enc_round_num  (enc_round_num),
        .dec_round_num  (dec_round_num),
	    .enc_round_key  (enc_round_key),
        .dec_round_key  (dec_round_key),
	    .key_ready      (key_ready)
	);

	aes_enc_round #(.KEY_BITS(KEY_BITS)) u_eround (
	    .round_num  (enc_round_num),
	    .state_in   (enc_state),
	    .round_key  (enc_round_key),
	    .state_out  (enc_round_out)
	);

    aes_dec_round #(.KEY_BITS(KEY_BITS)) u_dround (
	    .round_num  (dec_round_num),
	    .state_in   (dec_state),
	    .round_key  (dec_round_key),
	    .state_out  (dec_round_out)
    );

    // ---------------------------------------------------------
    // LANE 1: ENCRYPTION CONTROL
    // ---------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            enc_round_num <= 0;
            enc_running   <= 0;
            enc_done      <= 0;
            o_ciphertext  <= 0;
        end else if (enc_start && key_ready && !enc_running) begin
            // Round 0: Initial XOR with K_0
            enc_state     <= i_plaintext ^ enc_round_key; 
            enc_round_num <= 1;
            enc_running   <= 1;
            enc_done      <= 0;
        end else if (enc_running) begin
            enc_state <= enc_round_out;
            if (enc_round_num == Nr) begin
                o_ciphertext  <= enc_round_out;
                enc_done      <= 1;
                enc_running   <= 0;
                enc_round_num <= 0;
            end else begin
                enc_round_num <= enc_round_num + 1;
            end
        end else begin
            enc_done <= 0; // Clear done pulse
        end
    end

    // ---------------------------------------------------------
    // LANE 2: DECRYPTION CONTROL
    // ---------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dec_round_num <= 0;
            dec_running   <= 0;
            dec_done      <= 0;
            o_plain_text  <= 0;
        end else if (dec_start && key_ready && !dec_running) begin
            // Round 0: Initial XOR with K_Nr
            // Note: dec_round_num is 0, scheduler should provide K_Nr for dec
            dec_state     <= i_ciphertext ^ dec_round_key; 
            dec_round_num <= 1;
            dec_running   <= 1;
            dec_done      <= 0;
        end else if (dec_running) begin
            dec_state <= dec_round_out;
            if (dec_round_num == Nr) begin
                o_plain_text  <= dec_round_out;
                dec_done      <= 1;
                dec_running   <= 0;
                dec_round_num <= 0;
            end else begin
                dec_round_num <= dec_round_num + 1;
            end
        end else begin
            dec_done <= 0; // Clear done pulse
        end
    end

endmodule
