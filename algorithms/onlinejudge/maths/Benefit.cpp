/*
───────────────────────────────────────────────────────────────
🧳 UVa 11889 Benefit, https://onlinejudge.org/external/118/11889.pdf, Print the lowest integer B such that LCM(A,B) = C, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

auto factors = primes::primeFactors_power;
auto power = arithmetics::power<>;

namespace algorithms::onlinejudge::maths::benefit
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve();

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
       
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          ll a, lcm;
          scanf("%lld %lld", &a, &lcm);
          map_ll_i a_factors = factors(a);
          map_ll_i lcm_factors = factors(lcm);

          ll b = 1;
          bool has_solution = true;
          for(auto& fac : a_factors) {
            auto it = lcm_factors.find(fac.first);
            if(it == lcm_factors.end() ||
               fac.second > it->second) {
              has_solution = false;
              goto finished;
            }
            if(fac.second == it->second) 
              lcm_factors.erase(fac.first);
          }

          for(auto& fac : lcm_factors)
            b *= power(fac.first, fac.second);

          finished:
          printf("%s\n", has_solution ? std::to_string(b).c_str() : "NO SOLUTION");  
        }
    }
}