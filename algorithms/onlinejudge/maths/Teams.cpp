/*
───────────────────────────────────────────────────────────────
🧳 UVa 11609 Teams, https://onlinejudge.org/external/116/11609.pdf, https://oeis.org/A001787, a(n) = n*2^(n-1), rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

using ull = unsigned long long;



namespace algorithms::onlinejudge::maths::teams
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

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          ull team_members;
          scanf("%llu", &team_members);
        // discovery part
        //   ull ways = 0;
        //   for(ull i = 1; i <= (1ULL << team_members) - 1; ++i) {
        //     ways += __builtin_popcount(i);
        //   }
          printf("Case #%d: %llu\n", t_case++, team_members * arith::mod_power<ull>(2ULL, team_members - 1, 1000000007));
        }
    }
}