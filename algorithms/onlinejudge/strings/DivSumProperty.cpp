/*
───────────────────────────────────────────────────────────────
🧳 UVa 11361 Investigating Div-Sum Property, https://onlinejudge.org/external/113/11361.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



int MAX_DIGITS = 10;
int MAX_K = 10000;
int MAX_DIGITS_SUM = 91;

using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vvvvl = std::vector<vvvl>;
using vvvvvl = std::vector<vvvvl>;


ll count_numbers(const std::string& a, const std::string& b, ll k, bool is_tight_low, bool is_tight_high, int pos, int curr_mod, int sum, vvvvvl& memo) {
   
  if(pos == (int)b.size()) {
    if(curr_mod == 0 &&
       sum % k == 0) {
      return 1;
    } else {
      return 0;
    }
  }

  if(~memo[pos][curr_mod][sum][(int)is_tight_high][is_tight_low]) {
    return memo[pos][curr_mod][sum][(int)is_tight_high][is_tight_low];
  }

  ll count = 0;
  // Determine the lower and upper bounds for this specific slot
  int from = is_tight_low  ? (a[pos] - '0') : 0;
  int to   = is_tight_high ? (b[pos] - '0') : 9;
  for(int d = from; d <= to; ++d) {
    int new_mod = (curr_mod * 10 + d) % k;
    int new_sum = sum + d;
    count += count_numbers(a, b, k, is_tight_low && (d == from), is_tight_high && (d == to), pos + 1, new_mod, new_sum, memo);
  }
  return memo[pos][curr_mod][sum][(int)is_tight_high][is_tight_low] = count;
}


namespace algorithms::onlinejudge::strings::div_sum_property
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

      vvvvvl memo(MAX_DIGITS, vvvvl(MAX_K, vvvl(MAX_DIGITS_SUM, vvl(2, vl(2, -1)))));
      int t_cases;
      std::cin >> t_cases;
      std::cin.ignore();
      while(t_cases--) {
        int k;
        std::string a, b;
        std::cin >> a >> b >> k;
        
        while (a.length() < b.length()) {
          a = "0" + a;
        }

        // 1. DYNAMIC CLEARING:
        // Instead of clearing all 10000 elements, we only clear up to the current K.
        // This reduces the clear time from 1.9 seconds to less than 1 millisecond!
        int limit_num_mod = std::min(k, MAX_K);
        for (int i = 0; i < MAX_DIGITS; ++i) {
          for (int j = 0; j <= limit_num_mod; ++j) {
            for (int m = 0; m < MAX_DIGITS_SUM; ++m) {
              for(int l = 0; l < 2; ++l) {
                for(int n = 0; n < 2; ++n) {
                  memo[i][j][m][l][n] = -1;
                }
              }
            }
          }
        }
        std::cout << count_numbers(a, b, k, true, true, 0, 0, 0, memo) << std::endl;
      } 
    }
}