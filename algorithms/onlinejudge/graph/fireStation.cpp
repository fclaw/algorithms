/**
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10278 Fire Station, rt: s
 * ───────────────────────────────────────────────────────────────
 * -------------------------------------------------------------------------------------
 * ALGORITHM STRATEGY: UVa 10278 - Fire Station
 * -------------------------------------------------------------------------------------
 *
 * The core of this problem is to find a single location for a new fire station
 * that MINIMIZES the MAXIMUM distance from any intersection to its nearest station.
 * This is a classic "minimax" problem. A direct greedy approach (e.g., placing the
 * station nearest to the currently worst-off intersection) will fail. The only
 * guaranteed way to find the optimal solution is a full search over all possible
 * locations for the new station.
 *
 * To make this full search efficient, we break the solution into two phases:
 * a one-time, heavy pre-calculation phase, followed by a fast search phase.
 *
 *
 * -------------------------------------------------------------------------------------
 * PHASE 1: PRE-CALCULATION (One-time Setup)
 * -------------------------------------------------------------------------------------
 *
 * The goal of this phase is to compute all necessary distances upfront so that the
 * main search loop can perform its calculations in O(1) time.
 *
 *  Step 1: Calculate All-Pairs Shortest Paths (APSP)
 *  --------------------------------------------------
 *  *   ACTION:   Create a 2D matrix, `dist[i][j]`, to store the shortest distance
 *              between every pair of intersections `(i, j)`.
 *  *   METHOD:   The graph is sparse (up to 500 intersections, ~20 edges each).
 *              Therefore, we run Dijkstra's algorithm N times, once starting
 *              from each intersection `k` from 1 to N.
 *  *   RESULT:   A fully populated `dist` matrix, allowing O(1) lookup for the
 *              distance between any two intersections.
 *
 *  Step 2: Calculate Distances to the EXISTING Fire Station Network
 *  ------------------------------------------------------------------
 *  *   ACTION:   Create a 1D array, `dist_to_nearest_old[v]`, to store the
 *              shortest distance from any intersection `v` to its closest
 *              *existing* fire station.
 *  *   METHOD:   For each intersection `v` from 1 to N:
 *                  - Find `min(dist[v][s])` for all existing fire station locations `s`.
 *                  - Store this minimum value in `dist_to_nearest_old[v]`.
 *              (Optimization Note: This can also be done with a single multi-source
 *              Dijkstra run, starting with all existing stations in the priority queue
 *              at distance 0).
 *  *   RESULT:   We now know the "baseline" maximum travel time for every intersection
 *              before our new station is built. This array will be used repeatedly.
 *
 *
 * -------------------------------------------------------------------------------------
 * PHASE 2: FULL SEARCH (Finding the Optimal Location)
 * -------------------------------------------------------------------------------------
 *
 * With all distances pre-calculated, we can now efficiently iterate through all
 * possible locations for the new fire station and evaluate each one.
 *
 *  Step 3: Iterate Through All Candidates and Find the Best One
 *  -------------------------------------------------------------
 *  *   ACTION:   Find the intersection `u` that, when chosen as the new station's
 *              location, produces the minimum possible "maximum distance".
 *  *   METHOD:   We use a nested loop structure:
 *
 *              Initialize `min_max_dist = infinity`, `best_location = -1`.
 *
 *              // Outer loop: Iterate through all candidate locations for the new station.
 *              FOR each intersection `u` from 1 to N:
 *
 *                  Initialize `current_max_dist = 0`.
 *
 *                  // Inner loop: Evaluate this choice by checking every house.
 *                  FOR each intersection `v` from 1 to N:
 *
 *                      // For house `v`, find its distance to the nearest station,
 *                      // which is either one of the old ones or the new one at `u`.
 *                      dist_to_new = dist[v][u];
 *                      dist_to_old_network = dist_to_nearest_old[v];
 *                      dist_for_v = min(dist_to_new, dist_to_old_network);
 *
 *                      // Update the worst-case for the current candidate `u`.
 *                      current_max_dist = max(current_max_dist, dist_for_v);
 *
 *                  // After checking all houses, if building at `u` gives a better
 *                  // overall result than we've seen so far, update our answer.
 *                  IF current_max_dist < min_max_dist:
 *                      min_max_dist = current_max_dist;
 *                      best_location = u;
 *
 *  *   RESULT:   The final value of `best_location` is the answer to the problem.
 *
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/dijkstra.cpp"

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
#include <cctype>
#include <utility>
#include <functional>
#include <set>




namespace dijkstra = algorithms::onlinejudge::graph::tools::dijkstra;
namespace wg = algorithms::onlinejudge::graph::tools::wg;


tools::vvi calculate_apsp(int V, const wg::WGraph<>& graph) {
  // all pairs shortest paths matrix
  tools::vvi apsp(V, tools::vi(V, inf<int>));
  for(int v = 0; v < V; ++v) {
    wg::WNode<> start = wg::mkWNode(v, 0);
    dijkstra::Dijkstra<> dijkstra_s(V, start);
    dijkstra_s.mappend = [](int w, int a) { return w + a; };
    dijkstra::dijkstra(graph, dijkstra_s);
    apsp[v] = dijkstra_s.dist;
  }
  return apsp;
}


std::unordered_map<int, int> calculate_old_dist(int V, const tools::vvi& apsp, const std::unordered_set<int>& old) {
  std::unordered_map<int, int> dist_to_old;
  for(int v = 0; v < V; ++v) {
    if(old.count(v)) { 
      dist_to_old[v] = 0; // Explicitly handle the base case
    } else {
      int min_dist = inf<int>;
      for(int s : old)
        min_dist = std::min(min_dist, apsp[v][s]);
      dist_to_old[v] = min_dist;
    }
  }
  return dist_to_old;
}


namespace algorithms::onlinejudge::graph::fire_station
{
    /** https://onlinejudge.org/external/102/10278.pdf */
    int t_cases, F, V; // F stands for the number of fire stations
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
        bool is_first = true;
        while(t_cases--) {
          while_read(F, V);
          std::unordered_set<int> old;
          int station;
          for(int i = 0; i < F; ++i) {
            while_read(station);
            --station;
            old.insert(station);
          }
          int s, e, length;
          wg::WGraph<> graph(V);
          std::string line;
          std::cin.ignore();
          while(std::getline(std::cin, line) && 
                !line.empty()) {
            std::stringstream ss(line);
            ss >> s >> e >> length;
            --s; --e;
            wg::pair(graph, s, e, length);
          }

          // all pairs shortest paths matrix
          tools::vvi apsp = calculate_apsp(V, graph);
          // the closest fire station to every town
          std::unordered_map<int, int> old_dist = calculate_old_dist(V, apsp, old);

          int min_max_dist = inf<int>, best_location = -1;
          for(int u = 0; u < V; ++u) {
            int current_max_dist = 0;
            for(int v = 0; v < V; ++v) {
              int dist_to_new = apsp[v][u];
              int dist_to_old = old_dist[v];
              int dist_for_v = std::min(dist_to_new, dist_to_old);
              current_max_dist = std::max(current_max_dist, dist_for_v);
            }
            if(min_max_dist > current_max_dist) {
                min_max_dist = current_max_dist;
                best_location = u;
            }
          }
          if(!is_first) std::cout << std::endl;
          else is_first = false;
          std::cout << best_location + 1 << std::endl;
        }
    }
}