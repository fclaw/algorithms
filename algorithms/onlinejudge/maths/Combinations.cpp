/*
───────────────────────────────────────────────────────────────
🧳 UVa 369 Combinations, https://onlinejudge.org/external/3/369.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int N_MAX = 100;
constexpr int M_MAX = 100;

using vi = std::vector<int>;
using vvi = std::vector<vi>;



namespace algorithms::onlinejudge::maths::combinations
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

        int n, m;
        while(scanf("%d %d", &n, &m) == 2 && n != 0 && m != 0) {
          vvi dp(N_MAX + 1, vi(M_MAX + 1));
          for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= std::min(i, m); j++) {
              if(j == 0 || j == i) dp[i][j] = 1;
              else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
          }
          printf("%d things taken %d at a time is %d exactly.\n", n, m, dp[n][m]);
        }
    }
}