cmake_minimum_required(VERSION 3.10)
project(CaptureTheFlag)

include(${CMAKE_CURRENT_SOURCE_DIR}/Settings.cmake)

add_subdirectory(Systems)
add_subdirectory(Entities)

add_executable(CaptureTheFlag 
    main.cpp
    # test.cpp
)

target_link_libraries(CaptureTheFlag PUBLIC
    raylib dl pthread rt 
    RenderSystem 
    Entities
)

target_include_directories(CaptureTheFlag SYSTEM PRIVATE
    ${RAYLIB_CPP_INCLUDE_DIR}
    ${RAYLIB_INCLUDE_DIR}    
)

target_include_directories(CaptureTheFlag PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(CaptureTheFlag PUBLIC 
    ${RAYLIB_LINK_DIR}
)

target_compile_options(CaptureTheFlag PUBLIC 
    ${COMPILER_FLAGS}
)


