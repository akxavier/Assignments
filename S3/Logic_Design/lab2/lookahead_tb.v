module lookahead_tb;

wire [3:0] s;
wire cout;
reg [3:0] a, b;

integer i, j;

lookahead a1 (.s(s), .cout(cout), .a(a), .b(b));

initial
begin
	{a, b} = 8'b00000000;
	for (i = 1; i < 16; i = i + 1)
	begin
		#5 a = i;
		
		for (j = 1; j < 16; j = j + 1)
			#5 b = j;
	end
end

initial
$monitor ($time, "a = %b, b = %b, cout = %b, s = %b", a, b, cout, s);
		
endmodule