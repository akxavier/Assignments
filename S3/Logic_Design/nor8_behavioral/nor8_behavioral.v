module nor8_behavioral (out, a, b, c, d, e, f, g, h);

output reg out;
input a, b, c, d, e, f, g, h;

always @ (a, b, c, d, e, f, g, h)
begin
	out = ~ (a | b | c | d | e | f | g | h);
end 

endmodule