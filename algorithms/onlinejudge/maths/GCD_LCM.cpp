/*
───────────────────────────────────────────────────────────────
🧳 UVa 11388 GCD LCM, https://onlinejudge.org/external/113/11388.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


using ull = unsigned long long;
auto ___gcd = arithmetics::__gcd<ull>;


namespace algorithms::onlinejudge::maths::GCD_LCM
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
        scanf("%d", &t_cases);
        while(t_cases--) {
          ull g, l;
          scanf("%llu %llu", &g, &l);
          if((l % g)) {
            printf("-1\n");
          } else {
            ull first = -1, second;
            ull ratio = l / g; // lcm(a, b) = (a * b) / gcd(a, b) => a = a1 * gcd, b = b1 * gcd => a1 and b1 are co-prime 
            ull bound = std::floor(std::sqrt(ratio));
            for(ull a = 1; a <= bound; ++a) {
              if(!(ratio % a) && 
                 ___gcd(ratio / a, a) == 1) {
                first = a * g;
                second = (ratio / a) * g;
                goto finished;
              }
            }
            finished: first == (ull)-1 ? printf("-1\n") : printf("%llu %llu\n", first, second);
          }
        }
    }
}