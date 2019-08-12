add_library(core SHARED "")

#target_compile_options(core PRIVATE "-DGTK_DISABLE_DEPRECATED")

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
