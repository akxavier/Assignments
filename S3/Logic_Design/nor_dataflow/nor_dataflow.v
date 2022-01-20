module nor_dataflow (out, a, b);

output out;
input a, b;

assign out = ~ (a | b);

endmodule