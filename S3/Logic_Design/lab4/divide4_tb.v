module divide4_tb;

wire [3:0] out;
reg [3:0] in;

divide4 d1 (.out(out), .in(in));

initial
begin
	in = 4'b1010;
	#10 in = 4'b1000;
	#10 in = 4'b0100;
	#10 $stop;
end

initial
$monitor ($time, "in = %b, out = %b", in, out);

endmodule