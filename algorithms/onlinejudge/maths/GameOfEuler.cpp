/*
───────────────────────────────────────────────────────────────
🧳 UVa 10536 Game of Euler, https://onlinejudge.org/external/105/10536.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr char OCCUPY = 'X';
constexpr int SIZE = 4;
constexpr int MAX_PIN = 3;

using Cell = std::pair<int, int>;
using v_cell = std::vector<Cell>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;


uint32_t fill_cells_2d(uint32_t board, const v_cell& cells) {
  uint32_t new_board = board;
  for(const Cell& cell : cells) {
    int r = cell.first;
    int c = cell.second;
    // --- The Conversion Step ---
    // Convert the (r, c) coordinate to a 1D bit position.
    int position = r * SIZE + c;
    new_board |= (1u << position);
  }
  return new_board;
}

bool is_free(uint32_t board, const v_cell& cells) {
  if(cells.empty()) return false;
  bool res = true;
  for(const Cell& cell : cells) {
    int r = cell.first;
    int c = cell.second;
    // --- The Conversion Step ---
    // Convert the (r, c) coordinate to a 1D bit position.
    int position = r * SIZE + c;
    res = res && !(board & (1u << position));
  }
  return res;
}

// clockwise from up
vii dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


bool in_board(int r, int c) { 
  return r >= 0 && r < SIZE &&  c >= 0 && c < SIZE; 
}

bool is_side_cell(int r, int c, vii& ds) {
  if(r == 0 && c == 0) ds = {dirs[2], dirs[1]};
  else if(r == 0 && c == SIZE - 1) ds = {dirs[2], dirs[3]};
  else if(r == SIZE - 1 && c == 0) ds = {dirs[0], dirs[1]}; 
  else if(r == SIZE - 1 && c == SIZE - 1) ds = {dirs[0], dirs[3]};
  else if(r == 0) ds = {dirs[2]};
  else if(r == SIZE - 1) ds = {dirs[0]};
  else if(c == 0) ds = {dirs[1]};
  else if(c == SIZE - 1) ds = {dirs[3]};
  return r == 0 || r == SIZE - 1 || c == 0 || c == SIZE - 1;
}

v_cell place_pin(const Cell& center_cell, int pin_size, const ii& d) {
  int r = center_cell.first;
  int c = center_cell.second;
  v_cell pin_cells;
  // 1. Add the center cell. This is always part of the pin.
  // 2. Loop from distance 1 up to pin_size to generate the arm cells.
  //  If pin_size is 0, this loop will not execute.
  for(int i = 0; i < pin_size; ++i) {
    int nr = r + d.first * i;
    int nc = c + d.second * i;
    if(in_board(nr, nc))
      pin_cells.push_back({nr, nc});
  }
  return (int)pin_cells.size() == pin_size ? pin_cells : v_cell();
}


bool memo[(1u << (SIZE * SIZE))];

bool can_win(uint32_t board, const v_cell& cells) {

  if(memo[board]) return memo[board];

  for(auto& curr_cell : cells) {
    if(is_free(board, {curr_cell})) {
      // place a pin perpendicularly
      int r = curr_cell.first;
      int c = curr_cell.second;
      int position = r * SIZE + c;
      uint32_t new_board = board | (1u << position);
      if(__builtin_popcount(new_board) < SIZE * SIZE) // if board is full you lose
        if(!can_win(new_board, cells)) {
          memo[board] = true;
          return true;
        }
      // try placing from the side
      for(int pin = 1; pin <= MAX_PIN; ++pin) {
        vii dirs;
        if(is_side_cell(r, c, dirs)) {
          for(auto& d : dirs) {
            v_cell pin_cells = place_pin(curr_cell, pin, d);
            if(is_free(board, pin_cells)) {
              uint32_t new_board = fill_cells_2d(board, pin_cells);
              if(__builtin_popcount(new_board) < SIZE * SIZE) {
                if(!can_win(new_board, cells)) {
                  memo[board] = true;
                  return true;
                }
              }
            }
          }
        }
      }
    }
  }
  return false;

}

namespace algorithms::onlinejudge::maths::game_of_euler
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

        int t_cases;
        char cell;
        scanf("%d\n", &t_cases);
        std::memset(memo, false, sizeof memo); // global memo
        while(t_cases--) {
          uint32_t board = 0;
          v_cell start_cells;
          for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
              scanf("%c\n", &cell);
              if(cell == OCCUPY) {
                int position = i * SIZE + j;
                board |= (1u << position); 
              } else start_cells.push_back({i, j});
            }
          }
          printf("%s\n", start_cells.empty() || can_win(board, start_cells) ? "WINNING" : "LOSING");
        }
    }
}