/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10356 Rough Roads, rt: s
 * ───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/w_graph.cpp"

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
#include <queue>
#include <deque>




namespace wg = algorithms::onlinejudge::graph::tools::wg;

template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();


struct State
{
    int point;
    bool is_on_cycle;
    int dist;
    bool operator < (const State& other) const {
      // We want the priority queue to pop the state with the lowest dist
      return dist > other.dist;
    }
};


namespace algorithms::onlinejudge::graph::rough_roads
{
    /** https://onlinejudge.org/external/103/10356.pdf */
    int V, E, t_case = 1;
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
        
        while(while_read(V, E)) {
          int source = 0, sink = V - 1;
          wg::WGraph<> roads(V);
          for(int e = 0; e < E; e++) {
            int from, to, length;
            while_read(from, to, length);
            wg::pair(roads, from, to, length, true);
          }

          std::vector<std::array<int, 2>> distance(V, {inf<int>, inf<int>});
          std::deque<State> queue;
          // he starts the journey with the flag is_on_cycle on assuming that prior we was on the bike
          distance[source][true] = 0;
          queue.push_back({source, true, 0});
          while(!queue.empty()) {
            State state = queue.front(); queue.pop_front();
            int point = state.point;
            bool is_on_cycle = state.is_on_cycle;
            int dist = state.dist;

            for(const wg::WNode<>& node : roads[point]) {
              int next_point = node.node;
              int w = node.weight + dist;
              if(distance[next_point][(int)!is_on_cycle] > w) {
                distance[next_point][(int)!is_on_cycle] = w;
                queue.push_front({next_point, !is_on_cycle, w});
              }
            }
          }
          int min_dist = distance[sink][true];
          printf("Set #%d\n%s\n", t_case++, min_dist == inf<int> ? "?" : std::to_string(min_dist).c_str());
        }
    }
}