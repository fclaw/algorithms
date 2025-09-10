/*
───────────────────────────────────────────────────────────────
🧳 UVa 583  Prime Factors   rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;


namespace algorithms::onlinejudge::maths::prime_factors
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
          std::string s;
          if(num < 0) s = "-1 x ";
          vll factors = primes::primeFactors(std::abs(num));
          for(ll fac : factors) s += std::to_string(fac) + " x ";
          s.pop_back();
          s.pop_back();
          s.pop_back();
          printf("%lld = %s\n", num, s.c_str());
        }
    }
}