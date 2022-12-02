cmake_minimum_required(VERSION 3.23)
project(advent-of-code-2022)

set(CMAKE_CXX_STANDARD 23)

add_executable(day01 d01/part1and2.cpp py++.cpp)
add_executable(day02 d02/part1and2.cpp py++.cpp)

include_directories(.)
