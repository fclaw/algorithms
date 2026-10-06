/*
───────────────────────────────────────────────────────────────
🧳 UVa 10032 Tug of War, https://onlinejudge.org/external/100/10032.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int Inf = (int)1e9;

using vi = std::vector<int>;



namespace algorithms::onlinejudge::advanced_topics::tug_of_war
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

        bool is_first_case = true;
        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {

          if(!is_first_case) {
            std::cout << std::endl;
          } else {
            is_first_case = false;
          }

          int n;
          std::cin >> n;
          vi weights(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> weights[i];
          }
          int W = std::accumulate(weights.begin(), weights.end(), 0);
          int S = n / 2 + (n % 2);
          std::vector<uint64_t> dp(W + 1);
          dp[0] = 1LL;
          for(int w_i : weights) {
            for(int w = W; w >= w_i; --w) {
              if(dp[w - w_i]) {
                dp[w] |= (dp[w - w_i] << 1);
              }
            }
          }

          int diff = Inf;
          int team_weight = 0;
          int other_team_weight = 0;
          for(int w = 0; w <= W; ++w) {
            if((dp[w] & (1LL << S))) {
              int local_diff = std::abs(W - 2 * w);
              if(diff > local_diff) {
                diff = local_diff;
                team_weight = std::min(w, W - w);
                other_team_weight = std::max(w, W - w);
              }
            }
          }
          printf("%d %d\n", team_weight, other_team_weight);
        }
    }
}