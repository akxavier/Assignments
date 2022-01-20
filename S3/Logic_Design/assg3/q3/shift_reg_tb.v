module shift_reg_tb;

wire [7:0] dout;
reg clk;
reg [7:0] din;

shift_reg r1 (.dout(dout), .clk(clk), .din(din));

always 
begin
	clk = 0;
	#10 clk = 1;
	#10;
end

initial
begin
	din = 8'b00000000;
	#20 din = 8'b01110100;
	#20 din = 8'b01000011;
	#20 din = 8'b11100101;
	#20 din = 8'b01010101;
	#20 din = 8'b11010100;
	#20 din = 8'b10101101;
	#20 din = 8'b11110110;
	#20 din = 8'b11000001;
	#20 din = 8'b10101010;
	#20;
end

initial
#120 $stop;

initial
$monitor ($time, "clk = %b, din = %b, dout = %b", clk, din, dout);

endmodule