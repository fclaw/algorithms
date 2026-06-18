/*
───────────────────────────────────────────────────────────────
🧳 UVa 11084 Anagram Division, https://onlinejudge.org/external/110/11084.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * DP STATE REDUCTION: THE SUFFICIENCY OF (COUNTER, CURR_MOD)
 * ============================================================================
 * In most "Permutation with Duplicates" problems, programmers use a 3D state:
 *      dp[pos][mask][curr_mod]
 * where 'mask' tracks used indices, and 'pos' tracks the current length.
 * 
 * However, we have successfully reduced the state space to just two parameters:
 *      dp[compacted_counter][curr_mod]
 * 
 * Why these two parameters are mathematically and logically SUFFICIENT:
 * ----------------------------------------------------------------------------
 * 1. THE REDUNDANCY OF 'POS' (Current Position):
 *    The current position (how many digits we have placed so far) is a direct 
 *    mathematical function of the remaining counts.
 *         pos = Total_Length - Sum(counter[0...9])
 *    Because the remaining counts uniquely dictate how many steps we have taken, 
 *    adding 'pos' to the state is mathematically redundant.
 * 
 * 2. THE REDUNDANCY OF 'MASK' (Digit Exhaustion):
 *    A bitmask of exhausted digits is completely subsumed by the 'counter'. 
 *    If counter[digit] == 0, that digit is exhausted. The 'counter' holds the 
 *    complete, precise multiset of remaining digits, making 'mask' redundant.
 * 
 * THE "NATIVE UNIQUE" ADVANTAGE (Why this is superior):
 * -----------------------------------------------------
 * In the index-mask approach, we treat every character as distinct and must 
 * divide by (frequency!) at the end to remove duplicates.
 * 
 * In this (counter, curr_mod) approach, we transition by looping digit 'd' 
 * from 0 to 9. We only branch if `counter[d] > 0`.
 * 
 * Because we loop over UNIQUE DIGITS (0-9) rather than UNIQUE INDICES (0-N),
 * the recursion tree NATIVELY only generates unique permutations (anagrams). 
 * We never explore duplicate paths, resulting in a much smaller search tree 
 * and eliminating the need for factorial division at the end!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;
using ull = unsigned long long;
using vi = std::vector<int>;


ll compactVector(const std::vector<int>& counter) {
  ll hash_val = 0;
    
  for (int val : counter) {
    // Shift left by 4 bits to make room, then insert the value (0-10)
    hash_val = (hash_val << 4) | val;
  }

  return hash_val;
}

using map = std::unordered_map<int, std::unordered_map<ll, ull>>;

bool check_entry_in_memo(const map& memo, int curr_mod, ll hash_val) {
  if(memo.find(curr_mod) == memo.end()) {
    return false;
  }
  if(memo.at(curr_mod).find(hash_val) == memo.at(curr_mod).end()) {
    return false;
  } 

  return true;
}


ull get_valid_permutations(const std::string& number, int pos, int curr_mod, int d, vi& counter, map& memo) {

  if(pos == (int)number.size()) {
    if(curr_mod == 0) {
      return 1;
    } else {
      return 0;
    }
  }

  ll hash_val = compactVector(counter);
  if(check_entry_in_memo(memo, curr_mod, hash_val)) {
    return memo[curr_mod][hash_val];
  }

  ull count = 0;
  for(int digit = 0; digit < 10; digit++) {
    if(counter[digit] == 0) {
      continue;
    }
    counter[digit]--;
    count += get_valid_permutations(number, pos + 1, (curr_mod * 10 + digit) % d, d, counter, memo);
    counter[digit]++;
  }
  return memo[curr_mod][hash_val] = count;
}


namespace algorithms::onlinejudge::strings::anagram_division
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
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          int d;
          std::string number;
          std::cin >> number >> d;
          vi counter(10, 0);
          for(char c : number) {
            counter[c - '0']++;
          }
          map memo;
          std::cout << get_valid_permutations(number, 0, 0, d, counter, memo) << std::endl;
        }
    }
}