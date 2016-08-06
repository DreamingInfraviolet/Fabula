 
set(SRC_DIR                                        ${CMAKE_CURRENT_SOURCE_DIR})
set(COMMON_DIR                                     ${CMAKE_CURRENT_SOURCE_DIR}/common/)
set(PARSE_NODE_DIR                                 ${CMAKE_CURRENT_SOURCE_DIR}/ParseNodes/)
set(PARSER_DIR                                     ${CMAKE_CURRENT_SOURCE_DIR}/Parser/)
set(PARSER_CMD_DIR                                 ${CMAKE_CURRENT_SOURCE_DIR}/ParserCommandLine/)
set(INTERFACE_HTML_DIR                             ${CMAKE_CURRENT_SOURCE_DIR}/HTMLGeneratorInterface/)

macro(populate_sources name dir)
    file(GLOB ${name} ${dir}/*.cpp ${dir}/*.cc ${dir}/*.c)
endmacro()

macro(populate_headers name dir)
    file(GLOB ${name} ${dir}/*.h ${dir}/*.hpp)
endmacro()

macro(populate_sources_and_headers sources_name headers_name dir)
    populate_sources(${sources_name} ${dir})
    populate_headers(${headers_name} ${dir})
endmacro()

populate_sources_and_headers(COMMON_SOURCES         COMMON_HEADERS         ${COMMON_DIR})
populate_sources_and_headers(PARSE_NODE_SOURCES     PARSE_NODE_HEADERS     ${PARSE_NODE_DIR})
populate_sources_and_headers(PARSER_SOURCES         PARSER_HEADERS         ${PARSER_DIR})
populate_sources_and_headers(PARSER_CMD_SOURCES     PARSER_CMD_HEADERS     ${PARSER_CMD_DIR})
populate_sources_and_headers(INTERFACE_HTML_SOURCES INTERFACE_HTML_HEADERS ${INTERFACE_HTML_DIR})

set(PSC_TEST_SOURCES parametrised_string_constructor_test.cpp)
set(PSC_TEST_HEADERS parametrised_string_constructor.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(Parser)
add_subdirectory(ParseNodes)
add_subdirectory(ParserCommandLine)
add_subdirectory(HTMLGeneratorInterface)
add_subdirectory(third_party)
