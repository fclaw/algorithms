/*
───────────────────────────────────────────────────────────────
🧳 UVa 11347 Multifactorials, https://onlinejudge.org/external/113/11347.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

auto mk_factors = primes::primeFactors_power;
auto power = arithmetics::power<>;

namespace algorithms::onlinejudge::maths::multifactorials
{
    void submit(std::optional<char*> file, bool debug_mode)
    {

        primes::sieve(1000); 

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

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n, k;
          std::string s;
          while_read(s);
          size_t pos = s.find('!');
          auto s_n = s.substr(0, pos);
          n = std::atoi(s_n.c_str());
          k = s.size() - pos;
          
          std::set<int> terms = {!(n % k) ? k : n % k};
          for(int i = 0; i < n; ++i) {
            if(i * k >= n) break;
            terms.insert(n - i * k);
          }


          std::unordered_map<int, int> factors;
          for(int term : terms) {
            for(auto fac : mk_factors(term))
              factors[fac.first] += fac.second;
          }

          ll divs = 1;
          ll limit = power(10, 18);
          bool is_infinity = false;
          for(auto& fac : factors) {
            if(divs * (fac.second + 1) > limit) {
              is_infinity = true;
              goto finished;
            }
            divs *= (fac.second + 1);
          }

          finished: printf("Case %d: %s\n", t_case++, !is_infinity ? std::to_string(divs).c_str() : "Infinity");
        }
    }
}