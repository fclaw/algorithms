#include <vector>
#include <set>

namespace algorithms::backtrack::leetcode::sudoku
{

const int MAX_NUMBER = 9;
const int SQUARE_SIZE = 3;
const char empty = '.';
using board = std::vector<std::vector<char>>;
using clues = std::vector<int>;
using cells = std::vector<std::tuple<int, int, int>>;

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
    // check row
    // check col
    // check 3 x 3 square
    clues rows(MAX_NUMBER, 0);
    clues cols(MAX_NUMBER, 0);
    clues square(MAX_NUMBER, 0);
    int getSquare(int r, int c) { return SQUARE_SIZE * (r / SQUARE_SIZE) + c / SQUARE_SIZE; }
    bool finished = false;
    void backtrack(const board& sudoku, cells& xs, int pos)
    {
        if(pos == xs.size())
        {
            finished = true;
            return;
        }

        for(int k = 1; k <= MAX_NUMBER; k++)
        {
            int r, c;
            char l;
            std::tie(r, c, l) = xs[pos];
            if(((rows[r] & (1 << k)) || 
                (cols[c] & (1 << k)) ||
                (square[getSquare(r, c)] & (1 << k))))
              continue;  
            xs[pos] = {r, c, k};
            rows[r] |= (1 << k);
            cols[c] |= (1 << k);
            square[getSquare(r, c)] |= (1 << k);
            backtrack(sudoku, xs, pos + 1);
            if(!finished)
            {
                rows[r] &= ~(1 << k);
                cols[c] &= ~(1 << k);
                square[getSquare(r, c)] &= ~(1 << k);
                xs[pos] = {r, c, -1};
            }
        }
    }
    void solveSudoku(board& sudoku)
    {
        cells xs;
        for(int r = 0; r < MAX_NUMBER; r++)
          for(int c = 0; c < MAX_NUMBER; c++)
          {
             if(sudoku[r][c] != empty)
             {
                 int v = sudoku[r][c] - '0';
                 rows[r] |= (1 << v);
                 cols[c] |= (1 << v);
                 square[getSquare(r, c)] |= (1 << v);
             }
             else xs.push_back({r, c, -1});
          }

        backtrack(sudoku, xs, 0);
        for(auto x : xs)
        {
            int r, c;
            int l;
            std::tie(r, c, l) = x;
            sudoku[r][c] = std::to_string(l)[0];
        }
    }
}