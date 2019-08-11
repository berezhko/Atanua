add_library(core SHARED "")

#find_package(PkgConfig REQUIRED)

#pkg_search_module( GTK REQUIRED gtk+-3.0 IMPORTED_TARGET)

target_sources(core
  PRIVATE
    AtanuaConfig.cpp
    basechipfactory.cpp
    BoxStitchingInformation.cpp
    checknet.cpp
    chip.cpp
    fileio.cpp
    fileutils.cpp
    nativefunctions.cpp
    net.cpp
    pin.cpp
    pluginchip.cpp
    pluginchipfactory.cpp
    simutils.cpp
    slidingaverage.cpp
    wire.cpp
  )

target_include_directories(core
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../tinyxml
    ${GTK_INCLUDE_DIRS}
  )
