module demux_12_gatelevel (a, b, s, din);

output a, b;
input s, din;

wire s_bar, out1, out2;

nand g1 (s_bar, s, s);

nand g2 (out1, s_bar, din);
nand g3 (out2, s, din);
nand g4 (a, out1, out1);
nand g5 (b, out2, out2);

endmodule