cmake_minimum_required(VERSION 3.10)

project(opengl.hpp)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)

add_subdirectory(src)
add_subdirectory(example)
