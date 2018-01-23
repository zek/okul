cmake_minimum_required(VERSION 3.6)
project(com267_pa3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyLib.cpp MyLib.h)
add_executable(com267_pa3 ${SOURCE_FILES})