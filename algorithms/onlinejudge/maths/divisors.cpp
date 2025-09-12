/*
───────────────────────────────────────────────────────────────
🧳 UVa 294 Divisors, https://onlinejudge.org/external/2/294.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;


namespace algorithms::onlinejudge::maths::divisors
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);

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

        ll l, u;
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%lld %lld", &l, &u);
          ll num = l;
          int divs = primes::numDiv(l);;
          for(ll n = l + 1; n <= u; ++n) {
             int curr_divs = primes::numDiv(n);
             if(curr_divs > divs) {
                num = n;
                divs = curr_divs;
             } else if(curr_divs == divs) {
               num = std::min(num, n);
             }
          }
          printf("Between %lld and %lld, %lld has a maximum of %d divisors.\n", l, u, num, divs);
        }
    }
}