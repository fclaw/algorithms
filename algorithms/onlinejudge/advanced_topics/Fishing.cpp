/*
───────────────────────────────────────────────────────────────
🧳 UVa 12870 Fishing, https://onlinejudge.org/external/128/12870.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"





void run_dp_fishing(const vvi& ocean, vvvi& dp, int rows, int cols, int max_k) {
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      dp[r][c][1] = ocean[r][c];
    }
  }

  for(int r = rows - 2; r >= 0; --r) {
    for(int c = cols - 2; c >= 0; --c) {
      for(int k = 1; k <= max_k; ++k) {
        for(int p = r + 1; p < rows; ++p) {
          for(int l = c + 1; l < cols; ++l) {
            dp[r][c][k] = std::max(dp[r][c][k], ocean[r][c] + dp[p][l][k - 1]);
          }
        }
      }
    }
  }
}


void run_dp_nourishing(const vvi& ocean, vvvi& dp, int rows, int cols, int max_k) {
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < cols; ++c) {
      dp[r][c][1] = ocean[r][c];
    }
  }

  for(int r = rows - 2; r >= 0; --r) {
    for(int c = cols - 2; c >= 0; --c) {
      for(int k = 2; k <= max_k; ++k) {
        for(int p = r + 1; p < rows; ++p) {
          for(int l = c + 1; l < cols; ++l) {
            dp[r][c][k] = std::min(dp[r][c][k], ocean[r][c] + dp[p][l][k - 1]);
          }
        }
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
          int max_k = std::min(rows, cols);

          vvi ocean(rows, vi(cols));
          for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
              stdin_read(ocean[i][j]);
            }
          }

          vvvi dp_fishing(rows, vvi(cols, vi(max_k + 1, 0)));
          vvvi dp_nourishing(rows, vvi(cols, vi(max_k + 1, Inf)));

          run_dp_fishing(ocean, dp_fishing, rows, cols, max_k);
          run_dp_nourishing(ocean, dp_nourishing, rows, cols, max_k);

          vi profit(max_k + 1, 0);
          vi expenses(max_k + 1, Inf);
        
          for(int k = 1; k <= max_k; ++k) {
            for(int i = 0; i < rows; ++i) {
              for(int j = 0; j < cols; ++j) {
                profit[k] = std::max(profit[k], dp_fishing[i][j][k]);
                if(dp_nourishing[i][j][k] != Inf) {
                  expenses[k] = std::min(expenses[k], dp_nourishing[i][j][k]);
                }
              }
            }
          }

          int lump_sum_benefit = 0;
          for(int k = 1; 2 * k <= max_k; ++k) {
            if(expenses[2 * k] != Inf) {
              lump_sum_benefit = std::max(lump_sum_benefit, profit[k] - expenses[2 * k]);
            }
          }
          printf("%d\n", lump_sum_benefit);
        }
    }
}