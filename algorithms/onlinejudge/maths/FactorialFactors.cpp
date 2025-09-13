/*
───────────────────────────────────────────────────────────────
🧳 UVa 884 Factorial Factors, https://onlinejudge.org/external/8/884.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;

using map_ll_i = std::unordered_map<ll, int>;


namespace algorithms::onlinejudge::maths::factorial_factors
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

        primes::sieve(MAX);
        map_ll_i factors;
        for(int n = 2; n <= 1000000; ++n)
          factors[n] += (factors[n - 1] + primes::numPF(n));

        ll num;
        while(scanf("%lld", &num) == 1) {
          printf("%d\n", factors[num]);
        }
    }
}