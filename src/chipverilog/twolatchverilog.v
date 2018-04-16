module flipflip (data, clk, out);
    input data;
    input clk;
    output reg out;

wire temp;

latch l1(data, ~clk, temp);
latch l2(temp, clk, out);

endmodule


module latch(d, c, o);
    input d;
    input c;
    output reg o;

always_latch
    if(c)
        o <= d;

endmodule
