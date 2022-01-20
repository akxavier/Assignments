module fa_dataflow (s, c, a, b, cin);

output s, c;
input a, b, cin;

assign s = a ^ b ^ cin;
assign c = (a & b) | (b & cin) | (cin & a);

endmodule