module mult_unsign_tb;

wire [7:0] out;
reg [3:0] x, y;

mult_unsign m1 (.out(out), .x(x), .y(y));

initial
begin
	x = 4'b1001;
	y = 4'b0111;
end

initial
#20 $stop;

initial
$monitor ($time, "x = %b, y = %b, out = %b", x, y, out);

endmodule