module unclk_sr_behavioral (q, q_bar, r, s);

output reg q, q_bar;
input r, s;

always @ (r, s)
begin
	q = ~(r | q_bar);
	q_bar = ~(s | q);
end

endmodule