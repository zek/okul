#include <iostream>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Solver.h"

BOOST_PYTHON_MODULE (Sudoku) {
    using
    namespace
    boost::python;

    class_<SudokuArray>("SudokuArray")
            .def(vector_indexing_suite<SudokuArray>());

    class_<Solver>("Solver", init<SudokuArray>())
            .def("solve", &Solver::solve)
            .def("getSudoku", &Solver::getSudoku);

//def("TestClass", TestClass);
}