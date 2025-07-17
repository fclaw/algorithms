/*
───────────────────────────────────────────────────────────────
🧳 UVa 10259 Hippity Hopscotch, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




using pii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

struct State
{
    int r;
    int c;
    int pennies;
};

// For 4-directional movement (up, right, down, left)
const std::vector<pii> dirs_4 = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };


namespace algorithms::onlinejudge::graph::hopscotch
{
    /** https://onlinejudge.org/external/102/10259.pdf */
    int t_cases, N, K;
    bool in_board(int r, int c) { return r >= 0 && r < N && c >= 0 && c < N; }
    int memo[101][101];
    int do_dfs(const State& curr, const vvi& grid) {
      int cr = curr.r;
      int cc = curr.c;
      int c_pennies = curr.pennies;
      int& best = memo[cr][cc];

      if(~memo[cr][cc]) return memo[cr][cc];

      best = 0;
      for(int k = 1; k <= K; ++k) {
        for(const auto& d : dirs_4) {
          int nr = cr + k * d.first;
          int nc = cc + k * d.second;
          if(in_board(nr, nc)) {
            int n_pennies = grid[nr][nc];
            if(n_pennies > c_pennies) { // DAG property
              State next = {nr, nc, n_pennies};
              best = std::max(best, n_pennies + do_dfs(next, grid));
            }
          }
        }
      }
      return best;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        bool first_case = true;
        while_read(t_cases);
        while(t_cases--) {

          // --- THE FIX ---
          if(!first_case) {
            std::cout << std::endl; // Print the blank line separator BEFORE this case
          }
          first_case = false; // It's no longer the first case

          while_read(N, K);
          vvi grid(N, vi(N));
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              while_read(grid[i][j]);
            }
          }

          std::memset(memo, -1, sizeof memo);
          State init = {0, 0, grid[0][0]};
          int max_pennies = grid[0][0] + do_dfs(init, grid);
          std::cout << max_pennies << std::endl;
        }  
    }
}