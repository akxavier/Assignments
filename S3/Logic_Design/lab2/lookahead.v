module lookahead (s, cout, a, b);

output [3:0] s;
output cout;
input [3:0] a, b;

reg [2:0] g, p, d;
reg [3:1] c;

always @ (a, b)
begin
	g[0] = a[0] & b[0];
	g[1] = a[1] & b[1];
	g[2] = a[2] & b[2];
	
	p[0] = a[0] ^ b[0];
	p[1] = a[1] ^ b[1];
	p[2] = a[2] ^ b[2];
	
	d[0] = p[0] & 1'b0;
	c[1] = g[0] | d[0]; 

	d[1] = p[1] & c[1];
	c[2] = g[1] | d[1]; 

	d[2] = p[2] & c[2];
	c[3] = g[2] | d[2];
	
end
	
fa fa1 (.s(s[0]), .cout(c[1]), .a(a[0]), .b(b[0]), .c(1'b0));
fa fa2 (.s(s[1]), .cout(c[2]), .a(a[1]), .b(b[1]), .c(c[1]));
fa fa3 (.s(s[2]), .cout(c[3]), .a(a[2]), .b(b[2]), .c(c[2]));
fa fa4 (.s(s[3]), .cout(cout), .a(a[3]), .b(b[3]), .c(c[3]));

endmodule