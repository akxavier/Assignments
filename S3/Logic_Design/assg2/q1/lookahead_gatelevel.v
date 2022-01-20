module lookahead_gatelevel (s, cout, a, b);

output [3:0] s;
output cout;
input [3:0] a, b;

wire [2:0] g, p, d;
wire [3:1] c;

and (g[0], a[0], b[0]);
and (g[1], a[1], b[1]);
and (g[2], a[2], b[2]);

xor (p[0], a[0], b[0]);
xor (p[1], a[1], b[1]);
xor (p[2], a[2], b[2]);

and (d[0], p[0], 1'b0);
and (d[1], p[1], c[1]);
and (d[2], p[2], c[2]);

or (c[1], g[0], d[0]);
or (c[2], g[1], d[1]);
or (c[3], g[2], d[2]); 

fa_gatelevel fa1 (.s(s[0]), .cout(c[1]), .a(a[0]), .b(b[0]));
fa_gatelevel fa2 (.s(s[1]), .cout(c[2]), .a(a[1]), .b(b[1]));
fa_gatelevel fa3 (.s(s[2]), .cout(c[3]), .a(a[2]), .b(b[2]));
fa_gatelevel fa4 (.s(s[3]), .cout(cout), .a(a[3]), .b(b[3]));

endmodule