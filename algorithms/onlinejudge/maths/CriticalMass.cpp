/*
───────────────────────────────────────────────────────────────
🧳 UVa 580 Critical Mass, related to Tribonacci series; Tribonacci numbers
   are the generalization of Fibonacci numbers; it is defined by T1 = 1, T2 = 1,
   T3 = 2, and Tn = Tn−1 + Tn−2 + Tn−3 for n ≥ 4,  
   https://onlinejudge.org/external/5/580.pdf, rt: s
───────────────────────────────────────────────────────────────
0
0
1
3
8
20
47
107
238
520
1121
2391
5056
10616
22159
46023
95182
196132

 * --- Problem-Solving Strategy for UVa 580 - Critical Mass ---
 *
 * This is a classic combinatorial counting problem. The goal is to find the number of
 * binary sequences of length N that contain at least one block of 3 or more consecutive
 * 'URANIUM's (let's say '1's).
 *
 * PHASE 1: EMPIRICAL DISCOVERY VIA BACKTRACKING
 * A direct mathematical formula is not immediately obvious. The constraints on N (up to 31)
 * are small enough to allow for a more direct, computational approach first.
 *
 * 1.  Backtracking with Memoization (Top-Down DP):
 *     A recursive function was written to build all 2^N sequences. The state for the
 *     memoization was (current_length, consecutive_uraniums, has_critical_block_been_found).
 *
 * 2.  Generating the Sequence:
 *     This correct but slow approach was used to generate the first ~30 terms of the
 *     answer sequence. The output began: 0, 0, 1, 3, 8, 20, 47, 107, 238, 520, ...
 *
 * PHASE 2: PATTERN RECOGNITION (THE "AHA!" MOMENT)
 *
 * 1.  The OEIS (On-Line Encyclopedia of Integer Sequences):
 *     The generated sequence was plugged into the OEIS at https://oeis.org/.
 *
 * 2.  The Match:
 *     The sequence was a perfect match for A050231, described as "the number of n-tosses
 *     of a fair coin having a run of 3 or more heads." This is a mathematical isomorphism
 *     of our problem (URANIUM = Heads, LEAD = Tails).
 *
 * PHASE 3: THE ELEGANT COMBINATORIAL SOLUTION
 *
 * The OEIS entry provides a much more efficient formula based on a common combinatorial
 * technique: counting the complement.
 *
 * Total Sequences = 2^N
 * "Safe" Sequences = Number of sequences with NO run of 3 or more URANIUMs.
 * Answer = Total Sequences - "Safe" Sequences
 *
 * The number of "safe" sequences follows a Tribonacci-like recurrence relation.
 * Let S(n) be the number of safe sequences of length n:
 *   - A safe sequence of length n can be formed by adding:
 *     - 'L' to any safe sequence of length n-1.
 *     - 'LU' to any safe sequence of length n-2.
 *     - 'LUU' to any safe sequence of length n-3.
 *   - This gives the recurrence: S(n) = S(n-1) + S(n-2) + S(n-3).
 *
 * The final implementation calculates S(n) using a simple DP loop and then
 * computes (2^n - S(n)) for the final answer. This is an efficient O(N) solution.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;

constexpr int CRITICAL_UNITS = 2;
// Assuming max possible cap is 100 for this example
constexpr int MAX_CAP = 101; 

ull memo[MAX_CAP][MAX_CAP][2];

enum Element { URANIUM, LEAD, EMPTY };


struct State 
{
    int slot;
    int u_stack;
    bool is_critical;
    Element prev_el;
};


using v_el = std::vector<Element>;


ull backtrack(State state, int cap) {
  // BASE CASE: We have filled all slots.
  if (state.slot == cap) {
    return state.is_critical == true ? 1 : 0;
  }
  
 // --- MEMOIZATION CHECK ---
  // Before computing, check if we've already solved this exact subproblem.
  if (memo[state.slot][state.u_stack][state.is_critical] != -1ULL) {
    return memo[state.slot][state.u_stack][state.is_critical];
  }


  ull total_ways = 0;

  // --- BRANCH 1: Place URANIUM ---
  State u_state;
  u_state.slot = state.slot + 1;
  u_state.prev_el = URANIUM;
  u_state.u_stack = (state.prev_el == URANIUM) ? state.u_stack + 1 : 1;
  u_state.is_critical = state.is_critical || (ull)(u_state.u_stack > CRITICAL_UNITS);
  
  // Just recurse. No counting is done when placing a uranium.
  total_ways += backtrack(u_state, cap);
  
  // --- BRANCH 2: Place LEAD ---
  State l_state;
  l_state.slot = state.slot + 1;
  l_state.prev_el = LEAD;
  l_state.u_stack = 0; // Reset uranium stack since we placed lead.
  l_state.is_critical = state.is_critical;

  // Recurse for the lead branch.
  total_ways += backtrack(l_state, cap);

  return memo[state.slot][state.u_stack][state.is_critical] = total_ways;
}

namespace algorithms::onlinejudge::maths::critical_mass
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

        // Precompute the number of "safe" sequences S(n) up to n = 31
        const int MAX_N = 31;
        std::vector<ull> SEQ(MAX_N + 1, 0);
        SEQ[0] = 1; // Empty sequence
        SEQ[1] = 2; // "L", "U"
        SEQ[2] = 4; // "LL", "LU", "UL", "UU"
        for (int n = 3; n <= MAX_N; n++) {
          SEQ[n] = SEQ[n - 1] + SEQ[n - 2] + SEQ[n - 3];
        }

        int cap;
        while(scanf("%d", &cap) == 1 && cap != 0) {
          // Initialize memo table with -1 for each test case
          // memset(memo, -1, sizeof(memo));
          // State initial_state = {0, 0, false, EMPTY};
          // printf("%llu\n", backtrack(initial_state, cap));
          ull total_sequences = 1ULL << cap; // 2^n
          ull safe_sequences = SEQ[cap];
          ull result = total_sequences - safe_sequences;
          printf("%llu\n", result);
        }
    }
}