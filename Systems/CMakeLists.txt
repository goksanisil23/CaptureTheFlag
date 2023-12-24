cmake_minimum_required(VERSION 3.10)
project(RenderSystem)

include(${CMAKE_CURRENT_SOURCE_DIR}/../Settings.cmake)

set(RENDER_SYS_SRCS RenderSystem.cpp)

# Create the library
add_library(RenderSystem ${RENDER_SYS_SRCS})

target_include_directories(RenderSystem PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utils
)

target_include_directories(RenderSystem SYSTEM PRIVATE 
${RAYLIB_CPP_INCLUDE_DIR}
${RAYLIB_INCLUDE_DIR}
)

target_link_libraries(RenderSystem PRIVATE raylib dl pthread rt)
target_link_directories(RenderSystem PUBLIC ${RAYLIB_LINK_DIR})
target_compile_options(RenderSystem PRIVATE ${COMPILER_FLAGS})