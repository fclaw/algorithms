/*
───────────────────────────────────────────────────────────────
🧳 UVa 11391 Blobs in the Board, https://onlinejudge.org/external/113/11391.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * PROBLEM & BOARD REPRESENTATION:
 * ============================================================================
 * The board dimensions are R x C with R, C <= 4.
 * Total cells = R * C <= 16.
 *
 * Because total cells <= 16, the ENTIRE board state fits into a single 16-bit integer!
 * 
 * 1. 2D Coordinate <-> 1D Bit Index Mapping:
 *    idx = r * COLS + c
 *    r   = idx / COLS
 *    c   = idx % COLS
 *
 * 2. Bit Semantics:
 *    - Bit 'idx' is 1: Cell (r, c) is OCCUPIED by a blob.
 *    - Bit 'idx' is 0: Cell (r, c) is EMPTY.
 *
 * ============================================================================
 * PEG SOLITAIRE JUMP RULE (8 DIRECTIONS):
 * ============================================================================
 * A blob at Origin (r, c) can jump over a neighboring blob at Mid (mid_r, mid_c)
 * and land on an Empty cell Destination (jump_r, jump_c):
 *
 *      (Origin: Blob) ---> [Mid: Blob (Eaten!)] ---> (Destination: Empty)
 *          (r, c)              (r+dr, c+dc)             (r+2dr, c+2dc)
 *          bit = 1              mid_bit = 1               jump_bit = 0
 *
 * After the jump:
 *   1. Origin becomes EMPTY       (clear bit)
 *   2. Mid is EATEN/REMOVED       (clear mid_bit)
 *   3. Destination becomes OCCUPIED (set jump_bit)
 *
 * Every jump strictly reduces the total number of blobs on the board by 1.
 * This guarantees that the state space is a strictly decreasing DAG (no cycles)!
 * ============================================================================
 *
 * ============================================================================
 * ARCHITECTURAL INSIGHT: CROSS-TESTCASE (PERSISTENT) MEMOIZATION
 * ============================================================================
 * ----------------------------------------------------------------------------
 * 1. THE REPEATED SUBPROBLEM TRAP:
 * ----------------------------------------------------------------------------
 * In many multi-testcase problems, naive implementations wipe the cache 
 * clean on every single testcase:
 *
 *     while (T--) {
 *         memset(cache, -1, sizeof(cache)); // WIPING AWAY FREE WORK!
 *         solve();
 *     }
 *
 * Why this is catastrophic:
 * - A grid of size R x C with a given bitmask of blobs has the EXACT SAME 
 *   number of solutions in Testcase 1, Testcase 5, and Testcase 100!
 * - Discarding the cache throws away millions of solved subproblems, forcing
 *   the CPU to repeatedly re-traverse identical recursion trees.
 * - Additionally, calling memset on a multi-megabyte table dozens of times 
 *   burns raw clock cycles and evicts useful L1/L2 cache lines.
 *
 * ----------------------------------------------------------------------------
 * 2. THE PERSISTENT LIFECYCLE SOLUTION:
 * ----------------------------------------------------------------------------
 * By sizing the table to include the board dimensions:
 *
 *     int memo[5][5][1 << 16]; // ~6.5 MB of static BSS memory
 *
 * We initialize the table ONCE at the very start of main():
 *
 *     int main() {
 *         memset(memo, -1, sizeof(memo)); // INITIALIZED EXACTLY ONCE!
 *
 *         while (T--) {
 *             // Testcase 1 fills parts of the cache.
 *             // Testcases 2, 3, 4... get instant O(1) cache hits!
 *             solve();
 *         }
 *     }
 *
 * ----------------------------------------------------------------------------
 * 3. COMPLEXITY COLLAPSE (AMORTIZED ANALYSIS):
 * ----------------------------------------------------------------------------
 * Across the entire execution of the program:
 * - The total number of unique states in the universe is bounded by:
 *       4 x 4 x 2^16 = 1,048,576 states.
 * - Because the cache is never cleared, EVERY SUBPROBLEM IS SOLVED AT MOST 
 *   ONCE IN THE ENTIRE PROGRAM RUN.
 * - Later testcases skip recursion entirely, turning queries into pure O(1)
 *   table lookups.
 *
 * ----------------------------------------------------------------------------
 * 4. THE GOLDEN CHECKLIST: WHEN IS GLOBAL MEMOIZATION SAFE?
 * ----------------------------------------------------------------------------
 * You can safely keep the cache global across testcases IF AND ONLY IF:
 *   [x] The DP function is PURE: f(state) depends strictly on its state inputs.
 *   [x] Transitions do NOT depend on testcase-specific external data
 *       (e.g., no testcase-specific edge weights, costs, or dynamically 
 *       changing rules).
 *   [x] The state tuple completely and uniquely determines the subproblem.
 * ============================================================================
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


#define LSOne(S) ((S) & (-S))


bool in_board(const ii& pos, int R, int C) {
  return pos.first >= 0 && pos.first < R && pos.second >= 0 && pos.second < C;
}

ll cache[5][5][1 << 16];


ll dp(int mask, int ROWS, int COLS) {

  // ------------------------------------------------------------------------
  // 1. BASE CASE: Exactly 1 blob remains on the board
  // ------------------------------------------------------------------------
  // A successful sequence of moves must reduce the board down to a single blob.
  // If popcount == 1, we have successfully found 1 valid sequence path!
  if(__builtin_popcount(mask) == 1) {
    return 1LL;
  }

  if(~cache[ROWS][COLS][mask]) {
    return cache[ROWS][COLS][mask];
  }

  ll ways = 0LL;
  int blobs = mask;

  // ------------------------------------------------------------------------
  // 2. ITERATE OVER ALL ACTIVE BLOBS ON THE BOARD
  // ------------------------------------------------------------------------
  // Using __builtin_ctz and LSOne to loop only over set bits (active blobs)
  // rather than iterating through all 16 cells blindly.  
  while(blobs) {
    int idx = __builtin_ctz(blobs); // 0-based index of lowest set bit
    int r   = idx / COLS;           // Convert 1D index back to row
    int c   = idx % COLS;           // Convert 1D index back to col
    int bit = LSOne(blobs);         // Extract the single lowest bit (1 << idx)
    for(const ii& v : DIRS8) {
      int jump_r = r + 2 * v.first;
      int jump_c = c + 2 * v.second;
      int mid_r = r + v.first;
      int mid_c = c + v.second;
      int jump_idx = jump_r * COLS + jump_c;
      int mid_idx = mid_r * COLS + mid_c;
      int jump_bit = 1 << jump_idx;
      int mid_bit = 1 << mid_idx;
      if(in_board({jump_r, jump_c}, ROWS, COLS) && 
         in_board({mid_r, mid_c}, ROWS, COLS) &&
         !(mask & jump_bit) && 
         (mask & mid_bit)) {
        // BITWISE BOARD TRANSFORMATION:
        // 1. (mask & ~bit)     : Remove moving blob from origin
        // 2. (... & ~mid_bit)  : Remove eaten blob from mid
        // 3. (... | jump_bit)  : Place blob onto destination
        int new_mask = ((mask & ~bit) & ~mid_bit) | jump_bit;
        ways += dp(new_mask, ROWS, COLS);
      }
    }
    blobs -= bit;
  }

  return (cache[ROWS][COLS][mask] = ways);

}


ll count_ways(int ROWS, int COLS, int mask) {
  return dp(mask, ROWS, COLS);
}


namespace algorithms::onlinejudge::advanced_topics::blobs_in_the_board
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

        std::memset(cache, -1, sizeof cache);
        int t_cases, t_case = 1;
        stdin_read(t_cases);
        while(t_cases--) {
          int ROWS, COLS, blobs_n;
          stdin_read(ROWS, COLS, blobs_n);
          int mask = 0;
          for(int i = 0; i < blobs_n; ++i) {
            int r, c;
            stdin_read(r, c);
            --r; --c;
            int idx = r * COLS + c;
            int bit = 1 << idx;
            mask |= bit; 
          }
          printf("Case %d: %lld\n", t_case++, count_ways(ROWS, COLS, mask));
        }
    }
}