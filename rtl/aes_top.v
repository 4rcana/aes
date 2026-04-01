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
    input  wire [127:0]        plaintext,
    output wire                key_ready,
    output reg  [127:0]        ciphertext,
    output reg                 enc_done
);

	localparam [3:0] Nr = 4'((KEY_BITS / 32) + 6);

	wire [127:0] enc_round_key;
//	wire         key_ready;     VERILATOR NEEDS TO SEE THIS
	wire [127:0] enc_round_out;
	reg  [127:0] enc_state;
	reg  [3:0]   enc_round_num;
    reg  [3:0]   dec_round_num;
	reg          running;

	aes_key_schedule_iterative #(.KEY_BITS(KEY_BITS)) u_ksi (
	    .clk            (clk),
	    .rst_n          (rst_n),
	    .load           (key_load),
	    .key_in         (key_in),
	    .enc_round_num  (enc_round_num),
        .dec_round_num  (dec_round_num),
	    .enc_round_key  (enc_round_key),
	    .key_ready      (key_ready)
	);

	aes_enc_round #(.KEY_BITS(KEY_BITS)) u_round (
	    .round_num  (enc_round_num),
	    .state_in   (enc_state),
	    .round_key  (enc_round_key),
	    .state_out  (enc_round_out)
	);

	always @(posedge clk or negedge rst_n) begin
	    if (!rst_n) begin
	        enc_round_num   <= 0;
	        running         <= 0;
	        enc_done        <= 0;
	    end
	    else if (enc_start && key_ready && !running) begin
	        enc_state           <= plaintext ^ enc_round_key;  // initial AddRoundKey
	        enc_round_num   <= 1;
	        running         <= 1;
	        enc_done        <= 0;
	    end
	    else if (running) begin
	        enc_state   <= enc_round_out;
	        if (enc_round_num == Nr) begin
	            ciphertext      <= enc_round_out;
	            enc_done        <= 1;
	            running         <= 0;
	            enc_round_num   <= 0;
	        end else begin
	            enc_round_num   <= enc_round_num + 1;
	        end
	    end
	end

endmodule
