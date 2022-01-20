module demux_14_behavioral (a, b, c, d, s, din);

output a, b, c, d;
input [1:0] s;
input din;

wire out1, out2;

demux_12_behavioral demux1 (.a(out1), .b(out2), .s(s[1]), .din(din));
demux_12_behavioral demux2 (.a(a), .b(b), .s(s[0]), .din(out1));
demux_12_behavioral demux3 (.a(c), .b(d), .s(s[0]), .din(out2));

endmodule