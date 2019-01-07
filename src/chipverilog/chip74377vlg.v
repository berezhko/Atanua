module register8 (
    input [7:0] d,
    input en,
    input clk,
    output reg [7:0] q
);

always_ff @(posedge clk)
    if (~en)
        q <= d;

endmodule
