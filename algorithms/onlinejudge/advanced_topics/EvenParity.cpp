/*
───────────────────────────────────────────────────────────────
🧳 UVa 11464 Even Parity, https://onlinejudge.org/external/114/11464.pdf, rt: s
───────────────────────────────────────────────────────────────
💡 UVa 11464 - Even Parity
   URL: https://onlinejudge.org/external/114/11464.pdf
   Verdict: Accepted | Runtime: 0.450s (In-Place Recursive Backtracking)

   Algorithmic Summary & Design Principles:

   1. In-Place State Restoration (Zero Allocation Optimization):
      Deep copying a 2D vector (`vvii old = grid`) at every node of a deep recursion 
      tree incurs massive 'malloc' heap allocation and memory copy overhead (causing TLE).
      
      By replacing the deep copy with explicit, symmetric state mutation functions:
         - Forward step:  transform_0_to_1({r, c}, grid, ...)
         - Backward step: transform_1_to_0({r, c}, grid, ...)
      we perform backtracking in-place with O(1) memory overhead per stack frame, 
      keeping the CPU L1 cache warm and dropping runtime to 0.450s.

   2. The Forced Value Rule (For Rows r >= 1):
      To make cell (r-1, c) have EVEN parity, its lower neighbor cell (r, c) is 
      the absolute last cell in the search that can affect it:
        - If cell (r-1, c) currently has ODD parity, cell (r, c) MUST become 1 
          (should_0_change = true) to fix the upper neighbor.
        - Pruning Conflict: If cell (r, c) is an original '1', but upper cell 
          (r-1, c) remains ODD, the path is mathematically dead (we cannot change 
          1 to 0). We prune immediately.

   3. Left Diagonal Parity Validation:
      In row-major order (0,0 ... r,c), cell (r-1, c-1) is permanently finalized 
      once we reach (r, c). 'check_left_diagonals_parity' verifies that (r-1, c-1) 
      is EVEN before making deeper recursive calls.

   4. Base Case Verification (r == N):
      The parity of Row N-1 (the bottom row) cannot be fixed by any lower row. 
      Therefore, global matrix validity (even_parities_cells == N * N) must be 
      verified at r == N.
───────────────────────────────────────────────────────────────────────────────
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

void transform_1_to_0(ii cell, vvii& grid, int N) {
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
      parity--;
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

  // Advance to next row if we reach the end of the columns
  if (c == N) {
    r++;
    c = 0;
  }

  // Base Case: All N rows processed. Verify global matrix parity
  if (r == N) {
    if (even_parities_cells == N * N) {
      best = std::min(best, sol);
    }
    return;
  }

  // Pruning: Conflict check. If cell (r-1, c) is ODD, but cell (r, c) is already 1 
  // and cannot be flipped, the upper neighbor can never be fixed.
  if (r >= 1 && grid[r][c].first == 1 && (grid[r - 1][c].second % 2 != 0)) {
    return;
  }

  // Pruning: Cost branch-and-bound
  if (sol >= best) {
    return;
  }

  // Determine if a 0-to-1 transformation is FORCED by the row above
  bool should_0_change = false;
  if (r >= 1 && (grid[r - 1][c].second % 2)) {
    should_0_change = true; // Upper neighbor is ODD, we MUST change 0 to 1
  }

  // --- Branch 1: Change cell (r, c) from 0 to 1 ---
  if (!grid[r][c].first && (r == 0 || should_0_change)) {
    int curr_even_parities_cells = even_parities_cells;
    
    // In-place forward state transformation (Zero Allocation)
    transform_0_to_1({r, c}, grid, curr_even_parities_cells, N);
    grid[r][c].first = 1;
  
    // Validate finalized top-left neighbor before recursing
    if (check_left_diagonals_parity(r, c, grid, N)) {
      backtrack(r, c + 1, grid, N, curr_even_parities_cells, sol + 1, best);
    }

    // In-place backward state restoration (Zero Allocation)
    transform_1_to_0({r, c}, grid, N);
    grid[r][c].first = 0;
  }

  // --- Branch 2: Keep cell (r, c) as 0 ---
  if (check_left_diagonals_parity(r, c, grid, N)) {
    backtrack(r, c + 1, grid, N, even_parities_cells, sol, best);
  }
}


int min_transformation_required(vvii& grid, int N, int even_parities_cells) {
  int ans = INT32_MAX;
  backtrack(0, 0, grid, N, even_parities_cells, 0, ans);
  return ans == INT32_MAX ? -1 : ans;
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