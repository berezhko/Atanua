set(VERILOG_CHIPS
    andverilog
    chip7400vlg
    chip7402vlg
    chip7404vlg
    chip7408vlg
    chip7411vlg
    chip74153vlg
    chip7421vlg
    chip7432vlg
    chip74377vlg
    chip7474vlg
    chip7486vlg
    ffverilog
    latchverilog
    orverilog
    twolatchverilog
)

verilator_create_module(chipverilog "${VERILOG_CHIPS}")
