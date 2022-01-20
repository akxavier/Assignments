module ALU_1bit_tb;

wire cout, dout;
reg a, b;
reg [2:0] sel;

integer i, j;

ALU_1bit a1 (.cout(cout), .dout(dout), .a(a), .b(b), .sel(sel));

initial
begin
	{a, b} = 2'b00;
	for (i = 1; i <= 3; i = i + 1)
	begin
		sel = 3'b000;
		for (j = 1; j < 5; j = j + 1)
			#5 sel = j;
			
		#5 {a, b} = i;
	end
end

initial
$monitor($time, "a = %b, b = %b, sel = %b, cout = %b, dout = %b", a, b, sel, cout, dout);

endmodule