/*
───────────────────────────────────────────────────────────────
🧳 UVa 11699 Rooks, https://onlinejudge.org/external/116/11699.pdf, rt: s
───────────────────────────────────────────────────────────────
♟️ Verdict: Accepted | Runtime: 0.040s (Bitwise Feasibility Backtracking)

   Algorithmic Summary & Design Principles:

   1. Problem Reduction (Row Choice + Deterministic Column Choice):
      We must place the minimum number of rooks on a 15x15 chessboard so that 
      every '#' square is attacked (its row or column has a rook).
      
      If we choose a subset of rows to place rooks in (represented by 'rows'):
        - Row rooks placed = __builtin_popcount(rows).
        - Any '#' cell in a row r where r is NOT in 'rows' is an "uncovered/stray cell".

   2. The "Stray Cell" Column Grouping Principle:
      If a column 'c' contains 3 stray '#' cells in different unchosen rows, 
      placing ONE rook anywhere in column 'c' attacks ALL 3 stray cells at once.
      Therefore, the required column rooks equals the number of UNIQUE columns 
      that contain at least one stray '#' cell.

   3. Bitwise OR Column Accumulation (Zero-Allocation O(15) Check):
      To find all unique columns with stray cells, we invert 'rows' using 
      bitwise XOR (no_rook_rows = all_rows_mask ^ rows).
      
      We then perform a bitwise OR across all unchosen rows:
         uncovered_cols = OR_{r in no_rook_rows} (board[r])
      
      The bitwise OR collects all '#' column bits in 15 CPU instructions 
      without needing 2D nested loops or std::unordered_set.
      
      Column rooks required = __builtin_popcount(uncovered_cols).

   4. Feasibility Predicate (is_feasible):
      Comparing 'col_rooks <= row_rooks' evaluates whether the required column 
      rooks can be satisfied within the allowed budget for the current 
      search depth, providing a fast O(1) feasibility test for backtracking.

   5. Complexity Analysis:
      - Search Space: 2^15 = 32,768 row bitmasks.
      - Operations per mask: 15 bitwise OR operations.
      - Total Operations: 32,768 * 15 = 491,520 ops (~0.040s runtime).
───────────────────────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 
using vi = std::vector<int>;

const int SIZE = 15;


// Returns true if 'sub' is a subset of 'main_set' (sub <= main_set)
bool is_subset(int sub, int main_set) {
  return (sub & main_set) == sub;
}


bool is_feasible(const vi& board, int rows, int all_rows_mask) {
  int row_rooks = __builtin_popcount(rows);
  int no_rook_rows = all_rows_mask ^ rows; // Complement: unchosen rows
    
  int uncovered_cols = 0;

  // Accumulate all '#' column bits from unchosen rows
  for (int r = 0; r < SIZE; ++r) {
    if(no_rook_rows & (1 << r)) { // Check bit r (Row index)
      uncovered_cols |= board[r]; // Bitwise OR collects all '#' columns
    }
  }

  int col_rooks = __builtin_popcount(uncovered_cols);

  return col_rooks <= row_rooks;
}


namespace algorithms::onlinejudge::advanced_topics::rooks
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }
        
        std::string str;
        while(std::getline(std::cin, str) && str != "END") {
          int rows_mask = 0;
          vi board(SIZE);
          for(int i = 0; i < SIZE; ++i) {
            if(str[i] == '#') {
              board[0] |= (1 << i);
              rows_mask |= (1 << 0);
            }
          }
          for(int i = 1; i < SIZE; ++i) {
            std::getline(std::cin, str);
            for(int j = 0; j < SIZE; ++j) {
              if(str[j] == '#') {
                board[i] |= (1 << j);
                rows_mask |= (1 << i);
              }
            }
          }
          
          int best = SIZE;
          for(int mask = 0; mask < (1 << SIZE); ++mask) {
            if(is_subset(mask, rows_mask)) {
              int rooks = __builtin_popcount(mask);
              if(rooks < best && is_feasible(board, mask, rows_mask)) {
                best = std::min(best, rooks);
              }
            }
          }
          printf("%d\n", best);
        }
    }
}
