module ha_dataflow (s, c, a, b);

output s, c;
input a, b;

assign s = a ^ b,
	c = a & b;
	
endmodule