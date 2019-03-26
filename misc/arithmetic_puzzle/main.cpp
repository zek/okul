#include <fstream>
#include "MyLib.h"

/*
 * 1 + 2 / 6 = 2
 * 1 + 44 + 2 = 47
 * 1 + 44 / 2 = 23
 */
int main() {
    vector<double> operand_stack; // 1 2 3 4
    vector<char> operator_stack; // + - * /

    string number = "1234567";
    double result = 155;
    auto r = test_operand(operand_stack, operator_stack, number, result);
    if (r) {
        printResult(operand_stack, operator_stack);
        cout << " = " << result << endl;
    } else {
        cout << "No Result!" << endl;
    }

    return EXIT_SUCCESS;
}


