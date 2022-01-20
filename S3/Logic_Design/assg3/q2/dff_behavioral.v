module dff_behavioral (q, q_bar, clk, d);

output reg q, q_bar;
input clk, d;

always @ (posedge clk)
begin
	q <= d;
	q_bar <= ~d;
end

endmodule