cmake_minimum_required(VERSION 3.6)
project(com267lab4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sequence_exam3.cpp node1.cpp node1.h sequence3.h sequence3.cpp)
add_executable(com267lab4 ${SOURCE_FILES})