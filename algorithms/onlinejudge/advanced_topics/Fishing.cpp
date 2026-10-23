/*
───────────────────────────────────────────────────────────────
🧳 UVa 12870 Fishing, https://onlinejudge.org/external/128/12870.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ====================================================================================
 * OPTIMIZATION COMMENTARY: 2D SUFFIX MAXIMUM FOR O(R * C * E) DYNAMIC PROGRAMMING
 * ====================================================================================
 * 
 * 1. THE BRUTE FORCE PROBLEM (O(R^2 * C^2 * E) -> TLE)
 * ---------------------------------------------------
 * In the naive approach, computing the maximum profit for choosing 'e' fishing spots 
 * starting from cell (i, j) requires iterating over all possible next spots (p, l) 
 * such that p > i and l > j:
 * 
 *      f(i, j, e) = val(i, j) + max_{p > i, l > j} { f(p, l, e - 1) }
 * 
 * Searching every valid (p, l) pair inside the bottom-right subgrid introduces two 
 * nested loops of size R and C inside our main state loops, yielding a catastrophic 
 * O(R^2 * C^2 * E) time complexity that causes an instant Time Limit Exceeded (TLE).
 * 
 * 
 * 2. RECONCILING THE SUBGRID VIA REGION COMPOSITION
 * --------------------------------------------------
 * To eliminate the nested subgrid search, we introduce an auxiliary DP table, g(i, j, e),
 * defined as the maximum value of f(p, l, e) for any cell in the bounding suffix region 
 * extending from (i, j) to the bottom-right corner (Rows-1, Cols-1).
 * 
 * Geometrically, the suffix subgrid starting at (i, j) can be decomposed into three 
 * overlapping parts:
 * 
 *      +------------+------------+     Legend:
 *      |  (i, j)    |  Region B  |     - (i, j):   The standalone current cell ("Blind Spot").
 *      |  [dp/f]    |  [g(i,j+1)]|     - Region B: Suffix grid from the right neighbor (i, j+1).
 *      +------------+------------+     - Region C: Suffix grid from the bottom neighbor (i+1, j).
 *      |  Region C  | Overlap    |
 *      |  [g(i+1,j)]| (g(i+1,j+1)|     Note: The "Overlap" region is fully contained within 
 *      +------------+------------+     both Region B and Region C.
 * 
 * 
 * 3. THE MATHEMATICAL IDEMPOTENCY OF MAX()
 * ----------------------------------------
 * In standard 2D Prefix/Suffix sums (like finding an area total), overlapping regions 
 * must be subtracted to avoid double-counting. However, because our target operator 
 * is MAX(), we can exploit its idempotent property:
 * 
 *      max(x, x) = x
 * 
 * Overlapping queries do not distort or corrupt the maximum value. Therefore, Region B 
 * and Region C can overlap completely without consequence. Combining them covers every 
 * cell in the subgrid *except* for the top-left coordinate (i, j) itself. 
 * 
 * By including the value of the current cell—our "Blind Spot"—we achieve 100% gapless 
 * coverage of the entire suffix subgrid in exactly O(1) constant time.
 * 
 * 
 * 4. SYSTEM OF RECURRENCES
 * ------------------------
 * Executing in a bottom-up direction (from Rows-1 down to 0, and Cols-1 down to 0), 
 * the transitions reduce to two elegant, intertwined O(1) steps:
 * 
 *    Step 1: Compute optimal state for the current spot 'e' using the strict subgrid.
 *            f(i, j, e) = val(i, j) + g(i + 1, j + 1, e - 1)
 * 
 *    Step 2: Update the suffix maximum table to include the new cell for future lookups.
 *            g(i, j, e) = max({ g(i + 1, j, e), g(i, j + 1, e), f(i, j, e) })
 * 
 * 
 * 5. COMPLEXITY REDUCTION RESULT
 * ------------------------------
 * - Old Time Complexity: O(R^2 * C^2 * E)
 * - New Time Complexity: O(R * C * E)  --> Guaranteed Accepted (AC)
 * ====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"





void go_fishing(const vvi& ocean, vvvi& dp, int rows, int cols, int max_events) {

  vvvi max_dp(rows + 1, vvi(cols + 1, vi(max_events + 1, 0)));

  // Base Case: 1 event
  for (int r = rows - 1; r >= 0; --r) {
    for(int c = cols - 1; c >= 0; --c) {
      dp[r][c][1] = ocean[r][c];
      // Maintain suffix max for 1 event
      max_dp[r][c][1] = std::max({dp[r][c][1], max_dp[r + 1][c][1], max_dp[r][c + 1][1]});
    }
  }

  for(int r = rows - 2; r >= 0; --r) {
    for(int c = cols - 2; c >= 0; --c) {
      for(int e = 2; 2 * e <= max_events; ++e) {
        // 1. Calculate current DP spot using the optimal next subgrid state in O(1)
        dp[r][c][e] = std::max(dp[r][c][e], ocean[r][c] + max_dp[r + 1][c + 1][e - 1]);
        max_dp[r][c][e] = std::max({dp[r][c][e], max_dp[r + 1][c][e], max_dp[r][c + 1][e]});
      }
    }
  }
}


void go_nourishing(const vvi& ocean, vvvi& dp, int rows, int cols, int max_events) {

  vvvi min_dp(rows + 1, vvi(cols + 1, vi(max_events + 1, Inf)));

  // Base Case: 1 event
  for (int r = rows - 1; r >= 0; --r) {
    for(int c = cols - 1; c >= 0; --c) {
      dp[r][c][1] = ocean[r][c];
      // Maintain suffix min for 1 event
      min_dp[r][c][1] = std::min({dp[r][c][1], min_dp[r + 1][c][1], min_dp[r][c + 1][1]});
    }
  }

  for(int r = rows - 2; r >= 0; --r) {
    for(int c = cols - 2; c >= 0; --c) {
      for(int e = 2; e <= max_events; ++e) {
        // 1. Calculate current DP spot using the optimal next subgrid state in O(1)
        dp[r][c][e] = std::min(dp[r][c][e], ocean[r][c] + min_dp[r + 1][c + 1][e - 1]);
        min_dp[r][c][e] = std::min({dp[r][c][e], min_dp[r + 1][c][e], min_dp[r][c + 1][e]});
      }
    }
  }
}



namespace algorithms::onlinejudge::advanced_topics::fishing
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
        stdin_read(t_cases);
        while(t_cases--) {
          int rows, cols;
          stdin_read(rows, cols);
          int max_events = std::min(rows, cols);

          vvi ocean(rows, vi(cols));
          for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
              stdin_read(ocean[i][j]);
            }
          }

          vvvi dp_fishing(rows, vvi(cols, vi(max_events + 1, 0)));
          vvvi dp_nourishing(rows, vvi(cols, vi(max_events + 1, Inf)));

          go_fishing(ocean, dp_fishing, rows, cols, max_events);
          go_nourishing(ocean, dp_nourishing, rows, cols, max_events);

          vi profit(max_events + 1, 0);
          vi expenses(max_events + 1, Inf);
        
          for(int e = 1; e <= max_events; ++e) {
            for(int i = 0; i < rows; ++i) {
              for(int j = 0; j < cols; ++j) {
                profit[e] = std::max(profit[e], dp_fishing[i][j][e]);
                if(dp_nourishing[i][j][e] != Inf) {
                  expenses[e] = std::min(expenses[e], dp_nourishing[i][j][e]);
                }
              }
            }
          }

          int lump_sum_benefit = 0;
          for(int e = 1; 2 * e <= max_events; ++e) {
            if(expenses[2 * e] != Inf) {
              lump_sum_benefit = std::max(lump_sum_benefit, profit[e] - expenses[2 * e]);
            }
          }
          printf("%d\n", lump_sum_benefit);
        }
    }
}