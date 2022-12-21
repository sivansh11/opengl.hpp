cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SRC_FILES *.cpp)

project(src)

add_library(src ${SRC_FILES})

target_include_directories(src
    PUBLIC ../opengl
)

target_link_libraries(src
    glad
    glfw
)