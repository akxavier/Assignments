module ha_gatelevel (s, c, a, b);

output s, c;
input a, b;

xor g1 (s, a, b);
and g2 (c, a, b);

endmodule