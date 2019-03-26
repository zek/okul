#ifndef MYLIB_H
#define MYLIB_H

#include <iostream>
#include <vector>
#include <algorithm>    // std::reverse

using namespace std;

const char ops[] = {'+', '-', '/', '*'};

double apply(vector<char> operator_stack, vector<double> operand_stack);

bool test_operator(const vector<double> &operand_stack, vector<char> &operator_stack, double result, size_t n = 1);

bool test_operand(vector<double> &operand_stack, vector<char> &operator_stack, const string number, double result);

void printResult(vector<double> operand_stack, vector<char> operator_stack);

#endif