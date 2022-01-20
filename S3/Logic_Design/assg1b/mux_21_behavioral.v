module mux_21_behavioral (y, s, a, b);

output reg y;
input s, a, b;

reg s_bar, m, n;

always @ (a, b, s)
begin
	s_bar = ~(s & s);
	
	m = ~(s_bar & a);
	n = ~(s & b);
	
	y = ~(m & n);
end 

endmodule