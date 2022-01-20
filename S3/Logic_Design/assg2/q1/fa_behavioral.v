module fa_behavioral (s, cout, a, b, c);

output s, cout;
input a, b, c;

reg cout;

wire s1, c1, c2;

ha_behavioral ha1 (.s(s1), .c(c1), .a(a), .b(b));
ha_behavioral ha2 (.s(s), .c(c2), .a(s1), .b(c));

always @ (c1, c2)
	cout = c1 | c2;
	
endmodule