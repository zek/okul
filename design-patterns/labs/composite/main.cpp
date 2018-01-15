// Please implement the classes needed to make simple calculations:
// sum and difference. There is also a separate class for number,
// which allows changing the value of the number, but keeping the
// whole equation structure and updates result.

// The expected output is at the bottom of the file.

#include<iostream>
#include"MyMath.h"

int main() {
    using namespace std;

    MathNum firstNum = 5;
    MathNum secondNum = 2;
    MathNum thirdNum = 15;

    Multiply firstExp;
    firstExp << firstNum << secondNum << thirdNum;
    cout << "Formula: ";
    firstExp.PrintFormula();
    cout << endl;

    cout << "Value: ";
    firstExp.PrintValue();
    cout << endl;

    cout << "All: ";
    firstExp.PrintAll();
    cout << endl;

    Multiply secondExp;
    secondExp << secondNum <<thirdNum;
    secondExp << firstNum;

    Difference thirdExp = firstExp;
    thirdExp << secondExp;
    thirdExp.PrintAll();
    cout << endl;

    Sum fourthExp;
    fourthExp << secondExp << secondNum;
    Difference fifthExp = fourthExp;
    fifthExp << secondExp;

    Sum sixthExp;
    sixthExp << thirdExp << fifthExp;

    sixthExp.PrintAll();
    cout << endl;

    firstNum.Set(10);
    sixthExp.PrintAll();
    cout << endl;

    return 0;
}
/*
Formula: (5+2)
Value: 7
All: (5+2)=7
((5+2)-(2-5))=10
(((5+2)-(2-5))+(((2-5)+2)-(2-5)))=12
(((10+2)-(2-10))+(((2-10)+2)-(2-10)))=22
*/