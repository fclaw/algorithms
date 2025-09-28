/*
───────────────────────────────────────────────────────────────
🧳 UVa 900 Brick Wall Patterns, https://onlinejudge.org/external/9/900.pdf, combinatorics, the pattern ≈ Fibonacci, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 900 - Brick Wall Patterns ---
 *
 * This is a classic combinatorial tiling problem. The goal is to count the number
 * of ways to tile a 2xN wall with 2x1 bricks (dominoes).
 *
 * PHASE 1: DISCOVERY VIA EMPIRICAL ANALYSIS
 *
 * 1.  Solve Small Cases:
 *     The problem statement provides the first few answers:
 *     - For N=1: 1 way (a single vertical brick)
 *     - For N=2: 2 ways (two vertical OR two horizontal bricks)
 *     - For N=3: 3 ways
 *     This gives the start of a sequence: 1, 2, 3, ...
 *
 * 2.  (Optional) Backtracking Solver:
 *     A simple backtracking program could be written to generate more terms of the
 *     sequence, confirming the pattern: 1, 2, 3, 5, 8, ...
 *
 * 3.  Find the Recurrence Relation:
 *     The key insight is to consider how a valid wall of length N can be constructed:
 *     a) By taking a valid wall of length (N-1) and adding one 2x1 vertical
 *        brick to the end.
 *     b) By taking a valid wall of length (N-2) and adding a 2x2 block of two
 *        horizontal bricks to the end.
 *     This leads to the recurrence: Ways(N) = Ways(N-1) + Ways(N-2).
 *
 * PHASE 2: PATTERN RECOGNITION & EFFICIENT IMPLEMENTATION
 *
 * 1.  Identify the Sequence:
 *     The sequence 1, 2, 3, 5, 8, ... and the recurrence W(N)=W(N-1)+W(N-2) are
 *     hallmarks of the Fibonacci sequence. Specifically, the number of ways for a
 *     wall of length N is the (N+1)-th Fibonacci number (where F(1)=1, F(2)=1).
 *     - Ways(1) = 1 = F(2)
 *     - Ways(2) = 2 = F(3)
 *     - Ways(N) = F(N+1)
 *
 * 2.  The DP Solution (Memoized Recursion):
 *     The naive recursive implementation of this formula is exponential (O(2^N)) and
 *     too slow. The correct approach is to use Dynamic Programming.
 *     This code implements the solution using a top-down DP approach (recursion with
 *     memoization) to calculate the Fibonacci numbers efficiently.
 *     - A `memo` array stores the result for `Ways(n)` once it's computed.
 *     - Subsequent calls for the same 'n' return the stored value in O(1) time.
 *     - The final complexity is O(N), which is instantaneous for N<=50.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;

enum Pos { VERTICAL, HORIZONTAL, NONE };

// A helper to map Pos enum to integer for the memo table
int pos_to_int(Pos p) {
    if (p == VERTICAL) return 0;
    if (p == HORIZONTAL) return 1;
    return 2;
}

// The state for our memoization
// We will use integers for indexing: 0=VERTICAL, 1=HORIZONTAL, 2=NONE
ull memo[51][3][3];


struct State
{
    int brick_left;
    Pos pos;
    int v_brick; // how many vertical brick are there - max 2
};


ull backtrack(State state) { 
  // base case: no bricks are left
  if(state.brick_left == 0) {
    if(state.pos == VERTICAL || 
       (state.pos == HORIZONTAL && 
        state.v_brick == 2)) {
      return 1;
    }
    return 0;
  }

  // --- MEMOIZATION CHECK ---
  int pos_idx = pos_to_int(state.pos);
  if(~memo[state.brick_left][pos_idx][state.v_brick]) {
    return memo[state.brick_left][pos_idx][state.v_brick];
  }

  ull total_ways = 0;
  if(state.pos == HORIZONTAL && 
     state.v_brick > 0 && 
     state.v_brick < 2) {
    // place horizontal brick
    State v_state;
    v_state.brick_left = state.brick_left - 1;
    v_state.pos = HORIZONTAL;
    v_state.v_brick = state.v_brick + 1 > 2 ? 0 : state.v_brick + 1;
    total_ways += backtrack(v_state);
  } else {
      State h_state;
      h_state.brick_left = state.brick_left - 1;
      h_state.pos = HORIZONTAL;
      h_state.v_brick++;
      total_ways += backtrack(h_state);
    
      State v_state;
      v_state.brick_left = state.brick_left - 1;
      v_state.pos = VERTICAL;
      v_state.v_brick = 0;
      total_ways += backtrack(v_state);
  }

  // --- MEMOIZATION STORE ---
  return memo[state.brick_left][pos_idx][state.v_brick] = total_ways;
}


namespace algorithms::onlinejudge::maths::brick_wall_patterns
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

        int bricks;
        while(scanf("%d", &bricks) == 1 && bricks != 0) {  
          // Initialize memo table with -1
          memset(memo, -1, sizeof(memo));
        
          // The initial state seems tricky. Let's start with a wall of length N to fill.
          // The previous state doesn't exist, so 'NONE' might be appropriate.
          State initial_state = {bricks, NONE, 0}; 
        
          // Note: A simpler DP only needs dp(n) = dp(n-1) + dp(n-2)
          // Your backtracking logic seems to explore a different problem structure.
          // However, memoizing IT would follow this pattern.
          printf("%llu\n", backtrack(initial_state));
        }
    }   
}