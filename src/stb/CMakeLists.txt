enable_language(C)

add_library(stb SHARED "")

target_sources(stb
  PRIVATE
    stb_image.c
    stb_image_write.c
  )

target_include_directories(stb
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
