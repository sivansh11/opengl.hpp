cmake_minimum_required(VERSION 3.10)

project(opengl.hpp)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(opengl.hpp ${SRC_FILES})

target_include_directories(opengl.hpp
    PUBLIC src
)

target_link_libraries(opengl.hpp
    glad
    glfw
)
