add_executable(FabulaHtmlInterface
                    ${INTERFACE_HTML_SOURCES}
                    ${INTERFACE_HTML_HEADERS}
                    ${COMMON_SOURCES})

include_directories(. ${PARSER_DIR} ${PARSE_NODE_DIR} ${SRC_DIR}/third_party/docopt.cpp)
target_link_libraries(FabulaHtmlInterface FabulaParser ParseNodes Docopt)
