/*
───────────────────────────────────────────────────────────────
🧳 UVa 12712 Pattern Locker, https://onlinejudge.org/external/127/12712.pdf,   rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

using ull = unsigned long long;

constexpr ull MOD = 10000000000007ULL;


namespace algorithms::onlinejudge::maths::pattern_locker
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


        int t_cases, l, m, n, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d %d", &l, &m, &n);

          ull total_ways = 0;
          ull total_dots = (ull)(l * l);
          // The loop to sum up P(total_dots, k) for k from m to n.
          for(int i = m; i <= n; i++) {
            ull fact = 1;
            for(ull j = total_dots - i + 1; j <= total_dots; j++)
              fact = (fact * j) % MOD;
            total_ways = (total_ways + fact) % MOD;
          }
          printf("Case %d: %llu\n", t_case++, total_ways);
        }
    }
}