cmake_minimum_required(VERSION 3.0)

set(PE_LIB_NAME PhysicEngine)

set(PE_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(PE_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(PE_INC_DIR_BOULET ${CMAKE_CURRENT_LIST_DIR}/../include)
set(PE_COMMON_PATH ${CMAKE_CURRENT_LIST_DIR}/../Common)

# Server Sources File (*.cpp)
set(PE_SRC
    ${PE_SRC_DIR}/BoxCollider.cpp
    ${PE_SRC_DIR}/Layer.cpp
    ${PE_SRC_DIR}/RigidBody.cpp
)

# Server Headers File (*.hh, *.hpp)
set(PE_HEADERS
    ${PE_INC_DIR}/BoxCollider.hh
    ${PE_INC_DIR}/Layer.hh
    ${PE_INC_DIR}/RigidBody.hh
)

set(PE_DEPENDENCIES
    CommonToolsLib
)

# Build the binary.
add_library(${PE_LIB_NAME} STATIC ${PE_SRC} ${PE_HEADERS})
target_link_libraries(${PE_LIB_NAME} ${PE_DEPENDENCIES})

# Include on all the server can start with the root.
target_include_directories(${PE_LIB_NAME} PRIVATE
    ${PE_INC_DIR}
    ${PE_INC_DIR_BOULET}
    ${PE_COMMON_PATH}/include
)
