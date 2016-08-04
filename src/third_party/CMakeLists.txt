
#Docopt
add_library(Docopt
                ${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp/docopt.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp/docopt.h
                )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp)
