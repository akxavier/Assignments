module shift_reg (dout, clk, din);

output reg [7:0] dout;
input clk;
input [7:0] din;

always @ (negedge clk)
begin
	dout = din;
end

endmodule 