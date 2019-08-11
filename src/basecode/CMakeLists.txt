add_library(basecode SHARED "")

target_sources(basecode
  PRIVATE
    angelcodefont.cpp
    mersennetwister.cpp
    toolkit.cpp
  )

target_include_directories(basecode
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../include
  )
