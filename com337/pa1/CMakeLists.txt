cmake_minimum_required(VERSION 3.5)
project(cg_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated-declarations")

set(SOURCE_FILES main.cpp)
add_executable(cg_1 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(cg_1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
