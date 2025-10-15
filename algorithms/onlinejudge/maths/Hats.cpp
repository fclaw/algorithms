/*
───────────────────────────────────────────────────────────────
🧳 UVa 12024 Hats, https://onlinejudge.org/external/120/12024.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;
using v_ull = std::vector<ull>;

constexpr int MAX_FACT = 12;


ull count_derangements(int n) {
  v_ull dp(n + 1);
  // Base cases
  dp[1] = 0; // one element,
  dp[2] = 1; // two elements

  for(int i = 3; i <= n; i++)
    dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);

  return dp[n];
}


namespace algorithms::onlinejudge::maths::hats
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


        v_ull factorials(MAX_FACT + 1);
        factorials[1] = 1ULL;
        for(ull i = 2; i <= MAX_FACT; ++i)
          factorials[i] = i * factorials[i - 1];
        
        int t_cases, n;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d", &n);
          ull all_outcomes = factorials[n];
          ull derangements = count_derangements(n);
          printf("%llu/%llu\n", derangements, all_outcomes);
        }
    }
}