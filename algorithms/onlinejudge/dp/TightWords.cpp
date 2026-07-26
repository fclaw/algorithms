/*
───────────────────────────────────────────────────────────────
🧳 UVa 10081 Tight words, https://onlinejudge.org/external/100/10081.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
 



 
 namespace algorithms::onlinejudge::dp::tight_words
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

        int k, n;
        while(std::cin >> k >> n) {

          std::vector<std::vector<double>> dp(n + 1, std::vector<double>(k + 1, 0.0));

          for(int i = 0; i <= k; ++i) {
            dp[1][i] = 1.0 / (k + 1);
          }

          for(int i = 2; i <= n; ++i) {
            for(int j = 0; j <= k; ++j) {
              for(int prev = 0; prev <= k; ++prev) {
                if(std::abs(j - prev) <= 1) {
                  dp[i][j] += dp[i - 1][prev];
                }
              }
              dp[i][j] /= (k + 1);
            }
          }

          // Sum up all probabilities for length n
          double total_prob = 0.0;
          for (int j = 0; j <= k; ++j) {
            total_prob += dp[n][j];
          }

          printf("%0.5f\n", 100 * total_prob);
        }
     }
 }