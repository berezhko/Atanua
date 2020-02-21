`include "latchverilog.v"

module twolatchverilog (data, clk, out);
    input data;
    input clk;
    output reg out;

wire temp;

latch l1(data, ~clk, temp);
latch l2(temp, clk, out);

endmodule

