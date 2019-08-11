enable_language(C)

add_library(8051 SHARED "")

target_sources(8051
  PRIVATE
    core.c
    disasm.c
    opcodes.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/emu8051.h
  )

target_include_directories(8051
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
