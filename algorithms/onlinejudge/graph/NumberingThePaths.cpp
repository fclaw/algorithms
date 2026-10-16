/*
───────────────────────────────────────────────────────────────
🧳 UVa 10544 Numbering the Paths, https://onlinejudge.org/external/105/10544.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




// Global or per-testcase City ID Mapper
std::unordered_map<char, int> label_to_id;
std::unordered_map<int, char> id_to_label;
int unique_label_counter;

int get_id(char raw_label) {
  auto it = label_to_id.find(raw_label);
  if (it != label_to_id.end()) return it->second;
  label_to_id[raw_label] = unique_label_counter++;
  int id = label_to_id.at(raw_label);
  id_to_label[id] = raw_label;
  return id;
}


/**
 * Post-Order Memoized DFS for Path Counting on a Directed Acyclic Graph (DAG)
 * 
 * ============================================================================
 * PURPOSE:
 * ============================================================================
 * Computes ways[u] = the total number of distinct complete paths starting at 
 * node 'u' and ending at any dead-end (sink node with out-degree 0).
 *
 * This provides the "branch weights" needed for Lexicographical Path Ranking:
 * whenever our target path takes an edge (u -> v), any alternative edge 
 * (u -> smaller_sibling) allows us to skip exactly ways[smaller_sibling] paths!
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - Without memoization: Exponential O(2^V) due to diamond reconvergences in DAGs.
 * - With memoization (ways[u] != 0): Strictly O(V + E) linear time!
 * ============================================================================
 */
void dfs(int u, const vvi& graph, vi& ways) {

  // ------------------------------------------------------------------------
  // 1. MEMOIZATION CHECK (The 0.000s Line!)
  // ------------------------------------------------------------------------
  // In a DAG, multiple parents can point to the same node 'u' (diamond shape).
  // If ways[u] > 0, node 'u' has already been fully explored.
  // Returning immediately guarantees each node and edge is processed at most ONCE!
  if (ways[u] != 0) {
    return;
  }

  // ------------------------------------------------------------------------
  // 2. DEFAULT SINK BASE CASE
  // ------------------------------------------------------------------------
  // Tentatively assume 'u' is a dead end (out-degree 0).
  // A dead-end node represents exactly 1 complete path: stopping right at 'u'.
  ways[u] = 1;
  int count = 0;
  bool has_children = false;

  // ------------------------------------------------------------------------
  // 3. EXPLORE ALL OUTGOING ROADS (TRANSITION)
  // ------------------------------------------------------------------------
  for(int v : graph[u]) {
    has_children = true;
    // Step 3a: Ensure the child's path count is completely resolved
    dfs(v, graph, ways);
    // Step 3b: Accumulate all paths flowing through child 'v'
    // Every path continuing through 'v' extends a valid path from 'u'.
    count += ways[v];
  }

  // ------------------------------------------------------------------------
  // 4. FINALIZE NODE 'u'
  // ------------------------------------------------------------------------
  // If 'u' is not a dead end, its total paths equal the sum of its children's paths.
  // (If it has no children, ways[u] remains 1 as initialized above).
  if (has_children) {
    ways[u] = count;
  }
}

namespace algorithms::onlinejudge::graph::numbering_the_path
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

        int t_cases;
        stdin_read(t_cases);
        while(t_cases--) {
          unique_label_counter = 0;
          label_to_id.clear();
          id_to_label.clear();
          int V, E;
          stdin_read(V, E);
          vvi graph(V);
          vi in_degree(V, 0);
          std::unordered_map<char, std::string> children;
          std::unordered_set<std::string> edges;
          for(int e = 0; e < E; ++e) {
            std::string s;
            stdin_read(s);
            if(!edges.count(s)) {
              edges.insert(s);
              char from = s.front();
              char to = s.back();
              int from_id = get_id(from);
              int to_id = get_id(to);
              graph[from_id].push_back(to_id);
              in_degree[to_id]++;
              children[from].push_back(to);
            }
          }

          // sort children in alphabetical order
          for(auto& el : children) {
            std::sort(el.second.begin(), el.second.end());
          }

          vi sources;
          for(int v = 0; v < V; ++v) {
            if(!in_degree[v]) {
              sources.push_back(v);
            }
          }

          vi ways(V, 0);
          for(int s : sources) {
            dfs(s, graph, ways);
          }

          int Q;
          stdin_read(Q);
          while(Q--) {
            std::string path;
            stdin_read(path);
            int rank = 1;
            for(int i = 0; i < (int)path.size() - 1; ++i) {
              char u = path[i];
              char v = path[i + 1];
              std::string vs = children.at(u);
              for(char child : vs) {
                if(child == v) break;
                rank += ways[get_id(child)];
              }
            }
            printf("%s: %d\n", path.c_str(), rank);
          }
        }
    }
}
