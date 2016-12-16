#include "Mylib.h"

using namespace std;

void apply(stack<char> &operator_stack, stack<int> &operand_stack) {
    char c;
    int n1, n2;
    while (!operator_stack.empty()) {
        c = operator_stack.top();

        if (c == '(') {
            return;
        }
        if (operand_stack.size() < 2) {
            cout << "invalid expression" << endl;
            exit(0);
        }

        switch (c) {
            case '+':
                n1 = operand_stack.top();
                operand_stack.pop();
                n2 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(n2 + n1);
                break;
            case '-':
                n1 = operand_stack.top();
                operand_stack.pop();
                n2 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(n2 - n1);
                break;
            case '*':
                n1 = operand_stack.top();
                operand_stack.pop();
                n2 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(n2 * n1);
                break;
            case '/':
                n1 = operand_stack.top();
                operand_stack.pop();
                n2 = operand_stack.top();
                operand_stack.pop();
                operand_stack.push(n2 / n1);
                break;
        }
        operator_stack.pop();
    }
}

double read_and_evaluate(istream &ins) {

    stack<char> operator_stack; // 1 2 3
    stack<int> operand_stack; // + *

    int n;
    char c, c2;

    while (1) {
        cin >> ws;
        int p = cin.peek();

        if (p == EOF) break;

        if (isdigit(p)) {
            std::cin >> n;
            operand_stack.push(n);
        } else {
            std::cin >> c;
            if (c == '+' || c == '-') {
                if (operator_stack.size()) {
                    c2 = operator_stack.top();
                    if (c2 == '/' || c2 == '*') {
                        apply(operator_stack, operand_stack);
                    }
                }
                operator_stack.push(c);
            } else if (c == '*' || c == '/') {
                if (operator_stack.size()) {
                    c2 = operator_stack.top();
                    if (c2 == '/' || c2 == '*') {
                        apply(operator_stack, operand_stack);
                    }
                }
                operator_stack.push(c);
            } else if (c == '(') {
                operator_stack.push(c);
            } else if (c == ')') {
                if (operator_stack.size()) {
                    apply(operator_stack, operand_stack);
                }
                if (operator_stack.size() && operator_stack.top() == '(') {
                    operator_stack.pop();
                } else {
                    cout << "invalid expression" << endl;
                    exit(0);
                }
            } else {
                cout << "invalid expression" << endl;
                exit(0);
            }
        }

    }
    apply(operator_stack, operand_stack);
    if (operand_stack.size() == 1 && operator_stack.size() == 0) {
        return operand_stack.top();
    } else {
        cout << "invalid expression" << endl;
        exit(0);

    }
}
