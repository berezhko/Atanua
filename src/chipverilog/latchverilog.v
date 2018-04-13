module latch(data, clk, out);
    input data;
    input clk;
    output reg out;

always_latch
    if(clk)
        out <= data;

endmodule
