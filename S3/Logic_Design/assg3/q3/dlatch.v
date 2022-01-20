module dlatch (q, q_bar, clk, d);

output q, q_bar;
input clk, d;

wire a, b;

nand (a, d, clk);
nand (b, a, clk);

nand (q, a, q_bar);
nand (q_bar, b, q);

endmodule