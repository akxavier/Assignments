module mux_81_16bit_behavioral (y, s, a, b, c, d, e, f, g, h);

output [15:0] y;
input [15:0] a, b, c, d, e, f, g, h;
input [2:0] s;

wire [15:0] out1, out2;

mux_41_16bit_behavioral mux1 (.y(out1), .s(s[1:0]), .a(a), .b(b), .c(c), .d(d));
mux_41_16bit_behavioral mux2 (.y(out2), .s(s[1:0]), .a(e), .b(f), .c(g), .d(h));

mux_21_16bit_behavioral mux3 (.y(y), .s(s[2]), .a(out1), .b(out2));

endmodule