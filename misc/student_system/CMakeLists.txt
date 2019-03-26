cmake_minimum_required(VERSION 3.7)
project(safvanhw3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Student.cpp Student.h Advisor.cpp Advisor.h Exception.cpp Exception.h Assignment.cpp Assignment.h)
add_executable(safvanhw3 ${SOURCE_FILES})