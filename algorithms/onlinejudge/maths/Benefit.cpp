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

constexpr ll MAX = 100000;

namespace algorithms::onlinejudge::maths::benefit
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
       
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          ll a, c;
          scanf("%lld %lld", &a, &c);
          map_ll_i a_factors = primes::getPrimeFactorization(a);
          map_ll_i c_factors = primes::getPrimeFactorization(c);
          bool has_solution = false;
          for(auto& p : c_factors) {
            if(a_factors.count(p.first)) {
              int old = p.second;
              p.second -= a_factors.at(p.first);
              if(p.second == 0)
                c_factors.erase(p.first);
              if(p.second != old) {
                has_solution = true;
              }
            }  
          }
          ll b = 1;
          for(auto& p : c_factors)
            b *= arithmetics::power(p.first, (ll)p.second);


          if(b < a) {
            std::vector<std::pair<ll, int>> xs(a_factors.begin(), a_factors.end());
            std::sort(xs.begin(), xs.end());
            int i = 0;
            while(b < a) {
              for(ll p = 1; p <= (ll)xs[i].second; ++p) {
                b *= arithmetics::power(xs[i].first, p);
                if(b >= a) break;
              }
            }
          }
            
          printf("%s\n", has_solution ? std::to_string(b).c_str() : "NO SOLUTION");  
        }
    }
}