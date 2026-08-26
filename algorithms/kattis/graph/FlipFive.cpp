/*
───────────────────────────────────────────────────────────────
🧳 Flip Five, https://open.kattis.com/problems/flipfive, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int SIZE = 3;


using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;


bool in_grid(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; }

// 4-directional grid offsets: {dr, dc}
const vii dirs4 = {
    {-1,  0}, // 1. North (Up)
    { 0,  1}, // 3. East (Right)
    { 1,  0}, // 5. South (Down)
    { 0, -1}, // 7. West (Left)
};

void toggle(int& board, int r, int c) {
  // 1. Toggle the center cell itself (r, c)
  board ^= (1 << (r * SIZE + c));

  // 2. Toggle the 4 adjacent neighbors (if inside grid)
  for (const auto& d : dirs4) {
    int nr = r + d.first;
    int nc = c + d.second;
    if (in_grid(nr, nc)) {
      board ^= (1 << (nr * SIZE + nc));
    }
  }
}

int get_min_clicks(int target) {

  std::queue<int> queue;
  vi click(1 << (SIZE * SIZE), INT32_MAX);
  // init 
  queue.push(0);
  click[0] = 0;
  
  int min_clicks = -1;

  while(!queue.empty()) {
    int board = queue.front(); queue.pop();
    int clicks_so_far =  click[board];
    if(board == target) {
       min_clicks = clicks_so_far;
       break;
    }
    for(int r = 0; r < SIZE; ++r) {
      for(int c = 0; c < SIZE; ++c) {
        toggle(board, r, c);
        if(click[board] == INT32_MAX) {
          click[board] = 1 + clicks_so_far;
          queue.push(board);
        }
        toggle(board, r, c);
      }
    }
  }
  return min_clicks;
}


namespace algorithms::kattis::graph::flip_five
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
        std::cin >> t_cases;
        while(t_cases--) {
          char cell; 
          int target = 0;
          for(int r = 0; r < SIZE; ++r) {
            for(int c = 0; c < SIZE; ++c) {
              std::cin >> cell;
              if(cell == '*') {
                int bit = r * SIZE + c;
                target |= (1 << bit);
              }
            }
          }
          printf("%d\n", get_min_clicks(target));
        }
    }
}