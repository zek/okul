#ifndef MYLIB_H
#define MYLIB_H

#include <cstring>    // Provides strchr
#include <iostream>   // Provides cout, cin, peek, ignore
#include <stack>      // Provides the stack template class
#include <cctype>     // Provides isdigit
#include <cstdlib>    // Provides EXIT_SUCCESS

// Hints:
// 1- istream::peek function returns the next character in the input sequence, without extracting it: The character is left as the next character to be extracted from the stream.
// 2- int isdigit(int c) function: checks whether c is a decimal digit character.


// PROTOTYPES for functions used by this demonstration program:
double read_and_evaluate(std::istream& ins);
// Precondition: The next line of characters in the istream ins is a fully
// parenthesized arithmetic expression formed from decimal digits and
// the four operations + - * /.
// Postcondition: A line has been read from the istream ins, and this line has
// been evaluated as an arithmetic expression. The value of the expression has
// been returned by the function.




#endif