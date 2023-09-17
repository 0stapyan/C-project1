cmake_minimum_required(VERSION 3.26)
project(C_project1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_project1
        First.c)
