/*
───────────────────────────────────────────────────────────────
🧳 UVa 11464 Even Parity, https://onlinejudge.org/external/114/11464.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;


// 4-directional grid offsets: {dr, dc}
const vii dirs4 = {
    {-1,  0}, // 1. North (Up)
    { 0,  1}, // 3. East (Right)
    { 1,  0}, // 5. South (Down)
    { 0, -1}, // 7. West (Left)
};


void transform_0_to_1(ii cell, vvii& grid, int& even_parities_cells, int N) {
  int r = cell.first;
  int c = cell.second;
  for(ii d : dirs4) {
    int adj_i = r + d.first;
    int adj_j = c + d.second;
    if(adj_i >= 0 && 
       adj_i < N && 
       adj_j >= 0 &&
       adj_j < N) {
      int& parity = grid[adj_i][adj_j].second;
      parity++;
      if(!(parity % 2)) {
        even_parities_cells++;
      } else {
        even_parities_cells--;
      }
    }
  }
}


bool check_left_diagonals_parity(int r, int c, const vvii& grid, int N) {
  // Check top-left light (r - 1, c - 1): Permanently finalized by cell (r, c)  
  if(r - 1 >= 0 && 
     c - 1 >= 0) {
    int parity = grid[r - 1][c - 1].second;
    if(parity % 2) {
      return false;
    }
  }

  // End-of-Row Check: When at the last column (c == C - 1), 
  // the top-right light (r - 1, C - 1) is ALSO permanently finalized!
  if (c == N - 1 && 
      r - 1 >= 0) {
    int parity = grid[r - 1][c].second;
    if(parity % 2) {
      return false;
    }  
  }

  return true; // Valid progress, continue searching
}


void backtrack(int r, int c, vvii& grid, int N, int even_parities_cells, int sol, int& best) {

  if(c == N) {
    r++;
    c = 0;
  }

  if(r == N) {
    if(even_parities_cells == N * N) {
      best = std::min(best, sol);
    }
    return;
  }

  if(r >= 1 && grid[r][c].first == 1 && (grid[r - 1][c].second % 2 != 0)) {
    return;
  }

  if(sol >= best) {
    return;
  }

  bool should_0_change = true;
  if(r >= 1 && !(grid[r - 1][c].second % 2)) {
    should_0_change = false;
  }

  if(!grid[r][c].first && 
     should_0_change) {
    int curr_even_parities_cells = even_parities_cells;
    vvii old = grid;
    transform_0_to_1({r, c}, grid, curr_even_parities_cells, N);

    grid[r][c].first = 1;
  
    if(check_left_diagonals_parity(r, c, grid, N)) {
      backtrack(r, c + 1, grid, N, curr_even_parities_cells, sol + 1, best);
    }

    grid = old; // backtrack
    grid[r][c].first = 0;
  }

  if(check_left_diagonals_parity(r, c, grid, N)) {
    backtrack(r, c + 1, grid, N, even_parities_cells, sol, best);
  }

}


int min_transformation_required(vvii& grid, int N, int even_parities_cells) {
  int ans = INT32_MAX; 
  backtrack(0, 0, grid, N, even_parities_cells, 0, ans);
  if(ans == INT32_MAX) {
    ans = -1;
  }
  return ans;
}


namespace algorithms::onlinejudge::advanced_topics::even_parity
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

        int t_cases, N, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> N;
          vvii grid(N, vii(N));
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              std::cin >> grid[i][j].first; 
            }
          }

          int even_parities_cells = 0;
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              int parity = 0;
              for(ii d : dirs4) {
                int adj_i = i + d.first;
                int adj_j = j + d.second;
                if(adj_i >= 0 && 
                   adj_i < N && 
                   adj_j >= 0 &&
                   adj_j < N) {
                  if(grid[adj_i][adj_j].first) {
                    parity++;
                  }
                }
              }
              grid[i][j].second = parity;
              if(!(parity % 2)) {
                even_parities_cells++;
              }
            }
          }
          printf("Case %d: %d\n", t_case++, min_transformation_required(grid, N, even_parities_cells));
        }
    }
}