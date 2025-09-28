/*
───────────────────────────────────────────────────────────────
🧳 UVa 10334 Ray Through Glasses, https://onlinejudge.org/external/103/10334.pdf, combinatorics, Java BigInteger, rt: s
───────────────────────────────────────────────────────────────
from 0 to 15 reflections:
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
fibonacci numbers

 * --- Problem-Solving Strategy for UVa 10334 - Ray Through Glasses ---
 *
 * This problem involves counting the distinct paths a ray of light can take
 * through a series of reflections on three walls (top, middle, bottom).
 *
 * The key insights are:
 * 1. The ray can start by hitting either the middle or bottom wall first.
 * 2. From each wall, the ray can reflect to specific other walls:
 *    - From TOP, it can go to MIDDLE or BOTTOM.
 *    - From MIDDLE, it can only go to TOP.
 *    - From BOTTOM, it can go to TOP or MIDDLE.
 * 3. The problem can be modeled as a state-space search where each state is
 *    defined by the current wall and the number of reflections left.
 *
 * A backtracking approach with memoization is used to explore all possible
 * sequences of reflections. To avoid counting duplicate sequences that are
 * identical in terms of the walls hit (regardless of order), we use a set
 * to store unique sequences represented in a packed integer format.
 *
 * The final implementation counts the number of unique sequences for a given
 * number of reflections and prints the result.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

using ull = unsigned long long;
using vi = std::vector<int>;

const int MAX = 1002;


enum WALL { TOP = 1, MIDDLE = 2, BOTTOM = 3 };

std::map<WALL, std::vector<WALL>> 
  wall_reflections_rules = {
    { TOP,    {MIDDLE, BOTTOM} },
    { MIDDLE, {TOP} },
    { BOTTOM, {TOP, MIDDLE}    }
  };

int pack_reflections(const vi& reflections) {
  int packed_state = 0;

  for(int wall : reflections) {
    // Shift the existing bits left by 2 to make space.
    packed_state <<= 2;    
    // Use bitwise OR to set the last 2 bits to the new wall value.
    packed_state |= wall;
  }
  return packed_state;
}

bool backtrack(int n_reflections_left, vi& curr_sequences, std::set<int>& seen_sequences) {
  if(n_reflections_left == 0) {
    int packed = pack_reflections(curr_sequences);
    if(seen_sequences.count(packed)) {
      return false; // Already seen this configuration
    }
    seen_sequences.insert(packed);
    return true; // Found a valid configuration
  }

    std::vector<WALL> last_walls; 
    if(curr_sequences.empty()) 
       last_walls = { MIDDLE, BOTTOM };
    else last_walls.push_back(static_cast<WALL>(curr_sequences.back()));

    for(WALL last_wall : last_walls) {
      for(WALL next_wall : wall_reflections_rules[last_wall]) {
        curr_sequences.push_back(next_wall);
        if(backtrack(n_reflections_left - 1, curr_sequences, seen_sequences)) {
          curr_sequences.pop_back();
          return true; // Found a valid configuration
        }
        curr_sequences.pop_back();
      }
    }
  return false; // No valid configuration found from this state
}


namespace algorithms::onlinejudge::maths::ray_through_glasses
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

        std::vector<bg::bigint> fib(MAX + 1);
        fib[0] = bg::bigint(0);
        fib[1] = bg::bigint(1);
        for (int i = 2; i <= MAX; i++) {
          fib[i] = fib[i - 1] + fib[i - 2];
        }  

        int n_reflections;
        while(scanf("%d", &n_reflections) == 1) {
        //   std::set<int> seen_sequences;
        //   vi curr_sequences;
        //   while(backtrack(n_reflections, curr_sequences, seen_sequences))
        //     curr_sequences.clear();
        //   printf("%lu\n", seen_sequences.size());
          std::cout << fib[n_reflections + 2] << "\n";
        }
    }
}