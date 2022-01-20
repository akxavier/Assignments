module syn_dff_tb;

wire q, q_bar;
reg clk, pre, clr, d;

syn_dff d1 (.q(q), .q_bar(q_bar), .clk(clk), .pre(pre), .clr(clr), .d(d));

always
begin 
	clk = 0;
	#5 clk = 1;
	#5;
end

always
begin
	pre = 0; clr = 0; d = 0;
	#10 pre = 0; clr = 0; d = 1;
	#10 pre = 0; clr = 1; d = 0;
	#10 pre = 0; clr = 1; d = 1;
	#10 pre = 1; clr = 0; d = 0;
	#10 pre = 1; clr = 0; d = 1;
	#10 pre = 1; clr = 1; d = 0; 
	#10 pre = 1; clr = 1; d = 1;
	#10;
end

initial
#200 $stop;

initial 
$monitor ($time, "clk = %b, pre = %b, clr = %b, d = %b, q = %b, q_bar = %b", clk, pre, clr, d, q, q_bar);

endmodule