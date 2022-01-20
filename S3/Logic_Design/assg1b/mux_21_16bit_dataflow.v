module mux_21_16bit_dataflow (y, s, a, b);

output [15:0] y;
input [15:0] a, b;
input s;

mux_21_dataflow mux1 [15:0] (.y(y), .s(s), .a(a), .b(b));

endmodule