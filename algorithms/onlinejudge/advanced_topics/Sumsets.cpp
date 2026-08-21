/*
───────────────────────────────────────────────────────────────
🧳 UVa 10125 Sumsets, https://onlinejudge.org/external/101/10125.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;

struct AB
{
    int a;
    int b;
    int summand;
    // Must be const!
    bool operator < (const AB& other) const {
      return summand < other.summand;
    }
};


namespace algorithms::onlinejudge::advanced_topics::sumsets
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

        int N;
        while(std::cin >> N && N) {
          vi numset(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> numset[i];
          }

          std::sort(numset.begin(), numset.end());

          std::vector<AB> ab_sums;
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              if(i == j) continue;
              int a = numset[i];
              int b = numset[j];
              int summand = a + b;
              ab_sums.push_back({a, b, summand});
            }
          }

          std::sort(ab_sums.begin(), ab_sums.end());

          int max_d = INT32_MIN;
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              if(i == j) continue;
              int c = numset[i];
              int d = numset[j];
              int subtrahend = d - c;

              // 1. Create a dummy object to search by 'summand'
              AB target{0, 0, subtrahend};

              // 2. Find the range of all elements where summand == subtrahend
              auto [start_it, end_it] = std::equal_range(ab_sums.begin(), ab_sums.end(), target);

              // 3. Iterate through all matching sums and check for distinct elements
              for (auto it = start_it; it != end_it; ++it) {
                // Ensure all 4 elements are distinct: a, b, c, d
                if (it->a != c && it->a != d && it->b != c && it->b != d) {
                  max_d = std::max(max_d, d);
                  break; // Found a valid pair, no need to check further for this (c, d)
                }
              }
            }
          }
          if(max_d == INT32_MIN) {
            printf("no solution\n");
          } else {
            std::cout << max_d << std::endl;
          }
        }
    }
}