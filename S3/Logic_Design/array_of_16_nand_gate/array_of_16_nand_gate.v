module array_of_16_nand_gate
(output [15:0] out,
input [15:0] a, b);

nand g[15:0] (out, a, b);

endmodule 