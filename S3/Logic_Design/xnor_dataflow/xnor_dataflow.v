module xnor_dataflow (out, x, y);

output out;
input x, y;

assign out = x ~^ y;

endmodule