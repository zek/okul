#!/usr/bin/env python

import sys
from Sudoku import Solver, SudokuArray
from tkinter import Tk, Canvas, Frame, BOTH, TOP

MARGIN = 20
SIDE = 50
WIDTH = HEIGHT = MARGIN * 2 + SIDE * 9


class SudokuUI(Frame):
    def __init__(self, parent, puzzle):
        Frame.__init__(self, parent)
        self.puzzle = puzzle
        self.parent = parent
        self.row, self.col = -1, -1
        self.__initUI()

    def __initUI(self):
        self.parent.title("Sudoku Solved")
        self.pack(fill=BOTH)
        self.canvas = Canvas(self,
                             width=WIDTH,
                             height=HEIGHT)
        self.canvas.pack(fill=BOTH, side=TOP)

        self.__draw_grid()
        self.__draw_puzzle()

    def __draw_grid(self):
        for i in range(10):
            color = "blue" if i % 3 == 0 else "gray"
            x0 = MARGIN + i * SIDE
            y0 = MARGIN
            x1 = MARGIN + i * SIDE
            y1 = HEIGHT - MARGIN
            self.canvas.create_line(x0, y0, x1, y1, fill=color)

            x0 = MARGIN
            y0 = MARGIN + i * SIDE
            x1 = WIDTH - MARGIN
            y1 = MARGIN + i * SIDE
            self.canvas.create_line(x0, y0, x1, y1, fill=color)

    def __draw_puzzle(self):
        self.canvas.delete("numbers")
        for i in range(9):
            for j in range(9):
                answer = self.puzzle[i * 9 + j]
                if answer != 0:
                    x = MARGIN + j * SIDE + SIDE / 2
                    y = MARGIN + i * SIDE + SIDE / 2
                    self.canvas.create_text(
                        x, y, text=answer, tags="numbers", fill="black"
                    )


def read_sudoku_file(filename):
    numbers = SudokuArray()
    with open(filename) as f:
        for line in f:
            line = line.split()
            if line:
                line = [int(i) for i in line]
                numbers.extend(line)
    return numbers


def print_sudoku(su):
    for i in range(9):
        print(' '.join(str(x) for x in su[i * 9:i * 9 + 9]))


if __name__ == '__main__':
    filename = sys.argv[1] if len(sys.argv) > 1 else "input"
    numbers = read_sudoku_file(filename)
    solver = Solver(numbers)
    if (solver.solve()):
        print_sudoku(solver.getSudoku())
        root = Tk()
        SudokuUI(root, solver.getSudoku())
        root.mainloop()
    else:
        print("failed")
