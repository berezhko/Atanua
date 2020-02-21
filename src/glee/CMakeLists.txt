enable_language(C)

add_library(glee STATIC "")

target_sources(glee
  PRIVATE
    GLee.c
  )

target_include_directories(glee
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
