
/*
───────────────────────────────────────────────────────────────
🧳 UVa 106 Fermat vs. Pythagoras, https://onlinejudge.org/external/1/106.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include "utility/primes.cpp"
#include <bits/stdc++.h>




namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;
namespace primes = algorithms::onlinejudge::maths::utility::primes;

using ld = long double;
using ull = unsigned long long;

auto ___gcd = arithmetics::__gcd<ull>;

namespace algorithms::onlinejudge::maths::Fermat_vs_Pythagoras
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
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

        std::unordered_map<ull, ull> squared;
        for(ull i = 1; i <= 500000; ++i) {
            squared[i * i] = i;
        }

        ull n;
        while(scanf("%llu", &n) == 1) {
          int prime_triples = 0;
          int no_prime_triples = 0;
          for(ull z = 1; z <= n; ++z) {
            ull start = std::ceil(z / std::sqrt(2));
            ull c = z * z;
            for(ull y = start; y < z; ++y) { // 2 * y^2 > z^2
              if(___gcd(z, y) == 1) {
                if(auto it = squared.find(c - y * y); 
                   it != squared.end()) {
                //   if(___gcd(y, (ull)(it->second)) == 1)
                    prime_triples++;
                  }
              }
            }
          }
          printf("%d %d\n", prime_triples, no_prime_triples);
        }
    }
}