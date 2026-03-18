// CHECK THIS MODULE, SHIT WAS VIBECODED
//
module aes_top #(
    parameter KEY_BITS = 128
)(
    input  wire                clk,
    input  wire                rst_n,
    input  wire                key_load,
    input  wire [KEY_BITS-1:0] key_in,
    input  wire                enc_start,
    input  wire [127:0]        plaintext,
    output reg  [127:0]        ciphertext,
    output reg                 enc_done
);

	localparam Nr = (KEY_BITS / 32) + 6;

	wire [127:0] round_key;
	wire         key_ready;
	wire [127:0] round_out;
	reg  [127:0] state;
	reg  [3:0]   round_cnt;
	reg          running;

	aes_key_schedule #(.KEY_BITS(KEY_BITS)) u_ks (
	    .clk       (clk),
	    .rst_n     (rst_n),
	    .load      (key_load),
	    .key_in    (key_in),
	    .round_num (round_cnt),
	    .round_key (round_key),
	    .key_ready (key_ready)
	);

	aes_round #(.KEY_BITS(KEY_BITS)) u_round (
	    .clk       (clk),
	    .rst_n     (rst_n),
	    .round_cnt (round_cnt),
	    .state_in  (state),
	    .round_key (round_key),
	    .state_out (round_out)
	);

	always @(posedge clk or negedge rst_n) begin
	    if (!rst_n) begin
	        round_cnt <= 0;
	        running   <= 0;
	        enc_done  <= 0;
	    end
	    else if (enc_start && key_ready && !running) begin
	        state     <= plaintext ^ round_key;  // initial AddRoundKey
	        round_cnt <= 1;
	        running   <= 1;
	        enc_done  <= 0;
	    end
	    else if (running) begin
	        state     <= round_out;
	        if (round_cnt == Nr) begin
	            ciphertext <= round_out;
	            enc_done   <= 1;
	            running    <= 0;
	            round_cnt  <= 0;
	        end else begin
	            round_cnt <= round_cnt + 1;
	        end
	    end
	end

endmodule
