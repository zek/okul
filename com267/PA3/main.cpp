// FILE: PA3_Main.cpp
// Basic arithmetic expression evaluator that takes an arithmetic
// expression as input, and evaluates the arithmetic expression.
// The purpose is to illustrate a fundamental use of stacks.

#include "MyLib.h"


int main( )
{
    double answer;

    std::cout << "Type a fully parenthesized arithmetic expression:" << std::endl;
    answer = read_and_evaluate(std::cin);
    std::cout << answer << std::endl;


    return EXIT_SUCCESS;
}


