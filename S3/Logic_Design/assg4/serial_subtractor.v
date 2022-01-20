module serial_subtractor(A, B, rst, clk, sum);

input [7:0] A, B;
input rst, clk;
output wire [7:0] sum;

reg [3:0] cnt;
reg s, y, Y;

wire [7:0] QA, QB;
wire Run;

parameter G = 1’b0, H = 1’b1;

shift_reg shift_A (A, rst, 1’b1, 1’b0, clk, QA);
shift_reg shift_B (B, rst, 1’b1, 1’b0, clk, QB);
shift_reg shift_sum (8’b0, rst, Run, s, clk, sum);

always @ (QA, QB, y)
case (y)
	G: begin
		s = QA[0] ^ QB[0];
		if (QA[0] & QB[0]) Y = H;
		else Y = G;
	end

	H: begin
		s = QA[0] ~^ QB[0];
		
		if (~QA[0] & ~QB[0]) Y = G;
		else Y = H;
	end

	default: Y = G;
endcase

always @(posedge clk)
	if (rst) y < = G;
	else y < = Y;

always @(posedge clk)
begin
	if (rst) cnt = 8;
	else if (Run) cnt = cnt – 1;
	assign Run = cnt;
end
endmodule