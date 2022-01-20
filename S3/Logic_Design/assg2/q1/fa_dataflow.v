module fa_dataflow (s, cout, a, b, c);

output s, cout;
input a, b, c;

wire s1, c1, c2;

ha_dataflow ha1 (.s(s1), .c(c1), .a(a), .b(b));
ha_dataflow ha2 (.s(s), .c(c2), .a(s1), .b(c));

assign cout = c1 | c2;

endmodule