//
// Created by Talha Zekeriya Durmuş on 13/12/2017.
//

#ifndef PROJECT2_TESTCLASS_H
#define PROJECT2_TESTCLASS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef std::vector<int> SudokuArray;

class Solver {
private:
    SudokuArray _sudoku;
public:
    explicit Solver(const SudokuArray &sudoku) {
        _sudoku = sudoku;
    }

    bool solve() {
        int row = 0, col = 0;

        if (!findUnsolvedPos(row, col)) {
            return true;
        }

        for (int number = 1; number <= 9; number++) {
            if (isSafe(row, col, number)) {
                _sudoku[row * 9 + col] = number;
                if (solve()) return true;
            }

            _sudoku[row * 9 + col] = 0;
        }
        return false;
    }

    SudokuArray getSudoku() {
        return _sudoku;
    }

private:

    bool findUnsolvedPos(int &row, int &col) {
        for (row = 0; row < 9; row++)
            for (col = 0; col < 9; col++)
                if (_sudoku[row * 9 + col] == 0) {
                    return true;
                }
        return false;
    }

    bool usedInRow(int row, int num) {
        for (int col = 0; col < 9; col++)
            if (_sudoku[row * 9 + col] == num)
                return true;
        return false;
    }

    bool usedInCol(int col, int num) {
        for (int row = 0; row < 9; row++)
            if (_sudoku[row * 9 + col] == num)
                return true;
        return false;
    }

    bool usedInBox(int boxPos, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (_sudoku[boxPos + row * 9 + col] == num)
                    return true;
        return false;
        /**
         *  0  1  2   3  4  5   6  7  8
         *  9 10 11  12 13 14  15 16 17
         * 18 19 20  21 22 23  24 25 26
         *
         * 27 28 29  30 31 32  33 34 35
         */
    }

    bool isSafe(int row, int col, int num) {
        return !usedInRow(row, num) &&
               !usedInCol(col, num) &&
               !usedInBox((row - row % 3) * 9 + col - col % 3, num);
    }
};


#endif //PROJECT2_TESTCLASS_H
