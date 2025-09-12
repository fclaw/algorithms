/*
───────────────────────────────────────────────────────────────
🧳 UVa 10179 Irreducible Basic Fractions, https://onlinejudge.org/external/101/10179.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;


namespace algorithms::onlinejudge::maths::irreducible_basic_fractions
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

        ll num;
        while(scanf("%lld", &num) == 1 && num) {
          printf("%lld\n", primes::EulerPhi(num));
        }
    }
}