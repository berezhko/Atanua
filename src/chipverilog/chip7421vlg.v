module and4 (
    input [1:0] a,
    input [1:0] b,
    input [1:0] c,
    input [1:0] d,
    output reg [1:0] out
);

assign out = (a & b & c & d);

endmodule
