add_executable(FabulaCommandLine
                    ${PARSER_CMD_SOURCES}
                    ${PARSER_CMD_HEADERS}
                    ${COMMON_SOURCES}
                    ${COMMON_HEADERS})
include_directories(. ${PARSER_DIR})
target_link_libraries(FabulaCommandLine FabulaParser ParseNodes)
