/*
───────────────────────────────────────────────────────────────
🧳 UVa 10192 Vacation, https://onlinejudge.org/external/101/10192.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;


namespace algorithms::onlinejudge::strings::holiday
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

        int t_case = 1;
        std::string first, second;
        while(std::getline(std::cin, first) && first != "#") {
          std::getline(std::cin, second);
          
          vvi dp(first.size() + 1, vi(second.size() + 1, 0));

          for(int i = 1; i <= (int)first.size(); ++i) {
            for(int j = 1; j <= (int)second.size(); ++j) {
              if(first[i - 1] == 
                 second[j - 1]) {
                dp[i][j] = std::max(dp[i][j], 1 + dp[i - 1][j - 1]);
              }
              dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
              dp[i][j] = std::max(dp[i][j], dp[i][j - 1]);
            }
          }

          printf("Case #%d: you can visit at most %d cities.\n", t_case++, dp[first.size()][second.size()]);
        }
    }
}