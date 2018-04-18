module and3 (
    input [3:0] a,
    input [3:0] b,
    input [3:0] c,
    output reg [3:0] out
);

assign out = (a & b & c);

endmodule
