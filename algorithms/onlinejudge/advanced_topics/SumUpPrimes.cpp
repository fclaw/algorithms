/*
───────────────────────────────────────────────────────────────
🧳 UVa 10419 Sum-up the Primes, https://onlinejudge.org/external/104/10419.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


// A fixed-size array of 62 integers
std::array<int, 62> primes = {
  // Primes starting with '1' (25 primes)
  101, 103, 107, 109, 11, 113, 127, 13, 131, 137, 139, 149, 151, 157, 
  163, 167, 17, 173, 179, 181, 19, 191, 193, 197, 199,

  // Primes starting with '2' (19 primes)
  2, 211, 223, 227, 229, 23, 233, 239, 241, 251, 257, 263, 269, 271, 
  277, 281, 283, 29, 293,

  // Primes starting with '3' through '9' (18 primes)
  3, 31, 37, 41, 43, 47, 5, 53, 59, 61, 67, 7, 71, 73, 79, 83, 89, 97
};

int cache[62][14][3][1001];

bool dp(int i, int primes_used, int used_counter, int curr_val, int target, vi& sol, vi& tmp, int primes_n) {

  if(primes_used == primes_n) {
    if(curr_val == target) {
      sol = tmp;
    }
    return curr_val == target;
  }

  if(i >= 62 || primes_used >= primes_n) {
    return false;
  }

  if(~cache[i][primes_used][used_counter][curr_val]) {
    return cache[i][primes_used][used_counter][curr_val];
  }


  if(primes[i] == 2) {
    int next_val = curr_val + primes[i];
    if(next_val <= target) {
      tmp.push_back(2);
      if(dp(i + 1, primes_used + 1, used_counter, next_val, target, sol, tmp, primes_n)) {
        return (cache[i][primes_used][used_counter][curr_val] = true);
      }
      tmp.pop_back();
    }
  } else {
    if(used_counter < 2) {
      int next_val = curr_val + primes[i];
      if(next_val <= target) {
        tmp.push_back(primes[i]);
        if(dp(i, primes_used + 1, used_counter + 1, next_val, target, sol, tmp, primes_n)) {
          return (cache[i][primes_used][used_counter][curr_val] = true);
        }
        tmp.pop_back();
      }
    }
  }

  if(dp(i + 1, primes_used, 0, curr_val, target, sol, tmp, primes_n)) {
    return (cache[i][primes_used][used_counter][curr_val] = true);
  }

  return (cache[i][primes_used][used_counter][curr_val] = false);

}

std::pair<bool, vi> can_target_sum_up(int target, int primes_n) {
  vi sol, tmp;
  std::memset(cache, -1, sizeof cache);
  bool ans = dp(0, 0, 0, 0, target, sol, tmp, primes_n);
  return {ans, sol};
}


namespace algorithms::onlinejudge::advanced_topics::sum_up_primes
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

        int target, primes_n, t_case = 1;
        while(stdin_read(target, primes_n) &&
              (target && primes_n)) {
          std::pair<bool, vi> ans = can_target_sum_up(target, primes_n);
          if(!ans.first) {
            printf("CASE %d:\nNo Solution.\n", t_case++);
          } else {
            std::string sol;
            for(int p : ans.second) {
              sol += std::to_string(p) + "+";
            }
            sol.pop_back();
            printf("CASE %d:\n%s\n", t_case++, sol.c_str());
          }
        }
    }
}