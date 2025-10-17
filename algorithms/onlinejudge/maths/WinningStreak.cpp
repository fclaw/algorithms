/*
───────────────────────────────────────────────────────────────
🧳  UVa 11176 Winning Streak, https://onlinejudge.org/external/111/p11176.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ld = long double;
using vd = std::vector<ld>;
using vvd = std::vector<vd>;


ld p_global; // Win probability

/**
 * Calculates the expected value of the longest winning streak using a Direct Expectation DP.
 * This function explores a conceptual "decision tree" from the current state
 */
ld solve(int n_left, int max_streak, vvd& memo) {
  // --- Base Case ---
  // This is a LEAF of the decision tree. The path is complete.
  // The final value for this path is the 'max_streak' accumulated along the way.
  if(n_left == 0) {
    return static_cast<ld>(max_streak);
   }
    
  // --- Memoization (Pruning the Tree) ---
  // If we've already explored the entire subtree from this exact state,
  // we return the cached result immediately, pruning this branch.
  if(~(int)memo[n_left][max_streak]) {
    return memo[n_left][max_streak];
  }

  ld expected_value = 0;

  // --- The Recurrence: Summing the contributions from each branch of the decision tree ---

  // BRANCH 1: The "Lose Branch" (the rightmost) 
  // Explore the subtree where the very next game is a Loss.
  // The probability of taking this branch is (1-p).
  expected_value += (1.0 - p_global) * solve(n_left - 1, max_streak, memo);

  // BRANCH 2: The "Win-Then-Lose" Branches (everything in the middle)
  // This loop explores a series of subtrees. Each 'i' represents a branch
  // where we win the next 'i' games and then lose the (i+1)-th game.
  ld p_pow = 1.0; // Will hold p^i
  for (int i = 1; i < n_left; ++i) {
    p_pow *= p_global; // Update to p^i
    // The probability of this specific branch prefix (W...WL) is p^i * (1-p).
    // The new max_streak for the subsequent subproblem is updated with the streak 'i' we just achieved.
    expected_value += p_pow * (1.0 - p_global) * solve(n_left - i - 1, std::max(max_streak, i), memo);
  }

  // BRANCH 3: The "All-Win Branch" (the leftmost)
  // This is not a recursive call but a direct calculation for a specific LEAF path.
  // It represents the single path where we win all remaining 'n_left' games.
  p_pow *= p_global; // Update p_pow to be p^n_left
  // The probability of this branch is p^n_left.
  // The final value for this path is max(max_streak, n_left), as it's a completed path.
  expected_value += p_pow * std::max(max_streak, n_left);
    
  // --- Store and Return ---
  // Cache the total expected value for this entire subtree before returning.
  return memo[n_left][max_streak] = expected_value;
}


namespace algorithms::onlinejudge::maths::winning_streak
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

        int games;
        double prob;
        while(scanf("%d %lf", &games, &prob) == 2 && games) {
          p_global = prob;
          // We use a 2D vector for our memoization table to cache the results of our explorations.
          // A vector provides the fastest possible O(1) lookup, which is critical because
          // we will revisit the same crossroads in our decision tree millions of times. A map's
          // O(log N) lookup would be too slow.
          //
          // Our map marker to indicate "this path has not yet been explored" is -1.0. We can safely
          // use this marker because the journey we are mapping is the calculation of an expected
          // streak length. Streak lengths themselves can never be negative. As a result, the
          // final expected value—the average of all possible journey outcomes—is also guaranteed
          // to be a non-negative number. A result of -1.0 is therefore an impossible outcome,
          // making it a perfect, unambiguous flag for an unexplored state.
          vvd memo(games + 1, vd(games + 1, -1.0));
          printf("%0.10Lf\n", solve(games, 0, memo));
        }
    }
}
