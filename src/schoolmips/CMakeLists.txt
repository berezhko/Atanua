set(VERILOG_CHIPS
    marsohod
)

verilator_create_module(schoolmips "${VERILOG_CHIPS}")
