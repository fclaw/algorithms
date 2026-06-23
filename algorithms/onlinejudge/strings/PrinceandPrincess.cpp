/*
───────────────────────────────────────────────────────────────
🧳 UVa 10635 Prince and Princess, https://onlinejudge.org/external/106/10635.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: LONGEST COMMON SUBSEQUENCE (LCS) TO LONGEST INCREASING SUBSEQUENCE (LIS)
 *            REDUCTION (Prince and Princess - UVa 10635)
 * ============================================================================
 * THE PROBLEM & THE O(N^2) WALL:
 * We need to find the Longest Common Subsequence between the Prince's path (A)
 * and the Princess's path (B). 
 * The length of the paths can be up to N^2 = 62,500. 
 * A standard LCS DP algorithm uses O(lenA * lenB) time and space, which results 
 * in ~4 billion operations and 15GB of memory -> Instant TLE and MLE.
 * 
 * THE MASTER INSIGHT (Uniqueness):
 * The problem states that all numbers in each sequence are DISTINCT (no duplicates).
 * Because the elements of A are unique, we can map every element to its physical 
 * index in A using a Direct Addressing Table (DAT). 
 * This transformation converts the Prince's path into a strictly increasing sequence:
 *      A = [1, 7, 5, 4, 8]  -->  mapped_A = [0, 1, 2, 3, 4] (Strictly Increasing!)
 * 
 * THE REDUCTION (LCS -> LIS):
 * Since the mapped version of A is strictly increasing, any common subsequence 
 * between A and B must also appear in strictly increasing order of A's indices.
 * 
 * Therefore, we can find the LCS of A and B by:
 * 1. Mapping: For each element in B, find its index in A (using our DAT). 
 *    If the element from B doesn't exist in A, we discard it.
 * 2. LIS: Find the Longest Increasing Subsequence of this mapped version of B.
 * 
 * This reduces the complexity from O(N^2) LCS to O(N log N) LIS using 
 * binary search (std::lower_bound).
 * 
 * THE 3-STEP FLOW:
 * ----------------
 * STEP 1: Map indices of Prince's path (A) to their arrival times (steps):
 *         pos_map[A[i]] = i;
 * 
 * STEP 2: Go through Princess's path (B). If the number exists in A, record
 *         its arrival step into a flat vector:
 *         if (pos_map.count(B[j])) mapped_B.push_back(pos_map[B[j]]);
 * 
 * STEP 3: Run the O(N log N) Active Tails LIS on 'mapped_B'. 
 *         The size of the tails array is our final answer.
 * 
 * COMPLEXITY:
 * - Time:  O((p + q) log(p + q)) -> Blazingly fast! (~0.01 seconds)
 * - Space: O(N^2) for the DAT map (under 250KB of memory)
 * 
 * ============================================================================
 * THE SUBTLETY OF THE TEMPORAL TRANSITION: VALUES TO STEPS
 * ============================================================================
 * The most subtle and brilliant part of the LCS-to-LIS reduction is how 
 * we redefine the identity of the data.
 * 
 * THE SPATIAL VIEW (Old):
 * We think of the paths as sequences of physical board coordinates:
 *      Prince    = [17,  5, 42,  8]
 *      Princess  = [ 5, 17,  8, 12]
 * 
 * THE TEMPORAL VIEW (New):
 * We discard the spatial coordinates entirely and replace them with the 
 * Prince's "Arrival Times" (indices):
 *      17 -> Step 0
 *       5 -> Step 1
 *      42 -> Step 2
 *       8 -> Step 3
 * 
 * Now, the Prince's path is a perfect, strictly increasing timeline:
 *      mapped_Prince = [0, 1, 2, 3]
 * 
 * THE MONOTONICITY LAW:
 * When we map the Princess's path using the Prince's timeline, we get:
 *      mapped_Princess = [1, 0, 3]  (representing: 5 -> 17 -> 8)
 * 
 * Any common subsequence must be valid for both runners. Since the Prince 
 * can only move forward in time along his timeline (0 -> 1 -> 2 -> 3), any 
 * valid common path must be strictly INCREASING in terms of his step numbers.
 * 
 * - The subsequence [1, 3] (5 -> 8) is INCREASING. (Valid! 1 < 3)
 * - The subsequence [1, 0] (5 -> 17) is DECREASING. (Invalid! 1 > 0. The 
 *   Princess is asking the Prince to travel backward in time).
 * 
 * By finding the Longest INCREASING Subsequence of the mapped array, we 
 * are mathematically guaranteed to find the longest path where the Princess's 
 * movements never violate the temporal flow of the Prince's journey!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;



// Returns the length of the Longest Increasing Subsequence in O(N log N)
int lis(const vi&  seq) {
  if (seq.empty()) 
    return 0;

  // tails[i] stores the smallest tail of all active increasing 
  // subsequences of length i+1 encountered so far.
  vi tails;

  for(int x : seq) {
    // Use binary search (O(log N)) to find the first element 
    // in 'tails' that is greater than or equal to 'x'
    auto it = std::lower_bound(tails.begin(), tails.end(), x);

    if (it == tails.end()) {
      // x is larger than any tail we've seen so far. 
      // This means we can extend the longest subsequence!
      tails.push_back(x);
    } else {
      // x can be used to make a shorter/better tail for an 
      // existing subsequence of some length. We overwrite it.
      *it = x;
    }
  }

  // The length of the 'tails' vector is the length of the LIS!
  return tails.size();
}




namespace algorithms::onlinejudge::strings::prince_and_princess
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

        int t_cases, N, L, M, t_case = 1;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::cin >> N >> L >> M;
          vi prince_seq(L + 1), princess_seq(M + 1);
          for(int i = 0; i <= L; ++i) {
            std::cin >> prince_seq[i];
          }
          for(int i = 0; i <= M; ++i) {
            std::cin >> princess_seq[i];
          }

          // map princes path: indices -> step
          vi index_to_step(N * N + 1, -1);
          for(int i = 0; i <= L; ++i) {
            int step = i + 1;
            index_to_step[prince_seq[i]] = step;
          }

          vi prince_steps;
          for(int i = 0; i <= M; ++i) {
            int idx = princess_seq[i];
            int step = index_to_step[idx];
            if(~step) {
              prince_steps.push_back(step);
            }
          }
          printf("Case %d: %d\n", t_case++, lis(prince_steps));
        }
    }
}