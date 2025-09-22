/*
───────────────────────────────────────────────────────────────
🧳 UVa 10212 The Last Non-zero Digit, multiply numbers from N down
   to N-M+1; use /10 to discard the trailing zero(es); use %1 Billion, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
constexpr ll MOD = 10000000000;

// a simple function to remove all trailing zeros from a number.
// For example, 12300 -> 123.
ll strip_trailing_zeros(ll num) {
  // Edge case: if the number itself is 0, we should just return 0.
  // Otherwise, '0 % 10 == 0' would lead to an infinite loop.
  if(num == 0) return 0;
    
  // as long as the number is divisible by 10...
  // ...divide it by 10.
  while(num % 10 == 0) num /= 10;
  return num;
}

namespace algorithms::onlinejudge::maths::last_non_zero_digit
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

       ll n, m;
       while(scanf("%lld %lld", &n, &m) == 2) {
        ll last_digit = 1;
        for(ll k = n; k > n - m; --k)
          last_digit = strip_trailing_zeros(last_digit * k) % MOD;
        printf("%lld\n", last_digit % 10);
       }
    }
}