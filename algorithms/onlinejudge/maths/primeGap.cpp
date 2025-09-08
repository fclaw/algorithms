/*
───────────────────────────────────────────────────────────────
🧳 UVa 1644 Prime Gap, sieve; prime check, upper bound - lower bound, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1'300'000;


namespace algorithms::onlinejudge::maths::prime_gap
{
    /** https://onlinejudge.org/external/16/1644.pdf */
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

        ll num;
        primes::sieve(MAX); // generation of primes up to 1_000_000
        vll v_primes = primes::p;
        while(scanf("%lld", &num) == 1 && num) {
          int gap = 0;
          if(!primes::isPrime(num)) {
            auto next_prime = std::upper_bound(v_primes.begin(), v_primes.end(), num);
            auto prev_prime = next_prime - 1;
            gap = *next_prime - *prev_prime;
          }
          printf("%d\n", gap);
        }  
    }
}