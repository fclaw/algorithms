/*
───────────────────────────────────────────────────────────────
🧳 UVa 674 Coin Change, https://onlinejudge.org/external/6/674.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;



namespace algorithms::onlinejudge::dp::coin_change
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

        int money;
        vi coins = {1, 5, 10, 25, 50};
        while(std::cin >> money) {

          vi dp(money + 1, 0);
          dp[0] = 1;
          // Outer loop: Process each coin type one by one
          for (int c : coins) {
            // Inner loop: Update the DP table from 'c' up to 'money'
            for (int m = c; m <= money; ++m) {
                dp[m] += dp[m - c];
            }
          }
          std::cout << dp[money] << std::endl;
        }
    }
}