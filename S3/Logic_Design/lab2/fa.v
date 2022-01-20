module fa (s, cout, a, b, c);

output s, cout;
input a, b, c;

wire c1, c2, s1;

and g1 (c1, a, b);
xor g2 (s1, a, b);

and g3 (c2, s1, c);
xor g4 (s, s1, c);

or g5 (cout, c1, c2);

endmodule