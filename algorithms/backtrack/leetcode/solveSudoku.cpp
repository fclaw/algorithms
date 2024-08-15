#include <vector>

namespace algorithms::backtrack::leetcode::sudoku
{

enum Legend { Empty = 0, One, Two, Three, Four, Five, Six, Seven, Eight, Nine };
using sudoku = std::vector<std::vector<Legend>>;

    /**
     * https://leetcode.com/problems/sudoku-solver
     * Write a program to solve a Sudoku puzzle by filling the empty cells.
     * A sudoku solution must satisfy all of the following rules:
     * Each of the digits 1-9 must occur exactly once in each row.
     * Each of the digits 1-9 must occur exactly once in each column.
     * Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.]
     * some ideas:
     * For example, imagine you want to use an algorithm to solve a Sudoku puzzle. 
     * Think of the graph in which vertices correspond to partially 
     * completed Sudoku puzzles (with some of the 81 squares blank, but no rules of Sudoku violated), and directed edges correspond to filling in one new entry of the puzzle (subject to the rules of Sudoku). The problem of computing a solution to the puzzle is exactly the problem of computing a directed path from the vertex corresponding to the initial state of the puzzle to the vertex corresponding to the completed puzzle.4
     */
    
    void solveSudoku(sudoku& board)
    {
    }
}