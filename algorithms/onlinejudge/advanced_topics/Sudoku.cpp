/*
───────────────────────────────────────────────────────────────
🧳 UVa 989 SuDoku, https://onlinejudge.org/external/9/989.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




const int MAX_BIT = 82; 

using vi = std::vector<int>;
using vvi = std::vector<vi>;


void print_board_uva(int n, const vvi& board) {
    int N = n * n;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            std::cout << board[r][c] << (c == N - 1 ? "" : " ");
        }
        std::cout << "\n";
    }
}

struct Masks
{
    std::bitset<MAX_BIT> rows;
    std::bitset<MAX_BIT> cols;
    std::bitset<MAX_BIT> boxes;
};


int get_box_idx(int r, int c, int n) {
  return (r / n) * n + (c / n); // shrunk by the factor of n
}


void toggle_digit(int r, int c, int d, int n, Masks& masks) {
    int N = n * n;
    int box_id = get_box_idx(r, c, n);
    
    int r_bit = (r * N) + d;
    int c_bit = (c * N) + d;
    int b_bit = (box_id * N) + d;

    masks.rows.flip(r_bit);
    masks.cols.flip(c_bit);
    masks.boxes.flip(b_bit);
}



bool can_solved(int r, int c, int n, vvi& board, Masks& masks) {

  int N = n * n;

   // Advance to next row if we reach the end of column
  if(c == N) {
    r++;
    c = 0;
  }

  if(r == N) {
    return true;
  }

  if(board[r][c] != 0) {
    return can_solved(r, c + 1, n, board, masks);
  }

  for(int d = 1; d <= N; ++d) {
    int row_bit = (r * N) + d;
    int col_bit = (c * N) + d;
    int box_bit = (get_box_idx(r, c, n) * N) + d;
    if(!masks.rows.test(row_bit) && 
       !masks.cols.test(col_bit) && 
       !masks.boxes.test(box_bit)) {
      toggle_digit(r, c, d, n, masks);
      board[r][c] = d;
      if(can_solved(r, c + 1, n, board, masks)) {
        return true;
      }
      board[r][c] = 0;
      toggle_digit(r, c, d, n, masks);
    }
  }

  return false; // Trigger backtracking
}

namespace algorithms::onlinejudge::advanced_topics::sudoku
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

        int n;
        bool is_first = true;
        while(std::cin >> n) {
          if(!is_first) { 
            std::cout << std::endl; 
          } else {
            is_first = false; 
          }
          int N = n * n;
          vvi board(N, vi(N));
          Masks masks;
          for(int r = 0; r < N; ++r) {
            for(int c = 0; c < N; ++c) {
              std::cin >> board[r][c];
              if(board[r][c]) {
                int digit = board[r][c];
                int box_id = (r / n) * n + (c / n); // 0, 1, 2, 3 for 4x4
                // Unique bit offset for each constraint
                int row_bit = (r * N) + digit;      // Row r offset
                int col_bit = (c * N) + digit;      // Col c offset
                int box_bit = (box_id * N) + digit; // Sub-box offset
                masks.rows.set(row_bit);
                masks.cols.set(col_bit);
                masks.boxes.set(box_bit);
              }
            }
          }

          bool is_solved = can_solved(0, 0, n, board, masks);
          if(!is_solved) {
            printf("NO SOLUTION\n");
          } else {
            print_board_uva(n, board);
          }
        }
    }
}