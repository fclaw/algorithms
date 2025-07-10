/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa  12047 Highest Paid Toll, rt: s
 * ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: The Pre-calculation Paradigm
 * =====================================================================================
 *
 * This problem, like many complex graph or search problems, is solved efficiently by
 * applying a fundamental and ubiquitous algorithmic pattern: Pre-calculation.
 *
 * The core idea is to separate the problem into two distinct phases:
 *   1. A one-time, upfront "investment" phase where we compute and store all
 *      necessary intermediate results.
 *   2. A fast "query" or "combination" phase where we use the stored results
 *      to find the final answer.
 *
 * This pattern is chosen when a naive approach would lead to massively redundant
 * calculations inside its main loop.
 *
 *
 * --- Application to This Problem (Highest Paid Toll) ---
 *
 * 1. The Goal: For every edge `u -> v`, check if the path `s -> u -> v -> t` is
 *    affordable (total cost <= p).
 *
 * 2. The Naive Approach (and its Redundancy):
 *    A slow solution would iterate through all M edges. For each edge, it would
 *    run a new shortest path search to find `dist(s, u)` and another for `dist(v, t)`.
 *    This repeatedly re-calculates the same path segments, leading to a complexity
 *    like O(M * E log V), which is too slow.
 *
 * 3. The Pre-calculation Solution (This Implementation):
 *    We identify that the values `dist(s, x)` and `dist(y, t)` for all nodes
 *    `x` and `y` are the quantities being re-computed.
 *
 *    *   PRE-CALCULATION PHASE:
 *        a) `dist(s, x)` for all `x`: Solved by running Dijkstra's once from `s`
 *           on the forward graph. The results are stored in `dist_from_s`.
 *        b) `dist(y, t)` for all `y`: Solved by running Dijkstra's once from `t`
 *           on the *reversed* graph. The results are stored in `dist_to_t`.
 *           This is a classic technique for finding shortest paths *to* a sink.
 *
 *    *   COMBINATION PHASE:
 *        We perform a single, fast loop `O(M)` through all edges `(u, v)`. For each
 *        edge, we can now look up the required path costs in O(1) from our
 *        pre-calculated arrays:
 *
 *          `total_cost = dist_from_s[u] + cost(u, v) + dist_to_t[v]`
 *
 *        We then check this `total_cost` against the budget `p`.
 *
 * By "investing" in two O(E log V) Dijkstra runs upfront, we reduce the main
 * part of the work to a simple O(M) loop. This pre-calculation strategy is the
 * key to transforming an exponential or high-polynomial problem into an
 * efficient, solvable one.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/w_graph.cpp"
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
#include <sstream>
#include <cmath>




namespace wg = algorithms::onlinejudge::graph::tools::wg;
namespace dijkstra = algorithms::onlinejudge::graph::tools::dijkstra;

struct Edge
{
    int from;
    int to;
    int w;
};


namespace algorithms::onlinejudge::graph::highest_paid_toll
{
    /** https://onlinejudge.org/external/120/12047.pdf */
    int t_cases, V, E, source, sink, p;
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
          while_read(V, E, source, sink, p);
          --source; --sink;
          wg::WGraph<> source_graph(V);
          wg::WGraph<> sink_graph(V);
          std::vector<Edge> edges;
          for(int e = 0; e < E; ++e) {
            int u, v, toll;
            while_read(u, v, toll);
            --u; --v;
            wg::pair(source_graph, u, v, toll, false);
            wg::pair(sink_graph, v, u, toll, false);
            edges.emplace_back(u, v, toll);
          }

          // from source
          wg::WNode<> start = wg::mkWNode(source, 0);
          dijkstra::Dijkstra<> dijkstra_s(V, start);
          dijkstra_s.mappend = [](int w, int a) { return w + a; };
          dijkstra::dijkstra(source_graph, dijkstra_s);

          tools::vi source_dist = dijkstra_s.dist; // pre-calculation step, kind of a fast look-up table

          // from sink
          start = wg::mkWNode(sink, 0);
          dijkstra_s = dijkstra::Dijkstra<>(V, start);
          dijkstra_s.mappend = [](int w, int a) { return w + a; };
          dijkstra::dijkstra(sink_graph, dijkstra_s);

          tools::vi sink_dist = dijkstra_s.dist; // pre-calculation step, kind of a fast look-up table

          int max_toll = -1;
          for(auto& e : edges) {
            int source_toll = source_dist[e.from];
            int sink_toll = sink_dist[e.to];
            // Make sure the paths from both ends are reachable
            if(source_toll != inf<int> && 
               sink_toll != inf<int>) {
              int total_toll = source_toll + e.w + sink_toll;
              if(total_toll <= p) {
                max_toll = std::max(max_toll, e.w);
              }
            }
          }
          std::cout << max_toll << std::endl;
        }
    }
}