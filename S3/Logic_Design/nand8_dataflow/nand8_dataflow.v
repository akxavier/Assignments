module nand8_dataflow (out, a);

output out;
input [7:0] a;

assign out = ~ (a[7] & a[6] & a[5] & a[4] & a[3] & a[2] & a[1] & a[0]);

endmodule