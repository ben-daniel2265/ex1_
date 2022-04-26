cmake_minimum_required(VERSION 3.21)
project(ex1_ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tests)

add_executable(ex1_ RLEList_example_test.c RLEList.c)
