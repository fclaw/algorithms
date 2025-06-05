/*
───────────────────────────────────────────────────────────────
🧳 UVa 11407 Squares, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <cmath>



typedef std::vector<int> vi;


namespace algorithms::onlinejudge::dp::squares
{
    /** https://onlinejudge.org/external/114/11407.pdf */
    int t_cases, n;
    const int max = 1e5;
    int memo[10001];
    vi dp = vi(10001, max);
    int find_min_terms(int n)
    {
        if(n == 0) return 0;
        if(n == 1) return 1;
 
        int& terms = memo[n];
        if(~terms) return terms;

        terms = max;
        int l = std::sqrt(n);
        for(int k = 1; k <= l; ++k)
          terms = std::min(terms, 1 + find_min_terms(n - k * k));
        return terms;
    }
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

        dp[1] = 1; dp[0] = 0;
        for(int k = 2; k <= 10000; ++k)
          for(int l = 1; l * l <= k; ++l)
            dp[k] = std::min(dp[k], 1 + dp[k - l * l]);

        while_read(t_cases);
        while(t_cases--) {
          while_read(n);
          printf("%d\n", dp[n]);
        }  
    }
}