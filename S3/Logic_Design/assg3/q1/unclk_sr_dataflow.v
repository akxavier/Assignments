module unclk_sr_dataflow (q, q_bar, r, s);

output q, q_bar;
input r, s;

assign q = ~(r | q_bar);
assign q_bar = ~(s | q);

endmodule