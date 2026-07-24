/*
───────────────────────────────────────────────────────────────
🧳 UVa 11452 Dancing the Cheeky-Cheeky, https://onlinejudge.org/external/114/11452.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




std::string find_dance(const std::string& steps) {
  
  int S = (int)steps.size();
  int period = 0;
  int start = 0;
  for(int p = 1; p <= S / 2; ++p) {
    for(int noise = 0; noise <= S - 2 * p; ++noise) {
      bool is_period = true;
      int curr_start = 0;
      for(int i = noise; i < noise + p; ++i) {
        int next = i + p;
        if(steps[i] != steps[next]) {
          is_period = false;
          curr_start = i;
          break;
        }
      }

      if(is_period) {
        if(period < p) {
          start = curr_start;
        }
        period = std::max(period, p);
      }
    }
  }

  std::string base = steps.substr(start, period);
  std::string continuation = base.substr(S - start - 2 * period, base.length());
  for(int i = 1; i <= 8; ++i) {
    continuation += base; 
  }
  
  return (continuation.substr(0, 8) + "...");
}


namespace algorithms::onlinejudge::strings::cheeky
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
          std::string steps;
          std::cin >> steps;
          std::cout << find_dance(steps) << std::endl;
        }
    }
}