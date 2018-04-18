module twoMux4_1 (
    input [3:0] d[0:1],
    input [1:0] s,
    input [1:0] en,
    output reg [1:0] y
);

mux4_1 m1(d[0], s, en[0], y[0]);
mux4_1 m2(d[1], s, en[1], y[1]);

endmodule


module mux4_1 (
    input [3:0] d,
    input [1:0] s,
    input en,
    output y
);

    assign y = (~en) ? d[s] : 0;

endmodule
