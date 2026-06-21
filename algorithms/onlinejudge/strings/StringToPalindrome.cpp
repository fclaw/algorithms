/*
───────────────────────────────────────────────────────────────
🧳 UVa 10739 String to Palindrome, https://onlinejudge.org/external/107/10739.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM OVERVIEW: THE PALINDROME-REVERSE THEOREM (Edit Distance)
 * ============================================================================
 * THE PROBLEM: 
 * Find the minimum number of operations (Insert, Delete, Replace) required 
 * to transform a given string S into a valid palindrome.
 * 
 * THE STANDARD APPROACH: 
 * Usually, this requires an Interval DP (O(N^2) state: dp[i][j]), building 
 * the palindrome from the outside inward.
 * 
 * THE SHORTCUT (2-String Edit Distance):
 * We can completely bypass Interval DP and reuse a standard 2-String Edit 
 * Distance engine by comparing the string S against its own reverse (S^R).
 * 
 * THE MATHEMATICAL PROOF:
 * Let K be the minimum number of edit operations to turn S into a perfect 
 * palindrome P.
 * 
 * 1. By definition, a palindrome reads the same forwards and backwards: P = P^R.
 * 2. If it takes K steps to transform S -> P.
 * 3. It logically takes the exact same K steps to transform P^R -> S^R.
 * 
 * Therefore, the shortest transformation path from S to S^R naturally uses 
 * the optimal palindrome P as an intermediate "pitstop":
 * 
 *          (K steps)             (K steps)
 *      S -------------> [ P ] -------------> S^R
 * 
 * Because the total Edit Distance from S to S^R is exactly 2K, we simply 
 * run our standard Edit Distance algorithm and divide the result by 2!
 * 
 * ARCHITECTURAL BENEFIT:
 * This mathematically sound "hack" allows us to reuse existing Levenshtein 
 * Distance infrastructure without writing custom interval logic.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


struct State
{
    int steps;
    bool operator < (const State& other) const {
      return steps < other.steps;
    }
};



using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


State get_min_steps(const std::string& from, const std::string& to, int i, int j, vv_state& cache) {

  if (i == (int)from.size() && 
      j == (int)to.size()) {
    return {0};
  }

  // first string ends 
  // .... _ _ _
  // .... A B C
  // insert operation
  if (i == (int)from.size() && 
      j < (int)to.size()) {
    return {(int)to.size() - j};
  }

  // delete operation
  // .... A B C
  // .... _ _ _
  if (i < (int)from.size() && 
      j == (int)to.size()) {
    return {(int)from.size() - i};
  }

  if (cache[i][j].steps != -1) {
    return cache[i][j];
  }

  State eq_state = {INT_MAX};

  if(from[i] == to[j]) {
    eq_state = get_min_steps(from, to, i + 1, j + 1, cache);
  }

  State prev_insert = get_min_steps(from, to, i, j + 1, cache);
  prev_insert.steps++;

  State prev_delete = get_min_steps(from, to, i + 1, j, cache);
  prev_delete.steps++;

  State prev_replace = get_min_steps(from, to, i + 1, j + 1, cache);
  prev_replace.steps++;

  return cache[i][j] = std::min(eq_state, std::min(prev_replace, std::min(prev_insert, prev_delete)));
}



namespace algorithms::onlinejudge::strings::string_to_palindrome
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

         
        int t_cases, t_case = 1;
        std::cin >> t_cases;
        std::cin.ignore();
        std::string str;
        while(t_cases--) {
          std::cin >> str;
          std::string reverse_str(str.begin(), str.end());
          std::reverse(reverse_str.begin(), reverse_str.end());
          vv_state cache(str.size() + 1, v_state(str.size() + 1, State{-1})); 
          State state = get_min_steps(str, reverse_str, 0, 0, cache);
          printf("Case %d: %d\n", t_case++, state.steps / 2);
        }
    }
}