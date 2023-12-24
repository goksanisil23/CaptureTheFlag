cmake_minimum_required(VERSION 3.10)
project(Entities)

include(${CMAKE_CURRENT_SOURCE_DIR}/../Settings.cmake)

set(ENTITIES_SRCS Agent.cpp)

# Create the library
add_library(Entities ${ENTITIES_SRCS})

target_include_directories(Entities PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utils
)

target_include_directories(Entities SYSTEM PRIVATE 
${RAYLIB_CPP_INCLUDE_DIR}
${RAYLIB_INCLUDE_DIR}
)

target_link_libraries(Entities PRIVATE raylib dl pthread rt)
target_link_directories(Entities PUBLIC ${RAYLIB_LINK_DIR})
target_compile_options(Entities PRIVATE ${COMPILER_FLAGS})