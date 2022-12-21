cmake_minimum_required(VERSION 3.10)

project(example)

add_executable(example main.cpp)

target_include_directories(example
    PUBLIC src
)

include_directories(example
    ../
)

target_link_libraries(example
    src
)