cmake_minimum_required(VERSION 3.7)
project(project2)

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
if (${PYTHON_VERSION_MAJOR} EQUAL 3)
    FIND_PACKAGE(Boost COMPONENTS python3)
else()
    FIND_PACKAGE(Boost COMPONENTS python)
endif()

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!


set(SOURCE_FILES main.cpp Solver.h)

PYTHON_ADD_MODULE(Sudoku ${SOURCE_FILES})

set(CMAKE_CXX_STANDARD 11)


