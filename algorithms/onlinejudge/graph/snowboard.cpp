/*
───────────────────────────────────────────────────────────────
🧳 UVa 10285 Longest Run on a Snowboard, rt: s
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
    int peak;
};

// For 4-directional movement (up, right, down, left)
const std::vector<pii> dirs_4 = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };


namespace algorithms::onlinejudge::graph::snowboard
{
    /** https://onlinejudge.org/external/102/10285.pdf */
    int t_cases, N, M;
    bool in_board(int r, int c) { return r >= 0 && r < N && c >= 0 && c < M; }
    int memo[101][101];
    int do_dfs(const State& curr, const vvi& grid) {

      int cr = curr.r;
      int cc = curr.c;
      int peak = curr.peak;
      int& best = memo[cr][cc];

      if(~memo[cr][cc]) return memo[cr][cc];

      best = 0;
      for(const auto& d : dirs_4) {
        int nr = cr + d.first;
        int nc = cc + d.second;
        int n_peak = grid[nr][nc];
        if(in_board(nr, nc) &&
           // property accounts for turning a grid into DAG
           peak > n_peak) {
          State next = {nr, nc, n_peak};
          best = std::max(best, 1 + do_dfs(next, grid));
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
        
        while_read(t_cases);
        while(t_cases--) {
          std::string area;
          while_read(area, N, M);
          vvi grid(N, vi(M));
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
              while_read(grid[i][j]);
            }
          }
          

          int max_run = 0;
          std::memset(memo, -1, sizeof memo);
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
              State init = {i, j, grid[i][j]};
              max_run = std::max(max_run, 1 + do_dfs(init, grid));
            }
          }
          printf("%s: %d\n", area.c_str(), max_run);  
        }  
    }
}