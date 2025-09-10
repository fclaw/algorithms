/*
───────────────────────────────────────────────────────────────
🧳 UVa 11752, The Super Powers,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

constexpr ll MAX = 100;
constexpr ll MAX_BASE = 65535;

using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::super_powers
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

        std::set<ull> super_power_nums = {1};
        for(ll base = 2; base <= MAX_BASE; ++base) {
          auto log_max = std::log2l(static_cast<long double>(UINT64_MAX));
          auto log_base = std::log2l(static_cast<long double>(base));
          int exp_up = std::floor(log_max / log_base);
          for(ll exp = 2; exp <= exp_up; ++exp) {
            // check whether the power is composite
            if(!primes::isPrime(exp)) {
              ull num = arithmetics::power<ull>(base, exp);
              if(num > 0) super_power_nums.insert(num);
            }
          }                   
        }
        for(ull n : super_power_nums) printf("%llu\n", n);
    }
}