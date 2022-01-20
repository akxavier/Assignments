module asyn_d_gl (q, q_bar, clk, pre, clr, d);

output q, q_bar;
input clk, pre, clr, d;
wire a, b;

nand (a, d, clk);
nand (b, a, clk);

nand (q, a, pre, q_bar);
nand (q_bar, b, clr, q);

endmodule