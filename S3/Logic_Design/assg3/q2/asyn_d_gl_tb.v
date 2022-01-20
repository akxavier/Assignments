module asyn_d_gl_tb;

wire q, q_bar;
reg clk, pre, clr, d;

asyn_d_gl d1 (.clk(clk), .pre(pre), .clr(clr), .d(d), .q(q), .q_bar(q_bar));

always 
begin
clk = 0;
#30 clk = 1;
#30;
end

initial
#100 $stop;

initial
begin
	pre = 0; clr = 1; d = 0;
	#5 pre = 0; clr = 1; d = 1;
	#5 pre = 1; clr = 0; d = 0;
	#5 pre = 1; clr = 0; d = 1;
	#5 pre = 1; clr = 1; d = 0;
	#5 pre = 1; clr = 1; d = 1;
	#5 pre = 0; clr = 1; d = 0;
	#5 pre = 0; clr = 1; d = 1;
	#5 pre = 1; clr = 0; d = 0;
	#5 pre = 1; clr = 0; d = 1;
	#5 pre = 1; clr = 1; d = 0;
	#5 pre = 1; clr = 1; d = 1;
	#5;
end

initial 
$monitor ($time, "clk = %b, pre = %b, clr = %b, d = %b, q = %b, q_bar = %b", clk, pre, clr, d, q, q_bar);
endmodule