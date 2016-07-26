
#Lzz thigns
find_program(LZZ_COMMAND lzz REQUIRED)

function(add_lzz_file output filename)
  # Only process *.lzz files
  get_filename_component(ext ${filename} EXT)
  if(NOT ext STREQUAL ".lzz")
    return()
  endif()

  get_filename_component(base ${filename} NAME_WE)
  set(base_abs ${CMAKE_CURRENT_BINARY_DIR}/${base})
  set(outfiles ${base_abs}.cpp ${base_abs}.h)
  set(${output} ${${output}} ${outfiles} PARENT_SCOPE)

  #message("outfiles=${outfiles}, DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${filename}")
  add_custom_command(
    OUTPUT ${outfiles}
    COMMAND ${LZZ_COMMAND}
      -o ${CMAKE_CURRENT_BINARY_DIR} # output dir
      -hx ${header_extension}
      -sl -hl -il -tl -nl -x # insert #line commands w/ absolute paths
      -sd -hd -id -td -nd # don't output files that didn't change
      ${CMAKE_CURRENT_SOURCE_DIR}/${filename}
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${filename}"
  )

  set_source_files_properties(${outfiles} PROPERTIES GENERATED TRUE)
endfunction()

function(add_lzz_files output files)
    foreach(filename ${files})
        add_lzz_file(${output} ${filename})
    endforeach()
endfunction()

set(TARGET_NAME ParseNodes)

add_lzz_files(GENERATED_SOURCES ${PARSE_NODE_SOURCES})

source_group("" FILES ${PARSE_NODE_SOURCES})
source_group(generated FILES ${GENERATED_SOURCES})

add_library(${TARGET_NAME}
            ${COMMON_SOURCES}
            ${COMMON_HEADERS}
            ${PARSE_NODE_SOURCES}
            ${PARSE_NODE_HEADERS})

target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
include_directories(. ${PARSE_NODE_DIR} ${PARSER_HEADERS})
