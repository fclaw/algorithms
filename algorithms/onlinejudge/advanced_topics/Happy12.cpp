/*
───────────────────────────────────────────────────────────────
🧳 UVa 12445 Happy 12, https://onlinejudge.org/external/124/12445.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../maths/utility/permutations.cpp"
#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

using vi = std::vector<int>;

constexpr int SIZE = 12;
constexpr int MAX_MOVES_DEPTH = 8;
constexpr int MAX_SOLUTION_DEPTH = 19;


namespace perm = algorithms::onlinejudge::maths::utility::permutations;


// ============================================================
// 1. LEFT RING ROTATIONS (Indices: 0, 1, 2, 3, 4, 5, 11)
// ============================================================

void turn_left_ring_clockwise(vi& perm) {
    int t0 = perm[0];
    perm[0]  = perm[1];
    perm[1]  = perm[2];
    perm[2]  = perm[3];
    perm[3]  = perm[4];
    perm[4]  = perm[5];
    perm[5]  = perm[11];
    perm[11] = t0;
}

void restore_from_left_ring_clockwise(vi& perm) {
    // Inverse of L_CW is L_CCW
    int t11 = perm[11];
    perm[11] = perm[5];
    perm[5]  = perm[4];
    perm[4]  = perm[3];
    perm[3]  = perm[2];
    perm[2]  = perm[1];
    perm[1]  = perm[0];
    perm[0]  = t11;
}

void turn_left_ring_counter_clockwise(vi& perm) {
    restore_from_left_ring_clockwise(perm);
}

void restore_from_left_ring_counter_clockwise(vi& perm) {
    turn_left_ring_clockwise(perm);
}

// ============================================================
// 2. RIGHT RING ROTATIONS (Indices: 5, 6, 7, 8, 9, 10, 11)
// ============================================================

void turn_right_ring_clockwise(vi& perm) {
    int t11 = perm[11];
    perm[11] = perm[5];
    perm[5]  = perm[6];
    perm[6]  = perm[7];
    perm[7]  = perm[8];
    perm[8]  = perm[9];
    perm[9]  = perm[10];
    perm[10] = t11;
}

void restore_from_right_ring_clockwise(vi& perm) {
    // Inverse of R_CW is R_CCW
    int t10 = perm[10];
    perm[10] = perm[9];
    perm[9]  = perm[8];
    perm[8]  = perm[7];
    perm[7]  = perm[6];
    perm[6]  = perm[5];
    perm[5]  = perm[11];
    perm[11] = t10;
}

void turn_right_ring_counter_clockwise(vi& perm) {
    restore_from_right_ring_clockwise(perm);
}

void restore_from_right_ring_counter_clockwise(vi& perm) {
    turn_right_ring_clockwise(perm);
}

// ============================================================
// 3. WHOLE PUZZLE ROTATIONS (All 12 Tokens)
// ============================================================

void turn_puzzle_clockwise(vi& perm) {
    // Shift left by 1: [1..12] -> [2, 3, ..., 12, 1]
    std::rotate(perm.begin(), perm.begin() + 1, perm.end());
}

void restore_puzzle_from_clockwise(vi& perm) {
    // Shift right by 1: [1..12] -> [12, 1, 2, ..., 11]
    std::rotate(perm.begin(), perm.end() - 1, perm.end());
}

void turn_puzzle_counter_clockwise(vi& perm) {
    restore_puzzle_from_clockwise(perm);
}

void restore_puzzle_from_counter_clockwise(vi& perm) {
    turn_puzzle_clockwise(perm);
}

using MoveFunc = void (*)(vi&);

// 6 Pairs of {Apply Move, Restore Move}
const std::pair<MoveFunc, MoveFunc> moves[6] = {
    {turn_left_ring_clockwise,          restore_from_left_ring_clockwise},
    {turn_left_ring_counter_clockwise,  restore_from_left_ring_counter_clockwise},
    {turn_right_ring_clockwise,         restore_from_right_ring_clockwise},
    {turn_right_ring_counter_clockwise, restore_from_right_ring_counter_clockwise},
    {turn_puzzle_clockwise,             restore_puzzle_from_clockwise},
    {turn_puzzle_counter_clockwise,     restore_puzzle_from_counter_clockwise}
};


struct State
{
    /**
     * 1. puzzle (The 12 Tokens Permutation)
     * -------------------------------------
     * A 1D array of 12 integers representing the current positions of tokens 1..12:
     *   Index 0..4   : Left outer arc  (Tokens 1, 2, 3, 4, 5)
     *   Index 5      : Bottom intersection (Token 6)
     *   Index 6..10  : Right outer arc (Tokens 7, 8, 9, 10, 11)
     *   Index 11     : Top intersection    (Token 12)
     * 
     * Target Solved State:
     *   puzzle = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
     * 
     * Search Space:
     *   12! = 479,001,600 permutations.
     */
    vi permutation;

    /**
     * 2. moves (Distance / Step Count g(n))
     * -------------------------------------
     * The number of wheel rotations executed so far from the start.
     */
    int moves;
};


