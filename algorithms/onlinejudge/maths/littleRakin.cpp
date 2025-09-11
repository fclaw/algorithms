/*
───────────────────────────────────────────────────────────────
🧳 UVa 12703 Little Rakin, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000;

using vi = std::vector<int>;

namespace algorithms::onlinejudge::maths::little_rakin
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);
        vll v_primes = primes::p;

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
          int n, zero, one;
          scanf("%d %d %d", &n, &zero, &one);
          vll zero_factors = primes::primeFactors(zero);
          vll one_factors = primes::primeFactors(one);

          vi fib_n_2(MAX); // F(n - 2)
          vi fib_n_1(MAX); // F(n - 1)
          for(ll fac : zero_factors) fib_n_2[fac]++;
          for(ll fac : one_factors) fib_n_1[fac]++;

          vi fib_curr(MAX);
          for(int i = 2; i <= n; ++i) {
            for(int j = 0; j < MAX; ++j)
              fib_curr[j] = fib_n_2[j] + fib_n_1[j];
            fib_n_2 = fib_n_1; 
            fib_n_1 = fib_curr; 
          }
          
          for(int fac = 2; fac < MAX; ++fac) {
            if(fib_curr[fac] > 0) 
              printf("%d %d\n", fac, fib_curr[fac]);
          }
          if(t_cases) printf("\n");
        }
    }
}