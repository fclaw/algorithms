/*
───────────────────────────────────────────────────────────────
🧳 Number Spiral, https://cses.fi/problemset/task/1071, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../onlinejudge/debug.h"
#include "../aux.h"
#include <bits/stdc++.h>

using ll = long long;


namespace algorithms::cses::number_spiral
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
        std::cin >> t_cases;
        while(t_cases--) {
          ll x, y;
          std::cin >> x >> y;
          --x ; --y; // Convert to 0-based indexing
          ll n = std::max(x, y);
        
          ll lower_bound = n * n + 1;
          ll upper_bound = (n + 1) * (n + 1);

          ll ans = 0;
          if(n % 2 == 0) {
            if(x < y){ 
              ans = upper_bound - x;
            } else {
              ans = lower_bound + y;
            }
          } else {
            if(x < y){ 
              ans = lower_bound + x;
            } else {
              ans = upper_bound - y;
            }
          }
          std::cout << ans << "\n";
        }  
    }
}
