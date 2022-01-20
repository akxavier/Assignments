module mult_seq (out, M, N);

output reg [7:0] out;
input [3:0] M, N;

reg C;
reg [3:0] A, Q;

integer n;

initial A = 4'b0000;

initial
begin
	C = 1'b0;
	Q = N;

	for (n = 4; n != 0; n = n - 1)
	begin
		if (Q[0] == 1)
			{C, A} = A + M;
			
		{C, A, Q} = {C, A, Q} >> 1;
	end
	
	out = {A, Q};
end

endmodule