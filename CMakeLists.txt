cmake_minimum_required(VERSION 3.17)
project(p1)

set(CMAKE_CXX_STANDARD 14)

add_executable(p1 main.cpp philosopher/Philosopher.cpp philosopher/Philosopher.h fork/Fork.cpp fork/Fork.h)