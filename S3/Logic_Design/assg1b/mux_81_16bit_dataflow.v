module mux_81_16bit_dataflow (y, s2, s1, s0, a, b, c, d, e, f, g, h);

output [15:0] y;
input [15:0] a, b, c, d, e, f, g, h;
input s2, s1, s0;

wire [15:0] out1, out2;

mux_41_16bit_dataflow mux1 (.y(out1), .s1(s1), .s0(s0), .a(a), .b(b), .c(c), .d(d));
mux_41_16bit_dataflow mux2 (.y(out2), .s1(s1), .s0(s0), .a(e), .b(f), .c(g), .d(h));

mux_21_16bit_dataflow mux3 (.y(y), .s(s2), .a(out1), .b(out2));

endmodule