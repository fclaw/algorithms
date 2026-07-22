/*
───────────────────────────────────────────────────────────────
🧳 UVa 153 Permalex, https://onlinejudge.org/external/1/153.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vd = std::vector<double>;
using ll = long long;


// Precompute factorials up to 40 using double to prevent overflow
vd precompute_factorials(int max_n) {
  vd fact(max_n + 1, 1.0);
  for(int i = 1; i <= max_n; ++i) {
    fact[i] = fact[i - 1] * i;
  }
  return fact;
}

// Global factorial table
const vd fact = precompute_factorials(40);

// Helper to calculate distinct permutations of the remaining elements
ll calculate_permutations(int remaining_length, const std::unordered_map<char, int>& freq, int pos) {
   if (remaining_length <= 0 || pos == 0) return 0;

  double numerator = pos * fact[remaining_length];
  double denominator = 1.0;

  for(std::pair<char, int> el : freq) {
    if(el.second > 1) {
      denominator *= fact[el.second];
    }
  }

  // Since the result is guaranteed to fit in a 32-bit signed integer, 
  // the double division is perfectly precise.
  return std::llround(numerator / denominator);
}


int get_pos(int i, const std::string& perm) {
  int count = 0;
  for(int j = i + 1; j < (int)perm.length(); ++j) {
    if(perm[j] < perm[i]) {
      count++;
    }
  }
  return count;
}

int get_permutation_rank(const std::string& perm) {

   int S = (int)perm.size();   
   std::unordered_map<char, int> freq;
   for(char c : perm) {
     freq[c]++;
   }
 
   int rank = 1;
   for(int i = 0; i < S; ++i) {
    int pos = get_pos(i, perm);
    rank += calculate_permutations(S - i - 1, freq, pos);
    freq[perm[i]]--;
   }
   
   return rank;
}


namespace algorithms::onlinejudge::strings::permalex
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
         
        std::string permutation;
        while(std::cin >> permutation && 
              permutation != "#") {
          printf("%10d\n", get_permutation_rank(permutation));
        }
    }
}