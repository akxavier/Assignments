module not_behavioral (out, in);

output reg out;
input in;

always @ (in)
begin
	out = ~in;
end

endmodule