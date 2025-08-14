/*
───────────────────────────────────────────────────────────────
🧳 UVa 10624 Super Number, rt: 0.360s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;
using vi = std::vector<int>;


int get_last_remainder(const vi& digits, int k) {
  int remainder = 0;
  for(int d : digits) {
    remainder = (remainder * 10 + d) % k;
  }
  return remainder;
}


void backtrack(int k, int left, int right, vi& digits, vi& ans, bool& found) {
  if(k > right) {
    ans = digits;
    found = true;
    return;
  }

  // --- Performance Bottleneck ---
  // To check the divisibility for the new k-th digit, we first need the remainder
  // of the (k-1)-digit prefix with respect to the new divisor 'k'.
  // This function correctly computes it, but it does so by re-scanning all k-1 digits
  // every time it's called. This leads to a complexity of roughly (num_calls * depth),
  // which is too slow and results in a Time Limit Exceeded verdict.
  // The optimal solution avoids this O(k) rescan by passing calling k - 1 remainders only once at the k-level
  // thus obtaining last remainder. afterwards what is left is to reconcile it with the currently used digit to get the final remainder
  int last_rem = get_last_remainder(digits, k);

  for(int digit = (k == 1 ? 1 : 0); digit <= 9; ++digit) {
    bool is_valid = (last_rem * 10 + digit) % k == 0;
    if(k < left || (k >= left && is_valid)) {
      digits.push_back(digit);
      backtrack(k + 1, left, right, digits, ans, found);
      digits.pop_back();
    }
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
        
        scanf("%d\n", &t_cases);
        while(t_cases--) {
          scanf("%d %d\n", &left, &right);
          vi digits, ans;
          bool found = false;
          backtrack(1, left, right, digits, ans, found);
          printf("Case %d: %s\n", t_case++, (found ? digits_to_string(ans) : std::to_string(-1)).c_str());
        }
    }
}