/*
───────────────────────────────────────────────────────────────
🧳 UVa 13194 DPA Numbers II, https://onlinejudge.org/external/131/13194.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>


namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using ll = long long;
using ull = unsigned long long;
auto __power = arithmetics::power<ull>;

std::string test(ull num, ull sum_of_divs) { 
  if(num > sum_of_divs) return "deficient";
  sum_of_divs -= num;
  if(num == sum_of_divs) return "perfect";
  else if(num < sum_of_divs) return "abundant";
  else return "deficient";
}


namespace algorithms::onlinejudge::maths::dpa_numbers_2
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
       
        primes::sieve();
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          ull num;
          ull sum_of_divisors = 1;
          scanf("%llu", &num);
          map_ll_i factors = primes::primeFactors_power(num);
          // https://en.wikipedia.org/wiki/Divisor_function (sigma function)
          for(auto& fac : factors) {
             sum_of_divisors *= ((__power(fac.first, fac.second + 1) - 1) / (fac.first - 1));
          }
          printf("%s\n", test(num, sum_of_divisors).c_str());
        }
    }
}