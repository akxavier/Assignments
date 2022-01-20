module xor_behavioral (out, a, b);

output reg out;
input a, b;

always @ (a, b)
begin
	out = a ^ b;
end 

endmodule