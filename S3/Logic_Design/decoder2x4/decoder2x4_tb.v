module decoder2x4_tb; 

wire [3:0] out;
reg [1:0] in;

decoder2x4 d1 (.out(out), .in(in));

initial
begin
	in = 2'b00;
	#10 in = 2'b01;
	#10 in = 2'b10;
	#10 in = 2'b11;
	#10 in = 2'b01;
	#10 in = 2'b11;
	#10 in = 2'b00;
	#10;
end

initial
$monitor ($time, "in = %b, out = %b", in, out);

endmodule