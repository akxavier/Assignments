module demux_18_gatelevel (a, b, c, d, e, f, g, h, s, din);

output a, b, c, d, e, f, g, h;
input [2:0] s;
input din;

wire out1, out2;

demux_12_gatelevel demux1 (.a(out1), .b(out2), .s(s[2]), .din(din));
demux_14_gatelevel demux2 (.a(a), .b(b), .c(c), .d(d), .s(s[1:0]), .din(out1));
demux_14_gatelevel demux3 (.a(e), .b(f), .c(g), .d(h), .s(s[1:0]), .din(out2));

endmodule