/*
───────────────────────────────────────────────────────────────
🧳 Apple Division, https://cses.fi/problemset/task/1623/, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../onlinejudge/debug.h"
#include "../aux.h"
#include <bits/stdc++.h>


namespace algorithms::cses::apple_division
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
        
        int apples_n;
        while(stdin_read(apples_n)) {
          vi weights(apples_n);
          ll total_weight = 0;
          for(int i = 0; i < apples_n; ++i) {
            stdin_read(weights[i]);
            total_weight += (ll)weights[i];
          }

          ll min_diff = std::numeric_limits<ll>::max();
          for(int set = 0; set < (1 << apples_n); ++set) {
            ll weight = 0;
            for(int j = 0; j < apples_n; ++j) {
              if(set & (1 << j)) {
                weight += (ll)weights[j];
              }
            }
            min_diff = std::min(min_diff, std::abs(2 * weight - total_weight));
          }
          std::cout << min_diff << "\n";
        }
    }
}
