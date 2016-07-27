

set(TARGET_NAME ParseNodes)

source_group("" FILES ${PARSE_NODE_SOURCES})
source_group(generated FILES)

add_library(${TARGET_NAME}
            ${COMMON_SOURCES}
            ${COMMON_HEADERS}
            ${PARSE_NODE_SOURCES}
            ${PARSE_NODE_HEADERS})

target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
include_directories(. ${PARSE_NODE_DIR})
