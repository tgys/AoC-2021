cmake_minimum_required(VERSION 3.19)
set (CMAKE_CXX_COMPILER "g++")
set (CMAKE_C_COMPILER "gcc")

project(scratch)

set(CMAKE_CXX_STANDARD 11)

add_executable(day_one day_one.cpp)
add_executable(day_two day_two.cpp)
add_executable(day_three day_three.cpp)