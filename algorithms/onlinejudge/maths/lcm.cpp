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
using ull = unsigned long long;
using map_ll_i = std::unordered_map<ll, int>;


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
          map_ll_i fac_freq;
          for(ll i = 2; i <= num; ++i) {
            map_ll_i curr_fac_freq;
            vll factors = primes::primeFactors(i);
            for(ll fac : factors) curr_fac_freq[fac]++;
            for(auto& p : curr_fac_freq) {
              fac_freq[p.first] = std::max(p.second, fac_freq[p.first]);
            }
          }
        }
    }
}