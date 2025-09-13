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
 
        std::unordered_map<ll, map_ll_i> map;
        for(ll n = 2; n <= 1000000; ++n)
          map[n] = primes::getPrimeFactorization(n);

        ll num; 
        while(scanf("%lld", &num) == 1 && num) {
          map_ll_i fac_freq;
          for(ll n = 2; n <= num; ++n) {
            for(auto& p : map[n]) {
              fac_freq[p.first] = std::max(p.second, fac_freq[p.first]);
            }
          }

          ll count2 = fac_freq[2];
          ll count5 = fac_freq[5];
          if(count2 > count5) {
            fac_freq.erase(5);
            fac_freq[2] = count2 - count5;
          } else {
            fac_freq.erase(2);
            fac_freq[5] = count5 - count2;
          }

          ll last_digit = 1;
          for(auto fac : fac_freq) {
            ll term = arithmetics::power_mod(fac.first, fac.second, MOD);
            last_digit = (last_digit * term) % MOD;
          }
 
          printf("%lld\n", last_digit);
        }
    }
}