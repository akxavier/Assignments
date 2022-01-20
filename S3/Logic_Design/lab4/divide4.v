module divide4 (out, in);

output [3:0] out;
input [3:0] in;

assign out = in >> 2;

endmodule