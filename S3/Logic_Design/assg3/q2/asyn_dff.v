module asyn_dff (q, q_bar, clk, pre, clr, d);

output reg q, q_bar;
input clk, pre, clr, d;
reg a, b;

always @ (posedge clk)
begin
	a = ~(d & clk);
	b = ~(a & clk);
	
	q = ~(a & pre & q_bar);
	q_bar = ~(b & clr & q);
end

endmodule