
# Docopt is used to conveniently parse program options.
add_library(Docopt
                ${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp/docopt.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp/docopt.h
                )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/docopt.cpp)

# Use poco to augment the standard library

# Disable the following poco libraries
#option(ENABLE_XML "Enable the XML" OFF)
#option(ENABLE_JSON "Enable the JSON" OFF)
option(ENABLE_MONGODB "Enable MongoDB" OFF)
option(ENABLE_PDF "Enable PDF" OFF)
#option(ENABLE_UTIL "Enable Util" OFF)
option(ENABLE_NET "Enable Net" OFF)
option(ENABLE_NETSSL "Enable NetSSL" OFF)
option(ENABLE_NETSSL_WIN "Enable NetSSL Windows" OFF)
option(ENABLE_CRYPTO "Enable Crypto" OFF)
option(ENABLE_DATA "Enable Data" OFF)
option(ENABLE_DATA_SQLITE "Enable Data SQlite" OFF)
option(ENABLE_DATA_MYSQL "Enable Data MySQL" OFF)
option(ENABLE_DATA_ODBC "Enable Data ODBC" OFF)
option(ENABLE_SEVENZIP "Enable SevenZip" OFF)
#option(ENABLE_ZIP "Enable Zip" OFF)
option(ENABLE_APACHECONNECTOR "Enable ApacheConnector" OFF)
option(ENABLE_CPPPARSER "Enable C++ parser" OFF)
option(ENABLE_POCODOC "Enable Poco Documentation Generator" OFF)
option(ENABLE_PAGECOMPILER "Enable PageCompiler" OFF)
option(ENABLE_PAGECOMPILER_FILE2PAGE "Enable File2Page" OFF)
set(ENABLE_CRYPTO OFF)
set(POCO_STATIC ON)
add_subdirectory(poco)
