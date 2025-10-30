/*
───────────────────────────────────────────────────────────────
🧳 UVa 711 Dividing up, https://onlinejudge.org/external/7/711.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi =  std::vector<int>;

constexpr int NUM_PILES = 6;

bool read_piles(vi& piles) {
  bool all_zero = true;
  for(int i = 0; i < NUM_PILES; ++i) {
   std::cin >> piles[i];
   all_zero = all_zero && (piles[i] == 0);
  }
  return !all_zero;
}


namespace algorithms::onlinejudge::advanced_topics::marbles
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

        int t_cases = 1;
        vi piles(NUM_PILES);
        bool is_first = true;
        while(read_piles(piles)) {
        }
    }
}