module clk_sr_behavioral (q, q_bar, clk, r, s);

output reg q, q_bar;
input clk, r, s;
reg a, b;

always @ (s, clk, r)
begin
	a = ~(s & clk);
	b = ~(r & clk);
	q = ~(a & q_bar);
	q_bar = ~(b & q);
end

endmodule