module mux_21_gatelevel (y, s, a, b);

output y;
input s, a, b;

wire m, n, s_bar;

nand (s_bar, s, s);

nand (m, s_bar, a);
nand (n, s, b);

nand (y, m, n);

endmodule