/*
───────────────────────────────────────────────────────────────
🧳 UVa 10140, Prime Distance, sieve, linear scan for U - L <= 1kk,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

using pll = std::pair<ll, ll>;
constexpr ll MAX = 1000000;



namespace algorithms::onlinejudge::maths::prime_distance
{
    /** ... */
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
    
        ll l, u;
        primes::sieve(MAX);
        vll v_primes = primes::p;
        while(scanf("%lld %lld", &l, &u) == 2) {

          pll min_pair, max_pair;
          int min_diff = INT32_MAX;
          int max_diff = INT32_MIN;
          ll last_prime = -1;
          bool is_solution = false;
          for(ll n = l; n <= u; ++n) {
            if(primes::isPrime(n)) {
              if(~last_prime) {
                int diff = n - last_prime;
                if(min_diff > diff) {
                  min_diff = diff;
                  min_pair = {last_prime, n};
                }
                if(max_diff < diff) {
                  max_diff = diff;   
                  max_pair = {last_prime, n};
                }
                is_solution = true;
              }
              last_prime = n;
            }
          }
          if(!is_solution) printf("There are no adjacent primes.\n");
          else printf("%lld,%lld are closest, %lld,%lld are most distant.\n", min_pair.first, min_pair.second, max_pair.first, max_pair.second);
        }  
    }
}