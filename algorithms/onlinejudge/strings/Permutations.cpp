/*
───────────────────────────────────────────────────────────────
🧳 UVa 941 Permutations, https://onlinejudge.org/external/9/941.pdf, rt: s
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
const vd fact = precompute_factorials(45);

// Helper to calculate distinct permutations of the remaining elements
ll calculate_rank(int prev_length, const std::unordered_map<char, int>& freq, int pos) {
  
  if(prev_length <= 0 || pos == 0) return 0;

  double numerator = pos * fact[prev_length];
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

int get_pos(int i, const std::string& origin, int used) {
    int count = 0;
    int S = (int)origin.size();

    for (int j = 0; j < S; ++j) {
        if (i == j) continue;
        
        int bit = 1 << j;
        // If the character at index j has not been used yet,
        // and is strictly smaller than the character at index i
        if (!(used & bit) && origin[j] < origin[i]) {
            count++;
        }
    }
    return count;
}

/**
 * Solves UVa 941 (Permutations) using a Heuristically Pruned Backtracking Approach.
 *
 * Core Concept & Pruning Strategy:
 *
 * 1. The Descending-Order Heuristic (Largest-First Search):
 *    Standard lexicographical generation starts with the smallest character (ascending).
 *    In this implementation, we deliberately sort the 'origin' string in DESCENDING order:
 *       std::sort(origin.begin(), origin.end(), std::greater<char>());
 *
 *    Why this optimizes pruning:
 *    At each position, the algorithm subtracts the number of valid permutations 
 *    represented by all available characters strictly smaller than the chosen character.
 *    By processing characters from largest to smallest:
 *      - We maximize the value subtracted from 'curr_rank' early in the loop.
 *      - If 'curr_rank' drops below 0, it means we have bypassed our target rank.
 *      - Since we are traversing in descending order, any subsequent smaller characters 
 *        in the loop would subtract even more, making 'curr_rank' even more negative.
 *      - Therefore, as soon as 'curr_rank < 0' is triggered, we can prune the entire 
 *        branch immediately.
 *
 * 2. Bitmask State Representation:
 *    The 32-bit integer 'used' acts as a bitmask where the i-th bit is set if 
 *    origin[i] has already been placed. This allows O(1) checks for character availability.
 *
 * 3. Dynamic Multinomial Coefficient Calculation:
 *    We dynamically use the 'freq' map of remaining characters to compute the exact 
 *    number of distinct permutations for the remaining pool at each step, preventing 
 *    double-counting of duplicate characters.
 *
 * State Parameters:
 *   @param origin      The sorted (descending) original string of characters.
 *   @param used        Bitmask representing the set of already placed characters.
 *   @param curr_rank   The remaining rank we need to decrement down to 0.
 *   @param perm        The running string being constructed.
 *   @param sol         Ref-parameter to store the successfully restored permutation.
 *   @param freq        Map tracking the frequencies of remaining unused characters.
 *   @return            True if the target permutation was found along this branch.
 */
bool backtrack(const std::string& origin, int used, ll curr_rank, std::string& perm, std::string& sol, std::unordered_map<char, int>& freq) {
  
  // Pruning: If the remaining rank drops below 0, we have subtracted too much.
  // Because we iterate in descending order, all subsequent iterations will also 
  // be invalid, so we can immediately return false and cut off this branch.
  if(curr_rank < 0) {
    return false;
  }

  int S = (int)origin.size();
  int V = __builtin_popcount(used);
  // Base Case: All characters have been placed
  if(V == S) {
    if(curr_rank == 0) {
      sol = perm;
    }
    return curr_rank == 0;
  }

  for(int i = 0; i < S; ++i) {
    int bit = 1 << i;
    if(!(used & bit)) {
      ll next_rank = curr_rank;
      // Calculate how many unused characters are strictly smaller than origin[i]
      int pos = get_pos(i, origin, used);
      // Subtract the number of distinct permutations we bypass by choosing origin[i]
      next_rank -= calculate_rank(origin.size() - V - 1, freq, pos);
      freq[origin[i]]--;
      perm.push_back(origin[i]);
      if(backtrack(origin, used | bit, next_rank, perm, sol, freq)) {
        return true;
      }
      freq[origin[i]]++;
      perm.pop_back();
    }
  }

  return false;
}


std::string build_permutations(ll rank, const std::string& perm) {

  auto origin = perm;
  std::sort(origin.begin(), origin.end(), std::greater<char>());
  std::unordered_map<char, int> freq;
  for(char c : origin) {
    freq[c]++;
  }
  
  std::string sought_perm;
  std::string local_perm;
  bool _ = backtrack(origin, 0, rank, local_perm, sought_perm, freq);
  return sought_perm;
}


namespace algorithms::onlinejudge::strings::permutations
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
        while(t_cases--) {
          ll rank;
          std::string perm;
          std::cin >> perm >> rank;
          printf("%s\n", build_permutations(rank, perm).c_str());
        }
    }
}