/*
───────────────────────────────────────────────────────────────
🧳 UVa 10350 Liftless EME, https://onlinejudge.org/external/103/10350.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

namespace algorithms::onlinejudge::graph::liftless_EME
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


        std::string case_name;
        while(stdin_read(case_name)) {
          int N, M;
          stdin_read(N, M);
          vvi dp(N, vi(M, Inf));

          // 1. Base Case: Ground floor starts at 0 for all holes
          for(int i = 0; i < M; ++i) {
            dp[0][i] = 0;
          }

          // 2. Transition through the floors (k = 0 to n - 2)
          for (int k = 0; k < N - 1; ++k) {
            for (int i = 0; i < M; ++i) { // Current hole on floor k
              for (int j = 0; j < M; ++j) { // Target hole on floor k + 1
                int walk_time;
                stdin_read(walk_time);
                dp[k + 1][j] = std::min(dp[k + 1][j], dp[k][i] + walk_time + 2);
              }
            }
          }

          // 3. Final Answer at floor n - 1
          int ans = Inf;
          for (int i = 0; i < M; ++i) {
            ans = std::min(ans, dp[N - 1][i]);
          }
          std::cout << case_name << "\n" << ans << "\n";
        }
    }
}
