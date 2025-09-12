/*
───────────────────────────────────────────────────────────────
🧳 UVa 10484, Divisibility of Factors, https://onlinejudge.org/external/104/10484.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 100;

using ull = unsigned long long;
using map_ll_i = std::unordered_map<ll, int>;


namespace algorithms::onlinejudge::maths::divisibility_of_factors
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);
        vll primes = primes::p;

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

        int n, d;
        while(scanf("%d %d", &n, &d) == 2) {
          if(!n && !d) break;
          
          d = std::abs(d);

          if(d == 1) {
            // If D=1, all factors of N! are divisible by 1.
            // We need to count the total number of factors of N!.
            ull total_factors = 1;
            for(ll p : primes::p) {
              total_factors *= (primes::legendre(n, p) + 1);
            }
            printf("%llu\n", total_factors);
            continue;
          }

          map_ll_i d_primes;
          vll factors = primes::primeFactors(d);
          for(ll fac : factors) d_primes[fac]++;

          // Calculate the product of choices for each prime's exponent
          ull ways = 1;
          bool possible = true;
          // Iterate through all primes <= N that could be factors of N!
          for(ll p : primes::p) {
            // Get max power of p in N!
            ll max_power = primes::legendre(n, p);

            // Get required min power of p from D's factorization
            int min_power = 0;
            if(d_primes.count(p)) {
              min_power = d_primes[p];
            }
            // Check if a solution is possible
            if (max_power < min_power) {
                possible = false;
                break;
            }
            // Number of choices for this prime's exponent is (max - min + 1)
            ways *= (max_power - min_power + 1);
          }

          // Final check for primes in D that are > N
         if(possible) {
           for(auto const& [p, power] : d_primes) {
             if(p > n) { // If D has a prime factor larger than N...
               possible = false; // ...then N! cannot be divisible by it.
               break;
              }
           }
         }

         printf("%llu\n", possible ? ways : 0);
        }
    }
}