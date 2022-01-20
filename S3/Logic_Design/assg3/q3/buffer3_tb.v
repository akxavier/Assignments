module buffer3_tb;

wire out;
reg clk, en, d;

buffer3 b1 (.out(out), .clk(clk), .en(en), .d(d));

always 
begin
	clk = 0;
	#5 clk = 1;
	#5;
end

initial
begin
	en = 0;
	#7 en = 1;
	#15 en = 0;
	#5 en = 1;
end

initial 
begin
	d = 1;
	#12 d = 0;
	#9 d = 1;
	#12 d = 0;
end

initial
#70 $stop;

endmodule