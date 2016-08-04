add_executable(FabulaHtmlInterface
                    ${INTERFACE_HTML_SOURCES}
                    ${INTERFACE_HTML_HEADERS}
                    ${COMMON_SOURCES})

include_directories(. ${PARSER_DIR} ${PARSE_NODE_DIR})
target_link_libraries(FabulaHtmlInterface ${Boost_LIBRARIES} FabulaParser ParseNodes)