int min_moves_required(vi& target) {

  vi source = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }; // source

  perm::ll s_perm_idx = perm::getPermutationIndex(source);
  perm::ll d_perm_idx = perm::getPermutationIndex(target);

  std::queue<State> queue;
  std::unordered_map<perm::ll, int> dist_s; // expansion from source
  dist_s[s_perm_idx] = 0;
  queue.push({source, 0});

  int min_moves = INT32_MAX;
  
  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    vi& curr_perm = state.permutation;
    int moves_so_far = state.moves;
    perm::ll curr_perm_idx = perm::getPermutationIndex(curr_perm);

    if(curr_perm_idx == d_perm_idx) {
      min_moves = moves_so_far;
      break;
    }
    
    if(moves_so_far > MAX_MOVES_DEPTH) {
      continue;
    }

    for(std::pair<MoveFunc, MoveFunc> m : moves) {
      m.first(curr_perm); // 1. Apply Turn
      perm::ll next_idx = perm::getPermutationIndex(curr_perm);
      if(dist_s.find(next_idx) == dist_s.end()) {
        dist_s[next_idx] = 1 + moves_so_far;
        queue.push({curr_perm,  1 + moves_so_far});
      }
      m.second(curr_perm); // 2. Restore (Backtrack)
    }
  }

  if(min_moves == INT32_MAX) {
    std::queue<State> queue;
    std::unordered_map<perm::ll, int> dist_t; // expansion from target
    dist_t[d_perm_idx] = 0;
    queue.push({target, 0});
    
    while(!queue.empty()) {
      State state = queue.front(); queue.pop();
      vi& curr_perm = state.permutation;
      int moves_so_far = state.moves;
      perm::ll curr_perm_idx = perm::getPermutationIndex(curr_perm);

      if(auto it = dist_s.find(curr_perm_idx); 
         it != dist_s.end()) {
        min_moves = it->second + moves_so_far;
        break;
      }
        
      if(moves_so_far > MAX_MOVES_DEPTH) {
        continue;
      }

      for(std::pair<MoveFunc, MoveFunc> m : moves) {
        m.first(curr_perm); // 1. Apply Turn
        perm::ll next_idx = perm::getPermutationIndex(curr_perm);
        if(dist_t.find(next_idx) == dist_t.end()) {
          dist_t[next_idx] = 1 + moves_so_far;
          queue.push({curr_perm,  1 + moves_so_far});
        }
        m.second(curr_perm); // 2. Restore (Backtrack)
      }
    }
  }

  if(min_moves == INT32_MAX) {
    min_moves = MAX_SOLUTION_DEPTH;
  }
  return min_moves;
}


namespace algorithms::onlinejudge::advanced_topics::happy_12
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
          vi puzzle(SIZE);
          for(int i = 0; i < SIZE; ++i) {
            std::cin >> puzzle[i];
          }
          printf("%d\n", min_moves_required(puzzle));
        }
    }
}
