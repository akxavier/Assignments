module unclk_sr_gl (q, q_bar, s, r);

output q, q_bar;
input r, s;

nor (q, r, q_bar);
nor (q_bar, s, q);

endmodule