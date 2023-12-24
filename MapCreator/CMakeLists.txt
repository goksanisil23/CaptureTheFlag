cmake_minimum_required(VERSION 3.10)
project(MapCreator)

include(${CMAKE_CURRENT_SOURCE_DIR}/../Settings.cmake)

add_executable(MapCreator 
    map_creator.cpp
)

target_link_libraries(MapCreator PUBLIC
    raylib dl pthread rt
)

target_include_directories(MapCreator SYSTEM PRIVATE
    ${RAYLIB_CPP_INCLUDE_DIR}
    ${RAYLIB_INCLUDE_DIR}    
)

target_include_directories(MapCreator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Utils
)

target_link_directories(MapCreator PUBLIC 
    ${RAYLIB_LINK_DIR}
)

target_compile_options(MapCreator PUBLIC 
    ${COMPILER_FLAGS}
)