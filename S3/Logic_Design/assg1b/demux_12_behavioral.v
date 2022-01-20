module demux_12_behavioral (a, b, s, din);

output reg a, b;
input s, din;

reg out1, out2;

always @ (s, din)
begin
	out1 = ~(~s & din);
	out2 = ~(s & din);

	a = ~(out1 & out1);
	b = ~(out2 & out2);
end

endmodule