module clk_sr_gl_tb;

reg clk, r, s;
wire q, q_bar;

clk_sr_gl sr1 (.q(q), .q_bar(q_bar), .clk(clk), .r(r), .s(s));

always
begin
clk = 1;
#30 clk = 0;
#30;
end

initial
#100 $stop;

always 
begin
	s = 0; r = 0;
	#10 s = 0; r = 1;
	#10 s = 1; r = 0;
	#10;
end

initial
$monitor ($time, "clk = %b, s = %b, r = %b, q = %b, q_bar = %b", clk, s, r, q, q_bar);

endmodule