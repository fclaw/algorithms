/*
───────────────────────────────────────────────────────────────
🧳 UVa 10404 Bachet’s Game, https://onlinejudge.org/external/104/10404.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::maths::bachet_game
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

        int num, n;
        while(scanf("%d %d", &num, &n) == 2) {
          std::vector<int> moves(n);
          for(int i = 0; i < n; ++i) {
            scanf("%d", &moves[i]);
          }
           std::vector<bool> dp(num + 1, false);
           for(int i = 0; i <= num; ++i) {
             for(int m : moves) {
               if(i - m >= 0) {
                 dp[i] = dp[i] || !dp[i - m];
               }
             }
           }
           printf("%s\n", dp[num] ? "Stan wins" : "Ollie wins");
        }
    }
}