#include "MyLib.h"

double apply_addsub(vector<char> &operator_stack, vector<double> &operand_stack) {
    for (int i = 0; i < operator_stack.size(); ) {
        switch (operator_stack[i]) {
            case '+':
                operand_stack[i] = operand_stack[i] + operand_stack[i + 1];
                break;
            case '-':
                operand_stack[i] = operand_stack[i] - operand_stack[i + 1];
                break;
            default:
                i++;
                continue;
        }
        operand_stack.erase(operand_stack.begin() + i + 1);
        operator_stack.erase(operator_stack.begin() + i);
    }
    return operand_stack.back();
}

double apply(vector<char> operator_stack, vector<double> operand_stack) {
    for (int i = 0; i < operator_stack.size(); ) {
        switch (operator_stack[i]) {
            case '*':
                operand_stack[i] = operand_stack[i] * operand_stack[i + 1];
                break;
            case '/':
                operand_stack[i] = operand_stack[i] / operand_stack[i + 1];
                break;
            default:
                i++;
                continue;
        }
        operand_stack.erase(operand_stack.begin() + i + 1);
        operator_stack.erase(operator_stack.begin() + i);
    }
    return apply_addsub(operator_stack, operand_stack);
}

/*
 * Backtracking Algorithm
 * operand_stack.size() = 5
 *
 * 1 + 2 + 3 + 4 + 5
 *
 * + - * -
 *
 */
bool test_operator(const vector<double> &operand_stack, vector<char> &operator_stack, double result, size_t n) {
    if (n == operand_stack.size()) {
        printResult(operand_stack, operator_stack);
        cout << endl;
        return apply(operator_stack, operand_stack) == result;
    } else {
        for (auto op : ops) {
            operator_stack.push_back(op);
            if (test_operator(operand_stack, operator_stack, result, n + 1)) return true;
            else operator_stack.pop_back();
        }
        return false;
    }
}


/*
 * Backtracking algoritm. Recursive Function
 *
 * test_operand(12345)
 * 1 test_operand(2345)
 * 2 test_operand(345)
 * 3
 */
bool test_operand(vector<double> &operand_stack, vector<char> &operator_stack, const string number, double result) {
    if (number.empty()) {
        return test_operator(operand_stack, operator_stack, result);
    } else {
        for (size_t i = 1; i < 4 && i <= number.size(); i++) {
            operand_stack.push_back(stoi(number.substr(0, i)));
            if (test_operand(operand_stack, operator_stack, number.substr(i), result)) return true;
            else operand_stack.pop_back();
        }
        return false;
    }
}


void printResult(vector<double> operand_stack, vector<char> operator_stack) {

    reverse(operand_stack.begin(), operand_stack.end());
    reverse(operator_stack.begin(), operator_stack.end());

    while (!operator_stack.empty()) {
        cout << operand_stack.back();
        operand_stack.pop_back();
        cout << " " << operator_stack.back() << " ";
        operator_stack.pop_back();
    }
    cout << operand_stack.front();
}