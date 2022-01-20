module nor8_gate
(output out,
input [7:0] a);

nor g1 (out, a[7], a[6], a[5], a[4], a[3], a[2], a[1], a[0]);

endmodule