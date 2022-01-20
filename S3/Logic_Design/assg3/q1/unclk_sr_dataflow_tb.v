module unclk_sr_dataflow_tb;

wire q, q_bar;
reg r, s;

unclk_sr_dataflow sr1 (.q(q), .q_bar(q_bar), .r(r), .s(s));

initial
begin
s = 1; r = 0;
#10 s = 0; r = 1;
#10 s = 0; r = 0;
#10;
end

initial 
$monitor ($time, "s = %b, r = %b, q = %b, q_bar = %b", s, r, q, q_bar);

endmodule