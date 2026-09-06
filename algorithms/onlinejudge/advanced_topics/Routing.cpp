/*
───────────────────────────────────────────────────────────────
🧳 UVa 1057 Routing, https://onlinejudge.org/external/10/1057.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int INF = (int)1e9; // Represents "infinity" for unreachable nodes
constexpr int MAX_NODES = 105; // Maximum number of nodes in the graph


int get_min_unique_nodes(const vvi& paths_to_dest, const vvi& paths_to_src) {
    int min_unique_count = INF;

    // 1. Pre-convert paths to bitsets (O(P * length)):
    std::vector<std::bitset<MAX_NODES>> masks_dest;
    for (const auto& p : paths_to_dest) {
        std::bitset<MAX_NODES> b;
        for (int node : p) b.set(node);
        masks_dest.push_back(b);
    }

    std::vector<std::bitset<MAX_NODES>> masks_src;
    for (const auto& p : paths_to_src) {
        std::bitset<MAX_NODES> b;
        for (int node : p) b.set(node);
        masks_src.push_back(b);
    }

    // 2. Test all pairs in 1 CPU cycle using bitwise OR (|):
    for (const auto& m1 : masks_dest) {
        for (const auto& m2 : masks_src) {
            int unique_count = (m1 | m2).count(); // Union size!
            min_unique_count = std::min(min_unique_count, unique_count);
        }
    }

    return min_unique_count;
}


/*
 * ============================================================================
 * 🧠 WHY THIS BACKTRACKING IS NEEDED: Shortest Path DAG Traversal
 * ============================================================================
 * 
 * 1. THE PROBLEM: Floyd-Warshall only gives NUMBERS, not PATHS
 * -----------------------------------------------------------
 * Standard Floyd-Warshall / Dijkstra only computes the SCALAR distance:
 *     apsp[1][2] = 3 (i.e. "the shortest path takes 3 hops")
 * It discards ties and cannot tell you the actual vertices visited along the route.
 * 
 * 2. WHY WE NEED ALL SHORTEST PATHS (UVa 1057 Context):
 * -----------------------------------------------------
 * In this problem, we must minimize the UNION of unique vertices: |P_forward ∪ P_return|.
 * There might be multiple alternative shortest paths of the exact same length:
 *     Option A: 1 -> 3 -> 2
 *     Option B: 1 -> 4 -> 2
 * If the return path uses node 3 (2 -> 3 -> 1), picking Option A results in 
 * 3 unique nodes, whereas picking Option B results in 4 unique nodes!
 * We MUST extract all candidate shortest paths to find the pair that maximizes 
 * node overlap!
 * 
 * 3. THE MATHEMATICAL BEAUTY: Guaranteed Zero Cycles (Strict DAG)
 * --------------------------------------------------------------
 * By enforcing the Bellman Optimality Invariant:
 *         apsp[u][v] == 1 + apsp[w][v]
 * 
 * We restrict exploration strictly to edges that move closer to the target. 
 * Because the remaining distance strictly decreases by 1 at every step 
 * (d -> d-1 -> d-2 ... -> 0):
 *   • It is MATHEMATICALLY IMPOSSIBLE to enter an infinite loop or cycle!
 *   • It never explores dead ends or sub-optimal branches.
 *   • Every path that reaches the base case is guaranteed to be of minimal length.
 * ============================================================================
 */
void shortest_path_from_source_to_dest(int u, int v, const vvi& graph, const vvi& apsp, vvi& all_paths, vi& current_path) {

  if(apsp[u][v] == 0) { // Base case: reached destination
    all_paths.push_back(current_path);
    return;
  }

  for(int w : graph[u]) { // Explore neighbors of u
    if(apsp[u][v] == 1 + apsp[w][v]) { // Check if w is on a shortest path to v
      current_path.push_back(w);
      shortest_path_from_source_to_dest(w, v, graph, apsp, all_paths, current_path);
      current_path.pop_back(); // Backtrack
    }
  }
}


std::string get_min_unique_nodes(const vvi& graph) {

  int N = graph.size();
  vvi apsp(N, vi(N, INF)); // Initialize with "infinity" and empty paths

  // Initialize distances and next nodes
  for(int u = 0; u < N; ++u) {
    for(int v = 0; v < N; ++v) {
      if(std::find(graph[u].begin(), graph[u].end(), v) != graph[u].end()) { // If there's an edge from u to v
        apsp[u][v] = 1; // Assuming unit edge weights
      }
    }
    apsp[u][u] = 0;
  }

  // Floyd-Warshall algorithm
  for(int k = 0; k < N; ++k) {
    for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
        apsp[i][j] = std::min(apsp[i][j], apsp[i][k] + apsp[k][j]);
      }
    }
  }
  
  int source = 0; // Node 1 in 1-based indexing
  int destination = 1; // Node 2 in 1-based indexing

  vvi all_paths_to_destination;
  for(int v : graph[source]) { // Explore neighbors of source
    vi current_path = {source, v}; // Start from source and include neighbor v
    shortest_path_from_source_to_dest(v, destination, graph, apsp, all_paths_to_destination, current_path);
  }

  vvi all_paths_to_source;
  for(int v : graph[destination]) { // Explore neighbors of destination
    vi current_path = {destination, v}; // Start from destination and include neighbor v
    shortest_path_from_source_to_dest(v, source, graph, apsp, all_paths_to_source, current_path);
  }

  if(all_paths_to_destination.empty() ||
     all_paths_to_source.empty()) {
    return "Impossible";
  }

  return "Minimum number of nodes = " + std::to_string(get_min_unique_nodes(all_paths_to_destination, all_paths_to_source));

}


namespace algorithms::onlinejudge::advanced_topics::routing
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

        int N, E, t_case = 0;
        while(std::cin >> N >> E && N) {

          vvi graph(N); // Initialize graph with empty vectors
          for(int e = 0; e < E; ++e) {
            int u, v;
            std::cin >> u >> v;
            --u; --v; // Convert to 0-based indexing
            graph[u].push_back(v); // directed edge from u to v with cost 1
          }
          printf("Network %d\n%s\n\n", ++t_case, get_min_unique_nodes(graph).c_str());
        }
    }
}