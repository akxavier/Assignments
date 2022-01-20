module buffer3 (out, clk, en, d);

output reg out;
input clk, en, d;

wire q;

d_latch l1 (.q(q), .clk(clk), .d(d));

always @ (en, q)
begin
	if (en)
		out = q;
end

endmodule