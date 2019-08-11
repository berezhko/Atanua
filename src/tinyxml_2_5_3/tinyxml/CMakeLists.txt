add_library(tinyxml SHARED "")

target_sources(tinyxml
  PRIVATE
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
  )

target_include_directories(tinyxml
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
