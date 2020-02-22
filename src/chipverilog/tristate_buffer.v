module tristate_buffer(x, e, y);
    input x;
    input e;
    inout y;

assign y = e ? x : 1'bz;

endmodule

