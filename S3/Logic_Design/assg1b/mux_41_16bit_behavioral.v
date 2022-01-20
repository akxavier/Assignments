module mux_41_16bit_behavioral (y, s, a, b, c, d);

output [15:0] y;
input [15:0] a, b, c, d;
input [1:0] s;

wire [15:0] out1, out2;

mux_21_16bit_behavioral mux1 (.y(out1), .s(s[0]), .a(a), .b(b));
mux_21_16bit_behavioral mux2 (.y(out2), .s(s[0]), .a(c), .b(d));
mux_21_16bit_behavioral mux3 (.y(y), .s(s[1]), .a(out1), .b(out2));

endmodule