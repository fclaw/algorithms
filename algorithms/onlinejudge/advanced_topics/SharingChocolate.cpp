/*
───────────────────────────────────────────────────────────────
🧳 UVa 1099 Sharing Chocolate, https://onlinejudge.org/external/10/1099.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



#define LSOne(S) ((S) & (-S))


int cache[101][1 << 15];


/**
 * Problem: UVa 1099 - Sharing Chocolate
 * Technique: Geometric Bitmask Dynamic Programming + Submask Enumeration
 *
 * ============================================================================
 * THE CORE GEOMETRIC INVARIANT:
 * ============================================================================
 * At every step, we are given a rectangular piece of chocolate that must be
 * partitioned among a subset of friends represented by 'mask'.
 *
 * 1. Area Conservation:
 *    The area of this piece MUST equal the sum of shares of everyone in 'mask':
 *        Area = comb_shares_area[mask]
 *
 * 2. Dimension Deduction (State Reduction):
 *    If we know ONE dimension ('length'), the other dimension ('height') is 
 *    100% mathematically fixed:
 *        height = comb_shares_area[mask] / length
 *    We never need to store both dimensions in our DP state!
 *
 * ============================================================================
 * DP STATE & TRANSITION:
 * ============================================================================
 * State: cache[length][mask] -> Can a rectangle with 'length' satisfy 'mask'?
 *
 * To solve (length, mask):
 *   We partition 'mask' into two disjoint non-empty subsets (A, B) such that
 *   A U B = mask and A ∩ B = ∅. We then check if a straight line cut 
 *   (either Horizontal or Vertical) can cleanly separate subset A from subset B.
 * ============================================================================
 */
bool can_shared(int length, const vi& shares, int mask, const vi& comb_shares_area) {

  // Derive the perpendicular dimension in O(1) from area conservation
  int height = comb_shares_area[mask] / length;

  // ------------------------------------------------------------------------
  // 1. BASE CASE: Only 1 person remains in this piece
  // ------------------------------------------------------------------------
  // A single person cannot be cut further. The piece is valid IF AND ONLY IF
  // its area matches that person's exact requested share!  
  if(__builtin_popcount(mask) == 1) {
    int bit = LSOne(mask);
    int i = __builtin_ctz(bit);
    if(shares[i] == height * length) {
      return (cache[length][mask] = true);
    }
    return (cache[length][mask] = false);
  }

  // ------------------------------------------------------------------------
  // 2. MEMOIZATION LOOKUP
  // ------------------------------------------------------------------------
  // Bitwise NOT trick: ~(-1) == 0 (unvisited), any other value is a cache hit!  
  if(~cache[length][mask]) {
    return cache[length][mask];
  }

  // ------------------------------------------------------------------------
  // 3. ENUMERATE ALL 2-PARTITIONS OF THE MASK (O(3^N) Trick)
  // ------------------------------------------------------------------------
  // '(mask - 1) & mask' efficiently jumps only through valid submasks.
  // 'A > (mask ^ A)' breaks symmetry: visits each unordered pair {A, B}
  for (int A = (mask - 1) & mask; A > (mask ^ A); A = (A - 1) & mask) {
    int B = mask ^ A;

    // ====================================================================
    // OPTION 1: HORIZONTAL CUT (Split along Height)
    // ====================================================================
    // The cut runs parallel to 'length'.
    // Both resulting pieces retain the exact same 'length', but their 
    // heights split into 'h' and 'height - h':
    //
    //       +-----------------------+
    //       |   Top Piece (A)       |  height = h, width = length
    //       |-----------------------|  <--- Horizontal Cut Line
    //       |   Bottom Piece (B)    |  height = height - h, width = length
    //       +-----------------------+
    for(int h = 1; h <= height; ++h) {
      int up_area = h * length;
      int down_area = (height - h) * length;
      // Geometric validity: areas must exactly match requested shares!
      if(comb_shares_area[A] == up_area && 
         comb_shares_area[B] == down_area) {
        if(can_shared(length, shares, A, comb_shares_area) &&
           can_shared(length, shares, B, comb_shares_area)) {
          return (cache[length][mask] = true);
        }
      }
    }

    // ====================================================================
    // OPTION 2: VERTICAL CUT (Split along Length)
    // ====================================================================
    // The cut runs parallel to 'height'.
    // Both resulting pieces retain the exact same 'height', but their 
    // lengths split into 'l' and 'length - l':
    //
    //       +-------------+---------+
    //       |             |         |
    //       |  Left (A)   | Right(B)|
    //       |             |         |
    //       +-------------+---------+
    //       |<-    l    ->|<- len-l->|
    //                     ^
    //             Vertical Cut Line
    for(int l = 1; l <= length; ++l) {
      int left_area = height * l;
      int right_area = height * (length - l);
      // Geometric validity: areas must exactly match requested shares!
      if(comb_shares_area[A] == left_area && 
         comb_shares_area[B] == right_area) {
        if(can_shared(l, shares, A, comb_shares_area) && 
           can_shared(length - l, shares, B, comb_shares_area)) {
          return (cache[length][mask] = true);
        }
      }
    }
  }

  return (cache[length][mask] = false);
}


namespace algorithms::onlinejudge::advanced_topics::sharing_chocolate
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

        int n, t_case = 1;
        while(stdin_read(n) && n) {
          int height, length;
          stdin_read(height, length);
          vi shares(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> shares[i];
          }
          vi comb_shares_area(1 << n);
          for(int mask = 0; mask < (1 << n); ++mask) {
            int size = 0;
            for(int i = 0; i < n; ++i) {
              if(mask & (1 << i)) {
                size += shares[i];
              }
            }
            comb_shares_area[mask] = size;
          }

          bool is_area_same = comb_shares_area[(1 << n) - 1] == height * length;
          std::memset(cache, -1, sizeof cache);
          printf("Case %d: %s\n", t_case++, is_area_same && can_shared(length, shares, (1 << n) - 1, comb_shares_area) ? "Yes" : "No");
        }
    }
}