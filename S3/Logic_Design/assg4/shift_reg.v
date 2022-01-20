module shift_reg (R, L, E, w, clk, Q);
parameter n = 4;

input [n –1:0] R;
input L, E, w, clk;
output reg [n –1:0] Q;

integer k;

always @(posedge clk)
if (L)
	Q < = R;
else if (E)
	begin
	for (k = n– 1; k > 0; k = k –1)
		Q[k– 1] < = Q[k];
	Q[n –1] < = w;
	end
endmodule