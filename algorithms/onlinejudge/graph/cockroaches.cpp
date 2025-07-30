 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10805 Cockroach Escape Networks, rt: s
 ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: UVa 10805 - Cockroach Escape Networks
 * =====================================================================================
 *
 * This problem asks for the "best" location for an event, where "best" is defined
 * as the location that minimizes the longest escape time for any roach. This is a
 * classic MINIMAX problem on a graph, which can be solved by finding the "center"
 * of the graph. The goal is to minimize the maximum shortest-path distance from a
 * chosen starting node to any other node in its component.
 *
 * The strategy can be broken down into two main phases:
 *
 * --- Phase 1: Decompose the Graph into Connected Components ---
 *
 * The roach dens might form several disconnected networks (islands). An escape is only
 * possible within a single connected component. The first step is to identify these
 * separate components using a traversal algorithm like Breadth-First Search (BFS)
 * or a data structure like a Union-Find Disjoint Set (UFDS).
 *
 * --- Phase 2: Find the Center of Each Component ---
 *
 * For each independent connected component, we must find its "center" by solving
 * the minimax problem:
 *
 * 1.  THE "MAX" STEP (Find the Worst-Case for a single start node):
 *     - We iterate through every node `u` within the current component, treating each
 *       one as a potential "event" location (the starting den for the escape).
 *     - From each potential starting node `u`, we run a Breadth-First Search (BFS).
 *     - A BFS from `u` builds a shortest-path tree and calculates the shortest
 *       distance (in number of edges) from `u` to all other reachable nodes.
 *     - The **maximum distance** found during this BFS represents the "eccentricity"
 *       of node `u`—the time required for the roach from the most "far-flung" den
 *       to reach safety at `u`. This is the worst-case scenario for `u`.
 *
 * 2.  THE "MIN" STEP (Find the Best of the Worst-Cases):
 *     - After calculating the worst-case escape time for every single node in the
 *       component, we find the **minimum** among all these worst-case times.
 *     - This minimum value is the "radius" of this component—the best possible
 *       worst-case time we can achieve for this network of dens.
 *
 * --- Final Answer ---
 *
 * The final answer to the problem is the SUM of the radii (the "best of the worst-
 * case" times) calculated for each individual connected component.
 *
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/tree.cpp"
#include <bits/stdc++.h>


namespace tree = algorithms::onlinejudge::graph::tools::tree;


tree::vvi do_bfs(int start, int V, const tree::vvi& graph) {
  tree::vvi bfs_tree(V);
  std::queue<int> q;
  std::vector<bool> visited(V, false);
  q.push(start);
  visited[start] = true;

  while(!q.empty()) {
    int node = q.front(); q.pop();
    for(int neigh : graph[node]) {
      if(!visited[neigh]) {
        visited[neigh] = true;
        bfs_tree[node].push_back(neigh);
        bfs_tree[neigh].push_back(node);
    q.push(neigh);
      }
    }
  }
  return bfs_tree;
}


namespace algorithms::onlinejudge::graph::cockroaches
{
    /** https://onlinejudge.org/external/108/10805.pdf */
    int t_cases, V, E, t_case = 1;
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
          while_read(V, E);
          tree::vvi graph(V);
          for(int e = 0; e < E; ++e) {
            int u, v;
            while_read(u, v);
            graph[u].push_back(v);
            graph[v].push_back(u);
          }

          int min_response_time = std::numeric_limits<int>::max();
          for(int v = 0; v < V; ++v) {
            tree::vvi bfs_tree = do_bfs(v, V, graph);
            tree::Point point = tree::find_first_point(v, -1, bfs_tree);
            tree::Diameter diameter = tree::detect_diameter(point.idx, -1, bfs_tree);
            min_response_time = std::min(min_response_time, diameter.length); // cases
          }
          printf("Case #%d: \n%d\n\n", t_case++, min_response_time);
        }
    }
}