/*
───────────────────────────────────────────────────────────────
🧳 UVa 10879 Code Refactoring, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


namespace algorithms::onlinejudge::maths::code_refactoring
{
    /** https://onlinejudge.org/external/108/10879.pdf */
    int t_cases, k, t_case = 1;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(k);
          std::vector<std::pair<int, int>> factors;
          for (int fac = 2; fac * fac <= k; ++fac) {
            if (k % fac == 0) {
              // We found a pair of factors: (i, k/i)
              // Both i and k/i will be greater than 1.
              factors.push_back({fac, k / fac});
            }
            if(factors.size() == 4) break;
          }
          int a = factors[0].first;
          int b = factors[0].second;
          int c = factors[1].first;
          int d = factors[1].second;
          printf("Case #%d: %d = %d * %d = %d * %d\n", t_case++, k, a, b, c, d);
        }
    }
}