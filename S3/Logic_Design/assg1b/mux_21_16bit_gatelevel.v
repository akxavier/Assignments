module mux_21_16bit_gatelevel (y, s, a, b);

output [15:0] y;
input [15:0] a, b;
input s;

mux_21_gatelevel mux1 [15:0] (.y(y), .s(s), .a(a), .b(b));

endmodule 