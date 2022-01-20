module ha_gatelevel_tb;

reg a, b;
wire s, c;

ha_gatelevel ha1 (.s(s), .c(c), .a(a), .b(b));

initial
begin
	a = 0; b = 0;
	#5 a = 0; b = 1;
	#5 a = 1; b = 0;
	#5 a = 1; b = 1;
	#5;
end

initial
$monitor ( $time, "a = %b, b = %b, s = %b, c = %b", a, b, s, c);

endmodule