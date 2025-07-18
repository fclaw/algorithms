/*
───────────────────────────────────────────────────────────────
🧳 UVa  907 Winterim Backpacking Trip, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cctype>



constexpr int CAMPS = 610;
constexpr int NIGHTS = 310;
constexpr int inf = 1e5;


using vi = std::vector<int>;
using vvi = std::vector<vi>;


struct State
{
    int camp;
    int nights_passed;
};



namespace algorithms::onlinejudge::graph::winterim
{
    /** https://onlinejudge.org/external/9/907.pdf */
    int camps, nights, last_camp, dest;
    int memo[CAMPS][NIGHTS];
    int calculate_minmax_of_walking(State s, const vi& walks, const vvi& dist) {
      int curr_camp = s.camp;
      int nights_passed = s.nights_passed;

      if(nights_passed > nights) return inf;

      if(curr_camp == dest) {
        return nights_passed == nights ? 0 : inf;
      } else if(curr_camp == last_camp) {
        return nights_passed == nights ? dist[curr_camp][dest] : inf;
      }
     
      int& best = memo[curr_camp][nights_passed];
      if(~best) return best;

      best = inf;
      for(int next_camp = curr_camp + 1; next_camp <= dest; ++next_camp) {
        int walk = dist[curr_camp][next_camp];
        int next_nights_passed = nights_passed;
        if(next_camp < dest) ++next_nights_passed;
        State ns = {next_camp, next_nights_passed};
        int next_max_walk = calculate_minmax_of_walking(ns, walks, dist);
        if(next_max_walk != inf) best = std::min(best, std::max(next_max_walk, walk));
      }

      return best;
    }
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
        
        while(while_read(camps, nights)) {
          dest = camps + 1; last_camp = camps;
          vi walks(camps + 1);
          for(int c = 0; c <= camps; ++c) {
            while_read(walks[c]);
          }

          // add to points: start, end
          vvi dist(camps + 2, vi(camps + 2));
          // 1. Create the prefix sum array.
          vi prefix_sum(camps + 2, 0);
          for(int i = 0; i <= camps; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + walks[i];
          }

          // 2. Populate the full distance matrix.
          for(int i = 0; i <= camps + 1; ++i) {
            for (int j = 0; j <= camps + 1; ++j) {
              // Distance from i to j is the absolute difference of their
              // distances from the start (node 0).
              dist[i][j] = std::abs(prefix_sum[j] - prefix_sum[i]);
            }
          }

          std::memset(memo, -1, sizeof memo);
          std::cout << calculate_minmax_of_walking({0, 0}, walks, dist) << std::endl;
        }
    }
}