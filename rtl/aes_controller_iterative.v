// ----------------------------------------------------------------
//              AES Iterative Controller (Generic)
// ----------------------------------------------------------------
module aes_controller_iterative #(
    parameter [63:0] DIRECTION = "FORWARD",
    parameter        KEY_BITS  = 128
)(
    input  wire       clk,
    input  wire       rst_n,
    
    // Handshaking
    input  wire       start,      
    input  wire       key_ready,      
    
    // Control Outputs
    output reg  [3:0] round_num,  
    output wire       init_cycle, 
    output reg        busy,       
    output wire       done        
);

    localparam [3:0] Nr = 4'((KEY_BITS / 32) + 6);

    assign init_cycle = start && key_ready && !busy;

    assign done = (busy && (round_num == Nr));

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            round_num <= 4'd0;
            busy      <= 1'b0;
        end 
        else if (init_cycle) begin
            round_num <= 4'd1;
            busy      <= 1'b1;
        end 
        else if (busy) begin
            if (round_num == Nr) begin 
                round_num <= 4'd0;
                busy      <= 1'b0;
            end else begin
                round_num <= round_num + 4'd1;
            end
        end
    end
endmodule
