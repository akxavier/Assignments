module reg_file (sout, reg_no, write, sin);

output reg [7:0] sout;
input write;
input [1:0] reg_no;
input [7:0] sin;

wire [3:0] sel;
wire [7:0] a1, a2, a3, a4;

decoder d1 (sel, reg_no);

shift_reg r1 (.dout(a1), .clk(sel[0] & write), .din(sin));
shift_reg r2 (.dout(a2), .clk(sel[1] & write), .din(sin));
shift_reg r3 (.dout(a3), .clk(sel[2] & write), .din(sin));
shift_reg r4 (.dout(a4), .clk(sel[3] & write), .din(sin));

always @ (reg_no, a1, a2, a3, a4)
begin
	case (reg_no)
		2'b00: sout = a1;
		2'b01: sout = a2;
		2'b10: sout = a3;
		2'b11: sout = a4;
		default: sout = 8'bxxxxxxxx;
	endcase
end

endmodule