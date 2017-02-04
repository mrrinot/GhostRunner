cmake_minimum_required(VERSION 3.0)

set(COMMON_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)
set(COMMON_HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

# Server Sources File (*.cpp)
set(COMMON_SRC_FILES
    ${COMMON_SRC_PATH}/Vector2.cpp
    ${COMMON_SRC_PATH}/Logger/Logger.cpp
    ${COMMON_SRC_PATH}/Logger/LogHandler.cpp
    ${COMMON_SRC_PATH}/Logger/LoggerCallbacks.cpp
    ${COMMON_SRC_PATH}/Logger/LoggerOptions.cpp
)

# Server Headers File (*.hh, *.hpp)
set(COMMON_HEADER_FILES
    ${COMMON_HEADER_PATH}/Vector2.hh
    ${COMMON_HEADER_PATH}/Logger.hh
    ${COMMON_HEADER_PATH}/PrettyPrinter.hh
    ${COMMON_HEADER_PATH}/Logger/Logger.hh
    ${COMMON_HEADER_PATH}/Logger/LoggerCallbacks.hh
    ${COMMON_HEADER_PATH}/Logger/LoggerOptions.hh
    ${COMMON_HEADER_PATH}/Logger/LogHandler.hh
)

# Build the library.
add_library(CommonToolsLib STATIC ${COMMON_SRC_FILES} ${COMMON_HEADER_FILES})

target_include_directories(CommonToolsLib PRIVATE ${COMMON_HEADER_PATH})