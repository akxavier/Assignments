module reg8bit (dout, clk, addr, din);

output [7:0] dout;
input clk;
input [2:0] addr;
input [7:0] din;

wire [7:0] sel, c;

decoder3to8 d1 (.out(sel), .in(addr));

and g1[7:0] (c, sel, clk);

dff1 ff[7:0] (.out(dout), .clk(c), .d(din));

endmodule