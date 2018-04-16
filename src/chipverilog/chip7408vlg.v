module nand4 (
    input [3:0] a,
    input [3:0] b,
    output reg [3:0] out
);

assign out = (a & b);

endmodule
