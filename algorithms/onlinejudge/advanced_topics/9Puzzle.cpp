/*
───────────────────────────────────────────────────────────────
🧳 UVa 11513 9 Puzzle, https://onlinejudge.org/external/115/11513.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;


constexpr int inf = std::numeric_limits<int>::max();
constexpr int L = 3;
constexpr int SHIFT = 4; 

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

    /**
     * 2. steps (Move Count / Distance)
     * --------------------------------
     * The number of shift operations (H1..H3, V1..V3) executed 
     * to reach this layout.
     * 
     * Since all moves cost 1, this is unweighted shortest path distance.
     */
    int steps;

    std::string path;  // Sequence of moves taken so far (e.g., "H1V2H3")
};

// Pack vector of 9 ints into a single uint64_t
inline uint64_t pack(const vi& layout) {
  uint64_t packed = 0;
  for (int i = 0; i < 3 * L; ++i) {
    packed |= (static_cast<uint64_t>(layout[i]) << (i * SHIFT));
  }
  return packed;
}

// Unpack uint64_t back into vector of 9 ints
inline vi unpack(uint64_t packed) {
  vi layout(9);
  for (int i = 0; i < 3 * L; ++i) {
    layout[i] = (packed >> (i * SHIFT)) & 0xF; // 0xF is mask 0b1111 (4 bits)
  }
  return layout;
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


std::string get_min_steps_required(const vi& target) {

  vi source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  uint64_t t_packed = pack(target);
  std::queue<State> queue;
  std::unordered_set<uint64_t> visited;
  queue.push({source, 0, {}});
  
  int min_steps_required = inf;
  std::string min_path;

  while(!queue.empty()) {

    State state = queue.front(); queue.pop();
    vi layout = state.layout;
    int steps = state.steps;
    auto path = state.path;

    uint64_t l_packed = pack(layout);


    if(l_packed == t_packed) {
      min_steps_required = steps;
      min_path = path;
      break;
    }
   
    if(visited.count(l_packed)) {
      continue;
    }

    visited.insert(l_packed);

    for(int r = 0; r < L; ++r) {
      shift_left(layout, r);
      std::string  new_path = path + "H" + std::to_string(r + 1);
      State new_state = {layout, 1 + steps, new_path};
      queue.push(new_state);
      shift_right(layout, r);
    }

    for(int c = 0; c < L; ++c) {
      shift_down(layout, c);
      std::string  new_path = path + "V" + std::to_string(c + 1);
      State new_state = {layout, 1 + steps, new_path};
      queue.push(new_state);
      shift_up(layout, c);
    }

  }

  if(min_steps_required == inf) {
    return "Not solvable";
  } else {
    return std::to_string(min_steps_required) + " " + min_path;
  }
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