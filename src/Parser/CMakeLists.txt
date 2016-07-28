
#Flex/Bison things
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
BISON_TARGET(Parser ${PARSER_DIR}/Grammar.ypp ${CMAKE_CURRENT_BINARY_DIR}/generated_parser.cpp)
FLEX_TARGET(Lexer ${PARSER_DIR}/Grammar.flex ${CMAKE_CURRENT_BINARY_DIR}/generated_lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_library(FabulaParser
                ${PARSER_SOURCES}
                ${PARSER_HEADERS}
                ${COMMON_SOURCES}
                ${COMMON_HEADERS}
                ${BISON_Parser_OUTPUTS}
                ${FLEX_Lexer_OUTPUTS})
target_link_libraries(FabulaParser ${Boost_LIBRARIES})
include_directories(. ${PARSE_NODE_DIR})
