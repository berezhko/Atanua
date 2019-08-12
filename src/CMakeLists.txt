cmake_minimum_required(VERSION 3.12)
project(Atanua VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/modules)

find_package(PkgConfig REQUIRED)

pkg_search_module(GTK REQUIRED gtk+-2.0 IMPORTED_TARGET)
pkg_search_module(SDL REQUIRED sdl IMPORTED_TARGET)
pkg_search_module(GLU REQUIRED glu IMPORTED_TARGET)

include(cmake/Verilator.cmake)
verilator_add()

add_subdirectory(8051)
add_subdirectory(basecode)
add_subdirectory(core)
add_subdirectory(glee)
add_subdirectory(stb)
add_subdirectory(chip)
add_subdirectory(tinyxml)
add_subdirectory(chipverilog)

add_executable(Atanua core/main.cpp)

target_include_directories(Atanua PUBLIC
    ./include
    ./
)

target_link_libraries(Atanua PkgConfig::SDL PkgConfig::GLU PkgConfig::GTK
    verilator chipverilog 8051 basecode core glee stb chip tinyxml
)
