module array_of_16_inverters_behavioral (out, in);

output reg [15:0] out;
input [15:0] in;

always @ (in)
begin
	out[0] = ~in[0];
	out[1] = ~in[1];
	out[2] = ~in[2];
	out[3] = ~in[3];
	out[4] = ~in[4];
	out[5] = ~in[5];
	out[6] = ~in[6];
	out[7] = ~in[7];
	out[8] = ~in[8];
	out[9] = ~in[9];
	out[10] = ~in[10];
	out[11] = ~in[11];
	out[12] = ~in[12];
	out[13] = ~in[13];
	out[14] = ~in[14];
	out[15] = ~in[15];
end

endmodule