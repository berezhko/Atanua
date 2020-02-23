
module marsohod(
      input       CLK100MHZ,
      input       KEY0,
      input       KEY1,
      output      [10:0]  LED

);

    // wires & inputs
    wire          clk;
    wire          clkIn     =  CLK100MHZ;
    wire          rst_n     =  KEY0;
    wire          clkEnable =  ~KEY1;
    wire [ 31:0 ] regData;

    //cores
    sm_top sm_top
    (
        .clkIn      ( clkIn     ),
        .rst_n      ( rst_n     ),
        .clkDevide  ( 4'b0001   ),
        .clkEnable  ( clkEnable ),
        .clk        ( clk       ),
        .regAddr    ( 5'b00010  ),
        .regData    ( regData   )
    );

    //outputs
    assign LED[0]   = clk;
    assign LED[10:1] = regData[9:0];

endmodule
