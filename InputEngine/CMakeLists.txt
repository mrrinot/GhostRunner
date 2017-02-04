cmake_minimum_required(VERSION 3.0)

set(IE_LIB_NAME InputEngine)

set(IE_SRC_PATH ${CMAKE_CURRENT_LIST_DIR}/src)
set(IE_HEADER_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

# Server Sourcs File (*.cpp)
set(IE_SRC
    ${IE_SRC_PATH}/Gamepad.cpp
    ${IE_SRC_PATH}/InputEngine.cpp
    ${IE_SRC_PATH}/KeyBoard.cpp
    ${IE_SRC_PATH}/Utils.cpp
)

# Server Headers File (*.hh, *.hpp)
set(IE_HEADERS
    ${IE_HEADER_PATH}/Gamepad.hh
    ${IE_HEADER_PATH}/InputEngine.hh
    ${IE_HEADER_PATH}/KeyBoard.hh
    ${IE_HEADER_PATH}/Utils.hh
    ${IE_HEADER_PATH}/InputDevice.hh
)

set(IE_DEPENDENCIES
	${CMAKE_CURRENT_LIST_DIR}/dependencies/lib/dinput8.lib
    ${CMAKE_CURRENT_LIST_DIR}/dependencies/lib/dxguid.lib
)

# Build the binary.
add_library(${IE_LIB_NAME} STATIC ${IE_SRC} ${IE_HEADERS})
target_link_libraries(${IE_LIB_NAME} ${IE_DEPENDENCIES})

target_include_directories(${IE_LIB_NAME} PRIVATE
    ${IE_HEADER_PATH}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/dependencies/include
)