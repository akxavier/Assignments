module demux_12_dataflow (a, b, s, din);

output a, b;
input s, din;

wire out1, out2;

assign out1 = ~(~s & din);
assign out2 = ~(s & din);

assign a = ~(out1 & out1);
assign b = ~(out2 & out2);

endmodule