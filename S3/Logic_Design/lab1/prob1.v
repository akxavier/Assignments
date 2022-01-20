module prob1 (out, x, y, z);

output out;
input x, y, z;

assign out = (x & ~y & ~z) | (x & ~y & z) | (x & y & ~z);

endmodule