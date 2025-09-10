/*
───────────────────────────────────────────────────────────────
🧳 UVa 11466 Largest Prime Divisor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 5000000;


namespace algorithms::onlinejudge::maths::lpd
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);
        vll v_primes = primes::p;

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
          vll factors = primes::primeFactors(std::abs(num));
          bool is_one_divisor = true;
          if(factors.size() > 1) { 
            ll div = factors.front();
            for(ll fac : factors) {
              is_one_divisor &= (div == fac);
            }
          }
          printf("%lld\n", factors.size() <= 1 || is_one_divisor ? -1 : factors.back());
        }
    }
}