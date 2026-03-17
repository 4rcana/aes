module aes_round_stream (
    input  wire        clk,
    input  wire        rst_n,
    input  wire        start,
    input  wire [7:0]  byte_in,
    input  wire [7:0]  round_key,
    output reg  [7:0]  byte_out,
    output reg         valid_out,
    output reg         done
);

    wire        sb_byte;
    wire [31:0] mc_col;
    reg  [7:0]  column_buf[0:3];
    reg  [1:0]  row_idx;

    // --------------------------
    // SubBytes stage (combinational)
    // --------------------------

    sbox u_box (
        .byte_in(byte_in),
        .byte_out(byte_out)
    )

    // --------------------------
    // MixColumns function
    // --------------------------

    function [31:0] MixColumns;
        input [7:0] b0;
        input [7:0] b1;
        input [7:0] b2;
        input [7:0] b3;
        
        reg [7:0] result_bytes [0:3];

        begin
        result_bytes[0] = xtime(b0) ^ (xtime(b1) ^ b1) ^ b2 ^ b3;
        result_bytes[1] = b0 ^ xtime(b1) ^ (xtime(b2) ^ b2) ^ b3;
        result_bytes[2] = b0 ^ b1 ^ xtime(b2) ^ (xtime(b3) ^ b3);
        result_bytes[3] = (xtime(b0) ^ b0) ^ b1 ^ b2 ^ xtime(b3);

        MixColumns = {result_bytes[0], result_bytes[1],
                      result_bytes[2], result_bytes[3]};
        end
    endfunction

    // GF(2^8) multiplication by 2
    function [7:0] xtime;
        input [7:0] x;
        begin
            xtime = (x << 1) ^ (8'h1b & {8{x[7]}});
        end
    endfunction

    // --------------------------
    // Finite-state machine
    // --------------------------

    always @ (posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            byte_cnt <= 0;
            row_idx <= 0;
            for (integer i=0; i<4; i=i+1)
                column_buf[i] = 8'b0;
            valid_out <= 0;
            done <= 0;
        end else begin
            if (start) begin
                column_buf[row_idx] <= sb_byte;
                if (row_idx != 3) begin     // wait for full column
                    row_idx <= row_idx + 1;
                end else begin              // mix columns
                    mc_col = MixColumns(column_buf[0], column_buf[1],
                                        column_buf[2], column_buf[3])
                    row_idx <= 0;
                end
            end
        end
    end

endmodule
