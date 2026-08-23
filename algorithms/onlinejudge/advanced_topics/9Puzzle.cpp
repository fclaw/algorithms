/*
───────────────────────────────────────────────────────────────
🧳 UVa 11513 9 Puzzle, https://onlinejudge.org/external/115/11513.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * Problem: UVa 11513 - 9-Puzzle
 * Paradigm: Offline Precomputation via Single-Source Backward BFS
 * ============================================================================
 * 
 * 💡 KEY ARCHITECTURAL INSIGHT:
 * ----------------------------
 * 1. Small Finite State Space:
 *    The puzzle is a permutation of 9 unique digits (1..9).
 *    Total possible board configurations = 9! = 362,880 states.
 * 
 * 2. Shared Target & Multiple Test Cases:
 *    Every single test case shares the EXACT SAME goal state:
 *        1 2 3
 *        4 5 6
 *        7 8 9
 *    Running a forward BFS per test case repeatedly traverses the same states 
 *    and results in Time Limit Exceeded (TLE).
 * 
 * 🚀 STRATEGY: BACKWARD BFS PRECOMPUTATION
 * ---------------------------------------
 * • At program startup, execute ONE single BFS starting BACKWARDS from the 
 *   solved goal state {1, 2, 3, 4, 5, 6, 7, 8, 9}.
 * 
 * • Transition Inversion:
 *   To move AWAY from the goal into ancestor states, apply inverse shifts:
 *     - Forward H_r (Shift Left)  <---> Backward: Shift RIGHT (record as H_r)
 *     - Forward V_c (Shift Down)  <---> Backward: Shift UP    (record as V_c)
 * 
 * • Path Reconstruction:
 *   If state V is reached from U via inverse move M, the forward solution for V is:
 *       path(V) = M + path(U)
 * 
 * ⏱️ COMPLEXITY:
 * -------------
 * • Precomputation Time : O(9!) ≈ 0.08 seconds (executed once at startup).
 * • Query Time          : O(1) instant hash lookup per test case.
 * • Space Complexity    : ~15 MB to store all 362,880 answers in memory.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;


constexpr int L = 3;
constexpr int SHIFT = 4; 

const std::string H_moves[3] = {"H1", "H2", "H3"};
const std::string V_moves[3] = {"V1", "V2", "V3"};

struct State
{
    /**
     * 1. layout (Flattened 3x3 Grid Permutation)
     * ------------------------------------------
     * A 1D array of 9 integers representing the 3x3 grid:
     *   Index: [0, 1, 2] -> Row 1
     *          [3, 4, 5] -> Row 2
     *          [6, 7, 8] -> Row 3
     * 
     * Target Goal State:
     *   layout = {1, 2, 3, 4, 5, 6, 7, 8, 9}
     *
     * Total possible permutations = 9! = 362,880 states.
     */
    vi layout;
};

// Pack vector of 9 ints into a single uint64_t
inline uint64_t pack(const vi& layout) {
  uint64_t packed = 0;
  for (int i = 0; i < 3 * L; ++i) {
    packed |= (static_cast<uint64_t>(layout[i]) << (i * SHIFT));
  }
  return packed;
}


// 1. Shift LEFT (Forward H move): [A, B, C] -> [B, C, A]
void shift_left(vi& layout, int r) {
    int b = r * 3;
    std::swap(layout[b + 0], layout[b + 1]);
    std::swap(layout[b + 1], layout[b + 2]);
}

// 2. Shift RIGHT (Backward H move): [A, B, C] -> [C, A, B]
void shift_right(vi& layout, int r) {
    int b = r * 3;
    std::swap(layout[b + 0], layout[b + 1]);
    std::swap(layout[b + 0], layout[b + 2]);
}

// 3. Shift DOWN (Forward V move): [Top, Mid, Bot] -> [Bot, Top, Mid]
void shift_down(vi& layout, int c) {
    std::swap(layout[c + 3], layout[c + 6]);
    std::swap(layout[c + 0], layout[c + 3]);
}

// 4. Shift UP (Backward V move): [Top, Mid, Bot] -> [Mid, Bot, Top]
void shift_up(vi& layout, int c) {
    std::swap(layout[c + 0], layout[c + 3]);
    std::swap(layout[c + 3], layout[c + 6]);
}


// Stores the precomputed shortest answer for each configuration
struct Answer {
  int steps;
  std::string path;
};

std::unordered_map<uint32_t, Answer> memo;

// ============================================================
// 1. RUN THIS ONCE AT START OF MAIN (Precompute all 362,880 states)
// ============================================================
void precompute() {

  vi source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::queue<State> queue;
  memo[pack(source)] = {0, {}};
  queue.push({source});
  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    vi layout = state.layout;
    uint32_t l_packed = pack(layout);


    Answer ans = memo[l_packed];
    for(int r = 0; r < L; ++r) {
      shift_left(layout, r);
      std::string new_path = H_moves[r] + ans.path;
      int new_steps = 1 + ans.steps;
      uint32_t n_packed = pack(layout);
      if(memo.find(n_packed) == memo.end()) {
        memo[n_packed] = {new_steps, new_path};
        queue.push({layout});
      }
      shift_right(layout, r); // backtrack
    }

    for(int c = 0; c < L; ++c) {
      shift_down(layout, c);
      std::string new_path = V_moves[c] + ans.path;
      int new_steps = 1 + ans.steps;
      uint32_t n_packed = pack(layout);
      if(memo.find(n_packed) == memo.end()) {
        memo[n_packed] = {new_steps, new_path};
        queue.push({layout});
      }
      shift_up(layout, c); // backtrack
    }
  }
}

// ============================================================
// 2. QUERY FUNCTION: O(1) Instant Lookup!
// ============================================================
std::string get_min_steps_required(const vi& target) {
  uint32_t t_packed = pack(target);
  auto it = memo.find(t_packed);
  if (it == memo.end()) {
    return "Not solvable";
  }
  return std::to_string(it->second.steps) + " " + it->second.path;
}

namespace algorithms::onlinejudge::advanced_topics::puzzle_9
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

        precompute();
        vi target(3 * L);
        while(scanf("%d %d %d %d %d %d %d %d %d",
                    &target[0], &target[1], &target[2],
                    &target[3],&target[4],&target[5],
                    &target[6],&target[7],&target[8]) == 9) {
          printf("%s\n", get_min_steps_required(target).c_str());
          target.clear();
        }
    }
}