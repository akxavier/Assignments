module fa_gatelevel_tb;

wire s, cout;
reg a, b, c;
integer i;

fa_gatelevel fa1 (.s(s), .cout(cout), .a(a), .b(b), .c(c));

initial
begin

{a, b, c} = 3'b000;

for (i = 1; i < 8; i = i + 1)
	#10 {a, b, c} = i;
end

initial
$monitor ($time, "a = %b, b = %b, c = %b, s = %b, cout = %b", a, b, c, s, cout);

endmodule