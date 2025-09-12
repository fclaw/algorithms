/*
───────────────────────────────────────────────────────────────
🧳 UVa 10791 Minimum Sum LCM, https://onlinejudge.org/external/107/10791.pdf, rt: s
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
using map_ll_i = std::unordered_map<ll, int>;


namespace algorithms::onlinejudge::maths::min_sum_lcm
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
        int t_case = 1;
        while(scanf("%lld", &num) == 1 && num) {
          if(num == 1) { printf("Case %d: 2\n", t_case++); continue; }
          if(primes::isPrime(num)) {
            printf("Case %d: %lld\n", t_case++, num + 1);
          } else {
            map_ll_i fac_freq;
            vll factors = primes::primeFactors(num);
            for(ll fac : factors) fac_freq[fac]++;
            int add_1 = fac_freq.size() == 1 ? 1 : 0; 
            ll min_sum = add_1;
            for(auto p : fac_freq) {
              min_sum += arithmetics::power(p.first, (ll)p.second);
            }
            printf("Case %d: %lld\n", t_case++, min_sum);
          }
        }
    }
}