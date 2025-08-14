/*
───────────────────────────────────────────────────────────────
🧳 UVa 10624 Super Number, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;
using vi = std::vector<int>;



bool check_divisibility(const vi& digits, int k) {
  ll remainder = 0;
  for(int d : digits)
    remainder = (remainder * 10 + d) % k;  
  return remainder == 0;
}


void backtrack(int i, int left, int right, vi& digits, vi& ans, bool& found) {
  if(i > right) {
    ans = digits;
    found = true;
    return;
  }

  for(int digit = 0; digit <= 9; ++digit) {
    if(digit == 0 && digits.empty()) 
      continue;
    digits.push_back(digit);
    bool is_valid = check_divisibility(digits, i);
    if(i >= left && !is_valid) {
      digits.pop_back();
      continue;
    }
    backtrack(i + 1, left, right, digits, ans, found);
    digits.pop_back();
    if(found) return;
  }
}


std::string digits_to_string(const vi& digits) {
  std::string s;
  for (int digit : digits) {
    s += std::to_string(digit);
  }
  return s;
}


namespace algorithms::onlinejudge::maths::super_number
{
    /** https://onlinejudge.org/external/106/10624.pdf */
    int t_cases, t_case = 1;
    int left, right;
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
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(left, right);
          vi digits;
          vi ans;
          bool found = false;
          backtrack(1, left, right, digits, ans, found);
          printf("Case %d: %s\n", t_case++, (found ? digits_to_string(ans) : std::to_string(-1)).c_str());
        }
    }
}