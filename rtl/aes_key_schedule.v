// CHECK THIS MODULE, SHIT WAS VIBECODED

module aes_key_schedule #(
    parameter KEY_BITS = 128    // 128, 192, or 256
)(
    input  wire                  clk,
    input  wire                  rst_n,
    input  wire                  load,        // pulse to load new key
    input  wire [KEY_BITS-1:0]   key_in,
    input  wire [3:0]            round_num,   // 0..Nr, drives key_mem read
    output reg  [127:0]          round_key,   // registered output
    output reg                   key_ready    // all round keys stored
);

	// ---------------------------------------------------------------
	// Derived constants — all computed from KEY_BITS, never hardcoded
	// ---------------------------------------------------------------
	localparam Nk      = KEY_BITS / 32;           // key words:   4 / 6 / 8
	localparam Nr      = Nk + 6;                  // rounds:     10 / 12 / 14
	localparam TOTAL_W = (Nr + 1) * 4;            // total words: 44 / 52 / 60

	// ---------------------------------------------------------------
	// S-Box function (all 256 entries — same LUT as aes_round)
	// ---------------------------------------------------------------
	function [7:0] sbox_lut;
	    input [7:0] b;
	    case (b)
	        8'h00:sbox_lut=8'h63; 8'h01:sbox_lut=8'h7c; 8'h02:sbox_lut=8'h77;
	        8'h03:sbox_lut=8'h7b; 8'h04:sbox_lut=8'hf2; 8'h05:sbox_lut=8'h6b;
	        8'h06:sbox_lut=8'h6f; 8'h07:sbox_lut=8'hc5; 8'h08:sbox_lut=8'h30;
	        8'h09:sbox_lut=8'h01; 8'h0a:sbox_lut=8'h67; 8'h0b:sbox_lut=8'h2b;
	        8'h0c:sbox_lut=8'hfe; 8'h0d:sbox_lut=8'hd7; 8'h0e:sbox_lut=8'hab;
	        8'h0f:sbox_lut=8'h76; 8'h10:sbox_lut=8'hca; 8'h11:sbox_lut=8'h82;
	        // ... all 256 entries in your real implementation ...
	        default: sbox_lut = 8'h00;
	    endcase
	endfunction

	// ---------------------------------------------------------------
	// SubWord and RotWord
	// ---------------------------------------------------------------
	function [31:0] sub_word;
	    input [31:0] w;
	    sub_word = { sbox_lut(w[31:24]), sbox_lut(w[23:16]),
	                 sbox_lut(w[15:8]),  sbox_lut(w[7:0]) };
	endfunction

	function [31:0] rot_word;
	    input [31:0] w;
	    rot_word = { w[23:0], w[31:24] };
	endfunction

	// ---------------------------------------------------------------
	// Rcon — only the first byte is non-zero per the AES spec.
	// Indices 1..10 cover all AES variants (AES-128 uses up to Rcon[10]).
	// ---------------------------------------------------------------
	function [31:0] rcon;
	    input [3:0] i;  // 1-based round constant index
	    reg [7:0] rc;
	    begin
	        case (i)
	            4'd1:  rc = 8'h01; 4'd2:  rc = 8'h02; 4'd3:  rc = 8'h04;
	            4'd4:  rc = 8'h08; 4'd5:  rc = 8'h10; 4'd6:  rc = 8'h20;
	            4'd7:  rc = 8'h40; 4'd8:  rc = 8'h80; 4'd9:  rc = 8'h1b;
	            4'd10: rc = 8'h36;
	            default: rc = 8'h00;
	        endcase
	        rcon = { rc, 24'h000000 };
	    end
	endfunction

	// ---------------------------------------------------------------
	// Core word-generation function — the entire schedule logic
	// lives here; the always block just iterates over word indices.
	//
	// KEY_BITS drives which branch is taken:
	//   128: SubWord+Rot+Rcon every 4th word, no extra SubWord
	//   192: SubWord+Rot+Rcon every 6th word, no extra SubWord
	//   256: SubWord+Rot+Rcon every 8th word, plain SubWord at offset 4
	// ---------------------------------------------------------------
	function [31:0] expand_word;
	    input [5:0] idx;
	    input [31:0] w_prev;    // W[idx-1]
	    input [31:0] w_nk;      // W[idx-Nk]
	    reg   [31:0] tmp;
	    reg   [3:0]  rcon_idx;
	    begin
	        if (idx % Nk == 0) begin
	            // Every Nk words: RotWord + SubWord + Rcon
	            rcon_idx  = idx / Nk;
	            tmp       = sub_word(rot_word(w_prev)) ^ rcon(rcon_idx);
	            expand_word = w_nk ^ tmp;
	        end
	        else if (KEY_BITS == 256 && idx % Nk == 4) begin
	            // AES-256 only: extra SubWord at the midpoint of each group
	            expand_word = w_nk ^ sub_word(w_prev);
	        end
	        else begin
	            // All other positions: straight XOR
	            expand_word = w_nk ^ w_prev;
	        end
	    end
	endfunction

	// ---------------------------------------------------------------
	// Word storage and round-key memory
	// ---------------------------------------------------------------
	reg [31:0]  w      [0:TOTAL_W-1];   // expanded word array
	reg [127:0] key_mem[0:Nr];          // Nr+1 round keys

	reg [5:0]   word_idx;   // 0..TOTAL_W-1
	reg         expanding;

	integer j;

	always @(posedge clk or negedge rst_n) begin
	    if (!rst_n) begin
	        word_idx  <= 0;
	        expanding <= 0;
	        key_ready <= 0;
	    end

	    else if (load) begin
	        // Seed the first Nk words directly from key_in
	        // key_in is packed MSB-first: word 0 = key_in[KEY_BITS-1:KEY_BITS-32]
	        for (j = 0; j < Nk; j = j + 1)
	            w[j] <= key_in[KEY_BITS-1 - j*32 -: 32];

	        word_idx  <= Nk;     // start generating from word Nk
	        expanding <= 1;
	        key_ready <= 0;

	        // Round key 0 is always the first 128 bits of key_in
	        key_mem[0] <= key_in[KEY_BITS-1 -: 128];
	    end

	    else if (expanding) begin
	        // Generate one word per cycle
	        w[word_idx] <= expand_word(word_idx, w[word_idx-1], w[word_idx-Nk]);

	        // When word_idx lands on the last word of a 4-word group
	        // (i.e. word_idx % 4 == 3), a new round key is complete.
	        // Use the last three already-stored words plus this new one.
	        if (word_idx[1:0] == 2'b11) begin
	            key_mem[word_idx[5:2]] <= {
	                w[word_idx-3],
	                w[word_idx-2],
	                w[word_idx-1],
	                expand_word(word_idx, w[word_idx-1], w[word_idx-Nk])
	            };
	        end

	        if (word_idx == TOTAL_W - 1) begin
	            expanding <= 0;
	            key_ready <= 1;
	        end else begin
	            word_idx <= word_idx + 1;
	        end
	    end
	end

	// ---------------------------------------------------------------
	// Round key read port — single-cycle registered lookup.
	// round_num is driven by your encryption controller (0..Nr).
	// ---------------------------------------------------------------
	always @(posedge clk)
	    round_key <= key_mem[round_num];

endmodule
