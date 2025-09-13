/*
───────────────────────────────────────────────────────────────
🧳 UVa 10680 LCM, https://onlinejudge.org/external/106/10680.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

constexpr ll MAX = 1000000;
constexpr ll MOD = 10;
using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::lcm
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

          std::vector<int> lcm_factors(num + 1, 0);
           // Loop through pre-computed primes p <= num
          for (ll p : primes::p) {
            if(p > num) { break; }

            ll cp = p;
            int exp = 0;

            // Keep multiplying by p until we exceed num.
            // This avoids repeated power calculations.
            while(cp <= num) {
              exp++;
                  
              // Check for potential overflow before multiplying.
              // This is crucial for large p and num.
              if(cp > num / p) {
                break; 
               }
               cp *= p;
            }
              
            if(exp > 0) {
              lcm_factors[p] = exp;
            }
          }

          if(lcm_factors.size() >= 5) {
            ll count2 = lcm_factors[2];
            ll count5 = lcm_factors[5];
            lcm_factors[5] = 0;
            lcm_factors[2] = count2 - count5;
          }

          ll last_digit = 1;
          for(ll base = 2; base <= num; ++base) {
            ll exp = lcm_factors[base];
            ll term = arithmetics::power_mod(base, exp, MOD);
            last_digit = (last_digit * term) % MOD;
          }
 
          printf("%lld\n", last_digit);
        }
    }
}