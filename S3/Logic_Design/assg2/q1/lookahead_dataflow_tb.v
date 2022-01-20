module lookahead_dataflow_tb;

wire [3:0] s;
wire cout;
reg [3:0] a, b;

lookahead_dataflow a1 (s, cout, a, b);

initial 
begin
	{a, b} = 6'b010110;
	#5 {a, b} = 6'b110001;
	#5 {a, b} = 6'b011101;
	#5 {a, b} = 6'b101010;
	#5 {a, b} = 6'b010010;
end

initial 
$monitor ($time, "a = %b, b = %b, s = %s, cout = %b", a, b, s, cout);

endmodule