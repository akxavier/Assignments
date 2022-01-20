module prob2 (y1, y2, y3, x1, x2, S);

output reg y1, y2, y3;
input x1, x2;
input [2:0] S;

always @ *

begin 

case (S)
	3'b000: {y1, y2} = {x1, x2};
	3'b001: {y1, y3} = {x1, x2};
	3'b010: {y1, y2} = {x2, x1};
	3'b011: {y2, y3} = {x1, x2};
	3'b100: {y1, y3} = {x2, x1};
	3'b101: {y2, y3} = {x2, x1};
endcase

end

endmodule
