#include <vector>

namespace algorithms::backtrack::leetcode::sudoku
{

enum Cell { Empty = 0, One, Two, Three, Four, Five, Six, Seven, Eight, Nine };
using sudoku = std::vector<std::vector<Cell>>;

    /**
     * https://leetcode.com/problems/sudoku-solver
     * Write a program to solve a Sudoku puzzle by filling the empty cells.
     * A sudoku solution must satisfy all of the following rules:
     * Each of the digits 1-9 must occur exactly once in each row.
     * Each of the digits 1-9 must occur exactly once in each column.
     * Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
     */
    void solveSudoku(sudoku& board)
    {
    }
}