/*
───────────────────────────────────────────────────────────────
🧳 UVa 543 Goldbach’s Conjecture, sieve; complete search; Goldbach’s conjecture, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

using pll = std::pair<ll, ll>;
constexpr ll MAX = 1'000'000;



namespace algorithms::onlinejudge::maths::Goldbach_Conjecture
{
    /** https://onlinejudge.org/external/5/543.pdf */
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
          pll best = {-1, -1};
          ll best_diff = best.second - best.first;
          auto middle = std::upper_bound(v_primes.begin(), v_primes.end(), num >> 1);
          for(auto a = v_primes.begin(); a != middle; ++a) {
            ll b = num - *a;
            if(primes::isPrime(b)) {
              if((!(~best.first) && 
                  !(~best.first)) ||
                 (~best.first &&
                  ~best.second && 
                  (b - *a > best_diff))) {
                best = {*a, b};
                best_diff = b - *a;
              }
            }
          }
          printf("%lld = %lld + %lld\n", num, best.first, best.second);
        }  
    }
}