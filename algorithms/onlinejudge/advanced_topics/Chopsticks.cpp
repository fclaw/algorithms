/*
───────────────────────────────────────────────────────────────
🧳 UVa 10271 Chopsticks, https://onlinejudge.org/external/102/10271.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int Inf = (int)1e9;


using vi = std::vector<int>;

int cache[5005][1005]; // Cache for memoization, initialized to -1


int dp(int idx, int remaining_pairs, const vi& lengths) {

  if(remaining_pairs == 0) return (cache[idx][remaining_pairs] = 0); // Base case: no more pairs to form
  if(3 * remaining_pairs > (int)lengths.size() - idx) {
    return (cache[idx][remaining_pairs] = Inf); // Not enough sticks left to form the required pairs
  }

  if(~cache[idx][remaining_pairs]) {
    return cache[idx][remaining_pairs]; // Return cached result
  }

  int best = Inf;
  // Option 1: Form a pair with the current stick and the next one
  int badness = (lengths[idx + 1] - lengths[idx]) * (lengths[idx + 1] - lengths[idx]);
  int take = dp(idx + 2, remaining_pairs - 1, lengths);
  best = std::min(best, badness + take);
  // Option 2: Skip the current stick and try to form pairs with the next sticks
  int skip = dp(idx + 1, remaining_pairs, lengths);

  return (cache[idx][remaining_pairs] = std::min(best, skip));
}


int get_minimum_badness(int k, const vi& lengths) {
  std::memset(cache, -1, sizeof(cache)); // Reset cache for new test case
  return dp(0, k + 8, lengths);
}


namespace algorithms::onlinejudge::advanced_topics::chopsticks
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
          int k, n;
          std::cin >> k >> n;
          vi lengths(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> lengths[i];
          }
          printf("%d\n", get_minimum_badness(k, lengths));
        }
    }
}