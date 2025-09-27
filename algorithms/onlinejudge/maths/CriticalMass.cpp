/*
───────────────────────────────────────────────────────────────
🧳 UVa 580 Critical Mass, related to Tribonacci series; Tribonacci numbers
   are the generalization of Fibonacci numbers; it is defined by T1 = 1, T2 = 1,
   T3 = 2, and Tn = Tn−1 + Tn−2 + Tn−3 for n ≥ 4,  
   https://onlinejudge.org/external/5/580.pdf, rt: s
───────────────────────────────────────────────────────────────
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

        int cap;
        while(scanf("%d", &cap) == 1 && cap != 0) {
          // Initialize memo table with -1 for each test case
          memset(memo, -1, sizeof(memo));
          State initial_state = {0, 0, false, EMPTY};
          printf("%llu\n", backtrack(initial_state, cap));
        }
    }
}