#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include <string>

class Exception : public std::exception {
    std::string s;

public:
    Exception(std::string ss) : s(ss) {}

    ~Exception() throw() {}

    const char *what() const throw() { return s.c_str(); }
};


#endif