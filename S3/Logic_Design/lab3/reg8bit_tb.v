module reg8bit_tb;

wire [7:0] dout;
reg [2:0] addr;
reg clk;
reg [7:0] din;

reg8bit r1 (.dout(dout), .addr(addr), .clk(clk), .din(din));

always 
begin
	clk = 0; 
	#5 clk = 1;
	#5;
end

initial
#100 $stop;

initial
$monitor ($time, "clk = %b, addr = %b, din = %b, dout = %b", clk, addr, din, dout);

initial
begin
	din = 8'b00001100; addr = 3'b001;
	#10 addr = 3'b101;
	#10 addr = 3'b111;
	#10 addr = 3'b000;
	#10 addr = 3'b010;
	#10 addr = 3'b011;
	#10 addr = 3'b100;
	#10 addr = 3'b110;
	#10 din = 8'b00101010; din = 3'b010;
end

endmodule