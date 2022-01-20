module clk_sr_dataflow (q, q_bar, clk, r, s);

output q, q_bar;
input clk, r, s;
wire a, b;

assign a = ~(s & clk);
assign b = ~(r & clk);

assign q = ~(a & q_bar);
assign q_bar = ~(b & q);

endmodule