cmake_minimum_required(VERSION 3.0)

set(SE_LIB_NAME SoundEngine)

set(SE_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)
set(SE_HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

# Server Sourcs File (*.cpp)
set(SE_SRC
    ${SE_SRC_PATH}/SoundEngine.cpp
    ${SE_SRC_PATH}/AudioExeption.cpp
    ${SE_SRC_PATH}/IdAlreadyTakeExeption.cpp
    ${SE_SRC_PATH}/NotFoundExeption.cpp
)

# Server Headers File (*.hh, *.hpp)
set(SE_HEADERS
    ${SE_HEADER_PATH}/AudioExeption.hh
    ${SE_HEADER_PATH}/IdAlreadyTakeExeption.hh
    ${SE_HEADER_PATH}/NotFoundExeption.hh
    ${SE_HEADER_PATH}/SoundEngine.hh
)

set(SE_DEPENDENCIES
	${CMAKE_CURRENT_LIST_DIR}/dependencies/lib/fmodL64_vc.lib
)

# Build the binary.
add_library(${SE_LIB_NAME} STATIC ${SE_SRC} ${SE_HEADERS})
target_link_libraries(${SE_LIB_NAME} ${SE_DEPENDENCIES})

target_include_directories(${SE_LIB_NAME} PRIVATE
    ${SE_HEADER_PATH}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/dependencies/include
)