/*
───────────────────────────────────────────────────────────────
🧳 UVa 10680 LCM, rt: s
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

        int n;
        while(scanf("%d", &n) == 1 && n) {
          std::set<ll> ps = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        //   for(int i = 1; i <= n; ++i) {
        //     for(ll fac : primes::primeFactors(i))
        //       ps.insert(fac);
        //   }

        //  dbg(ps);

          ll lcm = 1;
          for(ll p : ps) lcm = arithmetics::__lcm(lcm, p);
          dbg(lcm);
        }
    }
}