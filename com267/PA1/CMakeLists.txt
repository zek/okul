cmake_minimum_required(VERSION 3.5)
project(COM267PA1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sequence_exam.cpp sequence1.cpp sequence1.h)
add_executable(COM267PA1 ${SOURCE_FILES})