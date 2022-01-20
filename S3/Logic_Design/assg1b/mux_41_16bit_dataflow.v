module mux_41_16bit_dataflow (y, s1, s0, a, b, c, d);

output [15:0] y;
input [15:0] a, b, c, d;
input s1, s0;

wire [15:0] out1, out2;

mux_21_16bit_dataflow mux1 (.y(out1), .s(s0), .a(a), .b(b));
mux_21_16bit_dataflow mux2 (.y(out2), .s(s0), .a(c), .b(d));
mux_21_16bit_dataflow mux3 (.y(y), .s(s1), .a(out1), .b(out2));

endmodule