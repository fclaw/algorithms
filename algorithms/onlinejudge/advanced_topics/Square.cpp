/*
───────────────────────────────────────────────────────────────
🧳 UVa 10364 Square, https://onlinejudge.org/external/103/10364.pdf, rt: s
───────────────────────────────────────────────────────────────
 * Verdict: Accepted (0.170s)
 * Technique: Bitmask Dynamic Programming / Memoized Backtracking
 *
 * ============================================================================
 * PROBLEM FORMULATION:
 * ============================================================================
 * Given up to 20 sticks, determine if they can be partitioned into 4 subsets 
 * such that each subset sums to exactly 'side' = (sum of all sticks) / 4.
 *
 * ============================================================================
 * DP STATE & DIMENSION REDUCTION:
 * ============================================================================
 * 1. 'sticks_mask' (up to 20 bits):
 *    Tracks which sticks have been used so far.
 *
 * 2. 'sides_mask' (takes values 0 to 3):
 *    Tracks the remaining sides that need to be constructed.
 *    (Once 3 sides are successfully completed, the 4th side is guaranteed
 *    to be valid because the total sum of all sticks is 4 * side).
 *
 * 3. Why 'curr_side_length' is NOT in the cache:
 *    The sum of currently used sticks is uniquely determined by 'sticks_mask'.
 *    Therefore, curr_side_length = (sum of used sticks) % side.
 *    Because it is deterministic, it doesn't need an extra cache dimension!
 *
 * Memory footprint: (1 << 20) * 4 * sizeof(int) ≈ 4 MB (Very cache-friendly!).
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



#define LSOne(S) ((S) & (-S))


int cache[1 << 20][4];


bool can_square_formed(int sticks_mask, int sides_mask, int curr_side_length, int side, const vi& sticks) {
  
  int S = (int)sticks.size();
  // ------------------------------------------------------------------------
  // 1. BASE CASE: Success!
  // ------------------------------------------------------------------------
  // All sticks have been used AND all required sides have been completed.
  if(__builtin_popcount(sticks_mask) == S && 
     sides_mask == 0) {
    return true;
  }

  // ------------------------------------------------------------------------
  // 2. MEMOIZATION CHECK
  // ------------------------------------------------------------------------
  // Bitwise NOT trick: ~(-1) == 0 (unvisited). Any stored value (0 or 1) hits!
  if(~cache[sticks_mask][sides_mask]) {
    return cache[sticks_mask][sides_mask];
  }

  // ------------------------------------------------------------------------
  // 3. TRY EXPANDING WITH EVERY UNUSED STICK
  // ------------------------------------------------------------------------
  for(int s = 0; s < S; ++s) {
    int s_bit = 1 << s;
    if(!(sticks_mask & s_bit)) {
       int new_side_length = curr_side_length + sticks[s];
       // Case A: Stick partially fills the current side
       if(new_side_length < side) {
         if(can_square_formed(sticks_mask | s_bit, sides_mask, new_side_length, side, sticks)) {
           return (cache[sticks_mask][sides_mask] = true);
         }
       // Case B: Stick PERFECTLY completes the current side!
       } else if (new_side_length == side) {
         int bit = LSOne(sides_mask); // the first bit that is on
         // Reset curr_side_length to 0 to begin building the next side
         if(can_square_formed(sticks_mask | s_bit, sides_mask & ~bit, 0, side, sticks)) {
           return (cache[sticks_mask][sides_mask] = true);
         }
       }
       // Case C: new_side_length > side is implicitly pruned (stick is too long to fit)
    }
  } 

  // If no unused stick leads to a valid square from this state
  return (cache[sticks_mask][sides_mask] = false);
}

namespace algorithms::onlinejudge::advanced_topics::square
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
          int sticks_n;
          stdin_read(sticks_n);
          vi sticks(sticks_n);
          int total_length = 0;
          for(int s = 0; s < sticks_n; ++s) {
            stdin_read(sticks[s]);
            total_length += sticks[s];
          }
          if((total_length % 4)) {
            std::cout << "no" << "\n";
          } else {
            int side = total_length / 4;
            std::memset(cache, -1, sizeof cache);
            bool ans = can_square_formed(0, (1 << 4) - 1, 0, side, sticks);
            std::cout << (ans ? "yes" : "no") << "\n";
          }
        }
    }
}