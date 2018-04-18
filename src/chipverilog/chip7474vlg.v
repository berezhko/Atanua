module Flop7474(d, clk, pre, clr, q, notq);
    input [1:0] d;
    input [1:0] clk;
    input [1:0] pre;
    input [1:0] clr;
    output reg [1:0] q;
    output reg [1:0] notq;

flipflop ff1(d[0], clk[0], pre[0], clr[0], q[0], notq[0]);
flipflop ff2(d[1], clk[1], pre[1], clr[1], q[1], notq[1]);

endmodule



module flipflop(d, clk, pre, clr, q, notq);
    input d;
    input clk;
    input pre;
    input clr;
    output reg q;
    output reg notq;

always_ff @(posedge clk, negedge clr)
    if(~clr) begin
        q <= 0;
        notq <= 1;
    end else if (~pre) begin
        q <= 1;
        notq <= 0;
    end else if (clk) begin
        q <= d;
        notq <= ~d;
    end

endmodule
