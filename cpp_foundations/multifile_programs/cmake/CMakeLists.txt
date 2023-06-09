cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)

project(cmake_example)

add_executable(example src/main.cpp src/increment_and_sum.cpp src/vect_add_one.cpp)

set(CMAKE_C_COMPILER "C:/MinGW/bin/g++.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")