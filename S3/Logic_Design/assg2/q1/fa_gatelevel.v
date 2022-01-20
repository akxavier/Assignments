module fa_gatelevel (s, cout, a, b, c);

output s, cout;
input a, b, c;

wire c1, s1, c2;

ha_gatelevel ha1 (.s(s1), .c(c1), .a(a), .b(b));
ha_gatelevel ha2 (.s(s), .c(c2), .a(s1), .b(c));

or g1 (cout, c1, c2);

endmodule