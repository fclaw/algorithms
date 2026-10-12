/*
───────────────────────────────────────────────────────────────
🧳 UVa 11472 Beautiful Numbers, https://onlinejudge.org/external/114/11472.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>






ll cache[10][1 << 10][101];



ll dp(int digit, int digits_used, int curr_length, int max_length, int base) {

  if(curr_length >= max_length) {
    return 0LL;
  }

  if(~cache[digit][digits_used][curr_length]) {
    return cache[digit][digits_used][curr_length];
  }

  ll ways = 0;
  int left_d = digit - 1;
  int left_d_bit = 1 << left_d;
  if(left_d >= 0) {
    int new_digital_used = digits_used | left_d_bit;
    bool all_digits_used = __builtin_popcount(new_digital_used) == base;
    ways += (all_digits_used ? 1 : 0) + dp(left_d, new_digital_used, curr_length + 1, max_length, base);
  }

  int right_d = digit + 1;
  int right_d_bit = 1 << right_d;
  if(right_d < base) {
    int new_digital_used = digits_used | right_d_bit;
    bool all_digits_used = __builtin_popcount(new_digital_used) == base;
    ways += (all_digits_used ? 1 : 0) + dp(right_d, new_digital_used, curr_length + 1, max_length, base);
  }

  return (cache[digit][digits_used][curr_length] = (ways % MOD));
}


ll count_beautiful_numbers(int base, int length) {
  ll ways = 0;
  std::memset(cache, -1, sizeof cache);
  for(int d = 1; d < base; ++d) {
    ways += dp(d, 0 | (1 << d), 1, length, base);
  }
  return ways % MOD;
}


namespace algorithms::onlinejudge::advanced_topics::beautiful_numbers
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

        int t_cases;
        stdin_read(t_cases);
        while(t_cases--) {
          int base, length;
          stdin_read(base, length);
          std::cout << count_beautiful_numbers(base, length) << "\n";
        }
    }
}