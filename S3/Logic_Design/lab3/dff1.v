module dff1 (out, clk, d);

output reg out;
input clk, d;

reg q;


always @ (posedge clk)
begin
	q <= d;
end

always @ (negedge clk)
begin
	out = q;
end

endmodule