module clk_sr_gl (q, q_bar, clk,  r, s);

output q, q_bar;
input r, s, clk;
wire a, b;

nand (a, s, clk);
nand (b, r, clk);
nand (q, a, q_bar);
nand (q_bar, b, q);

endmodule