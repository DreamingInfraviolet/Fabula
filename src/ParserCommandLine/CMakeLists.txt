add_executable(FabulaCommandLine
                    ${PARSER_CMD_SOURCES}
                    ${PARSER_CMD_HEADERS}
                    ${COMMON_SOURCES})
include_directories(. ${PARSER_DIR} ${SRC_DIR}/third_party/docopt.cpp)
target_link_libraries(FabulaCommandLine FabulaParser ParseNodes Docopt)
