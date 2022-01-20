module dff1_tb;

wire out;
reg clk, d;

dff1 ff1 (.out(out), .clk(clk), .d(d));

always 
begin
	clk = 0;
	#10 clk = 1;
	#10;
end

initial
begin
	d = 1;
	#25 d = 0;
	#10 d = 1;
	#30 d = 0;
	#10 d = 1;
end

initial
#100 $stop;

initial
$monitor ($time, "clk = %b, d = %b, out = %b", clk, d, out);

endmodule