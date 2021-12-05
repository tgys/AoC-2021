cmake_minimum_required(VERSION 3.19)
set (CMAKE_CXX_COMPILER "g++")
set (CMAKE_C_COMPILER "gcc")

project(scratch)

set(CMAKE_CXX_STANDARD 20)

add_executable(day_one day_one.cpp)
add_executable(day_two day_two.cpp)
add_executable(day_three day_three.cpp)
add_executable(day_four day_four.cpp)
add_executable(day_five_pt1 day_five_pt1.cpp)
add_executable(day_five_pt2 day_five_pt2.cpp)