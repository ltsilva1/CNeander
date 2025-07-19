cmake_minimum_required(VERSION 3.31)
project(cneander C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(cneander src/main.c
        src/print_functions.c
        src/memory.c)
