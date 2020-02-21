/* verilator lint_off WIDTH */
module tristate_buffer(x, e, y);
    input x;
    input e;
    output y;

assign y = e ? x : 'bz;

endmodule

