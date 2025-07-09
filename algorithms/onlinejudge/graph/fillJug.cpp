/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10603 Fill, rt: s
 * ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: State-Space Dimensionality Reduction
 * =====================================================================================
 *
 * This problem is a classic state-space search, solvable with a shortest path
 * algorithm like Dijkstra's. The key to an efficient solution lies in correctly
 * defining the state and recognizing opportunities for optimization.
 *
 * A powerful rule of thumb applies here and in many similar problems (like the
 * "Ferry Loading" problem):
 *
 * "IF THE SUM OF THINGS IS CONSTANT, REDUCE THE STATE BY 1."
 *
 * --- The State ---
 * A state can be uniquely described by the amount of water in each of the three
 * jugs: (water_A, water_B, water_C). This seems to imply a 3D state space.
 *
 * --- The Conservation Law ---
 * However, the total amount of water in the system never changes. It is always
 * equal to the initial capacity of the third jug, C.
 *
 *   water_A + water_B + water_C = C
 *
 * --- The Reduction ---
 * Because of this conservation law, if we know the amount of water in the first
 * two jugs (water_A, water_B), the amount in the third is automatically determined:
 *
 *   water_C = C - water_A - water_B
 *
 * The `water_C` variable is redundant. We can therefore reduce the dimensionality
 * of our state space from 3D to 2D.
 *
 *   - Naive State:      (water_A, water_B, water_C) -> Requires a 3D `dist` array.
 *   - Optimized State:  (water_A, water_B)        -> Requires a 2D `dist` array.
 *
 * This optimization drastically reduces memory usage (from O(N^3) to O(N^2)) and
 * simplifies the logic, making the solution both faster and more elegant. This
 * principle of using conservation laws to reduce state dimensionality is a
 * fundamental technique in dynamic programming and graph search algorithms.
 *
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>



constexpr int JUGS = 3;
constexpr int MAX_CAP = 201;
constexpr int inf = 1e5;

using vi = std::vector<int>;
using vvi = std::vector<vi>;

struct State
{
    int water_poured; // edge
    vi jugs_content; // how many water is in every jug 
    // for priority queue
    bool operator < (const State& other) const { return water_poured > other.water_poured; }
};


namespace algorithms::onlinejudge::graph::fill_jug
{
    /** https://onlinejudge.org/external/106/10603.pdf */
    int t_cases, target;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        while_read(t_cases);
        while(t_cases--) {
          vi jugs_capacity(JUGS);
          for(int j = 0; j < JUGS; ++j) 
            while_read(jugs_capacity[j]);
          while_read(target);
          

          vvi water(MAX_CAP, vi(MAX_CAP, inf)); // state matrix
          std::priority_queue<State> queue;
          water[0][0] = 0;
          queue.push({0, {0, 0, jugs_capacity[2]}});
          while(!queue.empty()) {
            State state = queue.top(); queue.pop();
            int water_poured = state.water_poured;
            vi jugs = state.jugs_content;              

            if(water_poured > water[jugs[0]][jugs[1]]) continue;

            for(int i = 0; i < JUGS; ++i) {
              for(int j = 0; j < JUGS; ++j) {
                if(i != j) {
                  int new_water_poured = water_poured;
                  vi new_jugs = jugs; // not to mess up with others jugs  
                  int i_content = new_jugs[i];
                  int j_space_left = jugs_capacity[j] - new_jugs[j]; // how much free space is left;
                  int amount_to_pour = std::min(i_content, j_space_left);
                  if(amount_to_pour == 0) continue;
                  new_jugs[i] -= amount_to_pour;
                  new_jugs[j] += amount_to_pour;

                  new_water_poured += amount_to_pour;
                  if(new_water_poured < water[new_jugs[0]][new_jugs[1]]) {
                    water[new_jugs[0]][new_jugs[1]] = new_water_poured;
                    queue.push({new_water_poured, new_jugs});
                  }
                }
              }
            }
          }

          int min_water = 0;
          int min_content = 0;

          for(int t = target; t >= 0; --t)
            for(int i = 0; i < MAX_CAP; ++i)
            for(int j = 0; j < MAX_CAP; ++j) {
              if(water[i][j] == inf) continue;
              int k = jugs_capacity[2] - i - j;
              if(i == t || j == t || k == t) {
                min_water = water[i][j];
                min_content = t;

                // We must now find the minimum cost for THIS d_prime
                // by checking all other states that also satisfy it.
                // (This is a subtle but important detail for correctness)
                // loop is necessary because the target condition ("a jug contains d liters") 
                // isn't a single destination node in the graph. 
                // It's a set of many possible destination nodes, 
                // and you need to find which of those is the cheapest to get to.
                for(int s_i = 0; s_i < MAX_CAP; ++s_i) {
                  for(int s_j = 0; s_j < MAX_CAP; ++s_j) {
                    if(water[s_i][s_j] == inf) continue;
                      int s_k = jugs_capacity[2] - s_i - s_j;
                      if(s_i == t || s_j == t || s_k == t) {
                        min_water = std::min(min_water, water[s_i][s_j]);
                      }
                    }
                  }
                // Go to a label to break out of all loops
                goto found_answer;
              }
            }

          found_answer:
          printf("%d %d\n", min_water, min_content);
        }
    }
}