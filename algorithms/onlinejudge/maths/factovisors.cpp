/*
───────────────────────────────────────────────────────────────
🧳 UVa 10139, Factovisors, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000000;

using map_ii = std::unordered_map<int, int>;
using ii = std::pair<int, int>;


namespace algorithms::onlinejudge::maths::factovisors
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

        int n, m;
        while(scanf("%d %d", &n, &m) == 2) {
          map_ii m_factors_power;
          for(ll fac : primes::primeFactors(m))
            m_factors_power[fac]++;

          bool is_m_divides_n = true;
          for(const auto& x : m_factors_power) {
            int factor = x.first;
            int power = x.second;
            int max_power = primes::legendre(n, factor);
            if(max_power < power) {
              is_m_divides_n = false;
              goto finished;
            }
          }
          finished: printf("%d %s %d!\n", m, is_m_divides_n || m == 0 ? "divides" : "does not divide", n);
        }
    }
}