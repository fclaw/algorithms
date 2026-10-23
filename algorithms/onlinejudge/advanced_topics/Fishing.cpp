/*
───────────────────────────────────────────────────────────────
🧳 UVa 12870 Fishing, https://onlinejudge.org/external/128/12870.pdf, rt: s
───────────────────────────────────────────────────────────────
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