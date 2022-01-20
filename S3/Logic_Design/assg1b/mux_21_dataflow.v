module mux_21_dataflow (y, s, a, b);

output y;
input s, a, b;

wire s_bar, m, n;

assign s_bar = ~(s & s);

assign m = ~(s_bar & a);
assign n = ~(s & b);

assign y = ~(m & n);

endmodule