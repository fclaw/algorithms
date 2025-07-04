/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 11367 Full Tank?, rt: s
 *
 * Problem Summary:
 * ----------------
 * Given a graph where each node (city) has a fuel price per litre and
 * each edge represents a road with a fuel cost (in litres), find the
 * minimum cost to travel from city `s` to city `t` with a car that has
 * a fuel tank of capacity `C`.
 *
 * Constraints:
 * ------------
 * - We can refuel any amount up to the tank's capacity, one litre at a time.
 * - Each refuel action at city `u` costs `fuel_price[u]` per litre.
 * - Fuel is consumed only while travelling (edges have weights in litres).
 * - Graph is sparse (up to 1,000 nodes and 10,000 edges), but the number
 *   of states is large due to the fuel dimension.
 *
 * Approach:
 * ---------
 * The graph is implicit: nodes are of the form (city, fuel_left).
 * Total number of states = n cities × (C + 1) fuel levels.
 *
 * We use a Dijkstra-like algorithm over state-space:
 *   - Each state is a tuple: (total_cost, city, fuel)
 *   - Transitions:
 *       1. Buy fuel: move to (city, fuel + 1) with +fuel_price[city] cost.
 *       2. Drive: if fuel ≥ road_length, move to (neigh, fuel - road_length)
 *   - Only generate neighbours on the fly (graph is generated lazily).
 *   - Priority queue ordered by cost for Dijkstra's greedy step.
 *   - Track dist[city][fuel] to avoid reprocessing higher-cost paths.
 *
 * Notes:
 * ------
 * - The classic Dijkstra abstraction does not work here due to the
 *   state-space being multi-dimensional and implicit.
 * - An ad-hoc implementation is necessary to handle custom state transitions.
 * ───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

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




namespace tools = algorithms::onlinejudge::graph::tools;

template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();

struct State
{
    int city; // number of city in the graph
    int fuel_left; // fuel left in the tank
    int total_cost; // total cost to reach this state
    // comparator for priority queue
    bool operator < (const State& other) const {
      // We want the priority queue to pop the state with the lowest total_cost
      return total_cost > other.total_cost; // Min-heap based on total_cost
    }
};


namespace algorithms::onlinejudge::graph::full_tank
{
    /** https://onlinejudge.org/external/113/11367.pdf  */
    int V, E, Q;
    int do_dijkstra(
      int dest, 
      int cap, 
      tools::vvi& dist, 
      std::priority_queue<State>& queue, 
      const tools::vi& price, 
      const tools::Graph<int>& roads) {
      
      while(!queue.empty()) {
        State state = queue.top(); queue.pop();
        int city = state.city;
        int fuel_left = state.fuel_left;
        int total_cost = state.total_cost;


        // If we reached the destination with enough fuel
        if(city == dest) return total_cost;

        // If this state is not better than the best known, skip it
        // pruning search space
        if(total_cost > dist[city][fuel_left]) continue;

        // Drive to neighbours
        for(const tools::Node<int>& neigh : roads[city]) {
          int next_city = neigh.node;
          int road_length = neigh.value;

          // If we have enough fuel to reach the neighbour
          // without refueling
          // We can drive to the neighbour without refueling
          // If fuel_left is less than road_length, we cannot drive
          // to the neighbour, so we skip this transition
          if(fuel_left >= road_length) {
            // We can drive to the neighbour without refueling
            int new_fuel_left = fuel_left - road_length;
            if(new_fuel_left < 0) break; // Cannot have negative fuel
            if(total_cost < dist[next_city][new_fuel_left]) {
              dist[next_city][new_fuel_left] = total_cost;
              queue.push({next_city, new_fuel_left, total_cost});
            }
          }

          // top up the tank if needed and try reaching the neighbour
          int needed_fuel = cap - fuel_left;
          int full_cost = total_cost + needed_fuel * price[city];
          if(needed_fuel >= road_length) {
            // We can drive to the neighbour
            int new_fuel_left = needed_fuel - road_length;
            if(new_fuel_left < 0) break; // Cannot have negative fuel
            if(full_cost < dist[next_city][new_fuel_left]) {
              dist[next_city][new_fuel_left] = full_cost;
              queue.push({next_city, new_fuel_left, full_cost});
            }
          }

          // Try refueling at the current city
          // We can refuel from 1 to road_length litres
          // and then try to reach the neighbour
          for(int l = 1; l <= road_length; ++l) {
            // If we can refuel at the current city
            if(fuel_left + l <= cap) {
              int new_fuel_left = fuel_left + l;
              int new_cost = total_cost + l * price[city];
              if(new_fuel_left >= road_length) {
                // We can drive to the neighbour after refueling
                new_fuel_left -= road_length; // Fuel left after driving
                if(new_cost < dist[next_city][new_fuel_left]) {
                  dist[next_city][new_fuel_left] = new_cost;
                  queue.push({next_city, new_fuel_left, new_cost});
                }
              } else {
                // We cannot drive to the neighbour, but we can refuel
                if(new_cost < dist[city][new_fuel_left]) {
                  dist[city][new_fuel_left] = new_cost;
                  queue.push({city, new_fuel_left, new_cost});
                }
              }
            }
          }
        }
      }
        return inf<int>; // If we cannot reach the destination
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
        
        while(while_read(V, E)) {
          tools::vi fuel_price(V);
          for(int i = 0; i < V; ++i) {
            while_read(fuel_price[i]);
          }

          tools::Graph<int> roads(V);
          for(int i = 0; i < E; ++i) {
            int u, v, l;
            while_read(u, v, l);
            roads[u].push_back(tools::mkIntNode(v, l));
            roads[v].push_back(tools::mkIntNode(u, l)); // Undirected graph
          }

          while_read(Q);
          for(int i = 0; i < Q; ++i) {
            int c, s, e;
            while_read(c, s, e);
            tools::vvi dist(V, tools::vi(c + 1, inf<int>));
            dist[s][0] = 0; // Starting point, no cost at city s
            std::priority_queue<State> pq;
            pq.push({s, 0, 0}); // (city, fuel_left, total_cost)
            int min_cost = do_dijkstra(e, c, dist, pq, fuel_price, roads);
            if(min_cost == inf<int>) {
              std::cout << "impossible\n";
            } else std::cout << min_cost << "\n";
          }
        }
    }
}