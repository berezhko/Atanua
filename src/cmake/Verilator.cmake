macro(verilator_add)
    find_path(VERILATOR_INCLUDE verilated.h
        PATH_SUFFIXES verilator/include
        HINTS /usr/share
    )

    include_directories(SYSTEM ${VERILATOR_INCLUDE})

    set(VERILATOR_SOURCE_LIST
        verilated.cpp
        #verilated_save.cpp
        #verilated_vcd_c.cpp
        #verilated_vcd_sc.cpp
    )


    set(VERILATOR_SOURCES "")
    foreach(src ${VERILATOR_SOURCE_LIST})
        set(VERILATOR_SOURCES ${VERILATOR_SOURCES} ${VERILATOR_INCLUDE}/${src})
    endforeach()

    add_library(verilator SHARED ${VERILATOR_SOURCES})

    set(VERILATOR_LIBRARY verilator)
    set_target_properties(
        verilator
        PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall"
    )
endmacro()

macro(verilator_create_sources verilog_chip)
    set(VERILOG_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/src")

    set(VERILATOR_INCS "")
    set(VERILATOR_ARGS "")

    # Additional includes
    if(${ARGC} GREATER 2)
        foreach(inc ${ARGV2})
            set(VERILATOR_INCS ${VERILATOR_INCS} -I${inc})
        endforeach()
    endif()

    # Verilator additional arguments
    if(${ARGC} GREATER 3)
        set(VERILATOR_ARGS "${ARGV3}")
    endif()

    set(verilog_sources "")
    foreach(source ".cpp" "__Syms.cpp" ".h" "__Syms.h")
        set(verilog_sources  ${verilog_sources} "V${verilog_chip}${source}")
    endforeach()
    #set(verilog_sources  ${verilog_sources} "../${verilog_chip}.cpp")

    set(VERILOG_OUTPUT_SOURCES "")
    foreach(source ${verilog_sources})
        set(VERILOG_OUTPUT_SOURCES ${VERILOG_OUTPUT_SOURCES}
            ${VERILOG_OUTPUT_DIR}/${source})
    endforeach()

    add_custom_command(
        OUTPUT ${VERILOG_OUTPUT_SOURCES}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${VERILOG_OUTPUT_DIR}
        COMMAND verilator_bin ${VERILATOR_ARGS} ${VERILATOR_INCS}
            -Mdir ${VERILOG_OUTPUT_DIR}
            -cc ${verilog_chip}.v
        COMMAND ${CMAKE_COMMAND} -E remove ${VERILOG_OUTPUT_DIR}/*.mk
        COMMAND ${CMAKE_COMMAND} -E remove ${VERILOG_OUTPUT_DIR}/*.d
        COMMAND ${CMAKE_COMMAND} -E remove ${VERILOG_OUTPUT_DIR}/*.dat
        MAIN_DEPENDENCY ${verilog_chip}.v
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating C++ source ${verilog_chip}"
    )
endmacro()

macro(verilator_create_module verilog_module verilog_chips)
    set(VOS "")
    foreach(chip ${verilog_chips})
        verilator_create_sources(${chip})
        set(VOS ${VOS} ${VERILOG_OUTPUT_SOURCES})
        set(VOS ${VOS} "${chip}.cpp")
    endforeach()

    add_library(${verilog_module} SHARED ${VOS})

    target_include_directories(${verilog_module}
      PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
        ${CMAKE_CURRENT_LIST_DIR}/../include
        ${VERILOG_OUTPUT_DIR}
      )
endmacro()
