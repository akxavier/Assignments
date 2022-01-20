module fa_tb;

wire s, cout;
reg a, b, c;

fa fa1 (.s(s), .cout(cout), .a(a), .b(b), .c(c));

initial
begin
	a = 0; b = 0; c = 0;
	#5 a = 0; b = 0; c = 1;
	#5 a = 0; b = 1; c = 0;
	#5 a = 0; b = 1; c = 1;
	#5 a = 1; b = 0; c = 0;
	#5 a = 1; b = 0; c = 1; 
	#5 a = 1; b = 1; c = 0;
	#5 a = 1; b = 1; c = 1;
	#5;
end

initial 
$monitor ($time, "a = %b, b = %b, c = %b, cout = %b, s = %b", a, b, c, cout, s);

endmodule