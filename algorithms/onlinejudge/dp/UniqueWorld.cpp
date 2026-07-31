/*
────────────────────────────────────────────────────────────────────────────────
🧳 UVa 10448 - Unique World
   URL: https://onlinejudge.org/external/104/10448.pdf
   Verdict: Accepted | Runtime: ~0.010 0s
   Algorithmic Summary & Subtleties:

   1. The Tree Property:
      Because the graph is connected and has exactly one unique path between any 
      two nodes, it is mathematically a Tree. For any query from source 'A' to 
      destination 'B', we first find the unique simple path consisting of 'n' 
      edges with weights {C_1, C_2, ..., C_n}.

   2. The "Necessary Roads Only" Constraint:
      The problem states we can only use roads "necessary for the path." This 
      strictly forbids us from wandering off the unique simple path between A 
      and B. We cannot use any other adjacent edges in the tree.

   3. The Last Leg Constraint:
      We cannot perform round-trips on the last edge C_n. Once we cross the final 
      edge and land in our destination B, our journey stops. Thus, its traversal 
      count is exactly 1. Only the first n-1 edges on the path can be used for 
      round-trips.

   4. Mathematical Reduction to Coin Change:
      Let B be the base path cost (the sum of the n edges on the simple path).
      To get from A to B, we must cross each edge at least once (consuming B 
      energy and taking n steps). 
      
      Any additional cost must be spent as k_i >= 0 round-trips (back-and-forth) 
      on edge i (for 1 <= i <= n-1). Each round-trip adds 2 * C_i to the cost 
      and 2 to the steps.
      
      Total Cost Equation:
         B + 2 * Sum_{i=1}^{n-1} (k_i * C_i) = T  (where T is the target cost)
         Sum_{i=1}^{n-1} (k_i * C_i) = (T - B) / 2
      
      To minimize the total roads traveled (steps), we want to minimize:
         Total Steps = n + 2 * Sum_{i=1}^{n-1} k_i
      
      This reduces exactly to finding the minimum number of coins (round-trips) 
      to form the target sum (T - B) / 2 using the first n-1 edge weights.

   5. Crucial Feasibility and Edge Cases:
      - We must have T >= B (target cannot be less than the base path cost).
      - (T - B) must be even (since every round-trip adds an even cost of 2 * C_i).
      - If n = 1 (A and B are directly connected):
        The only edge is the last edge, which cannot be used for round-trips. 
        Thus, only T = B is possible (with exactly 1 step). If T > B, it is 
        impossible.

   6. Per-Query DP Execution:
      Because the allowed "coins" depend entirely on the unique path of each query, 
      we must run a local, unbounded DP of size (T - B) / 2 using the first 
      n-1 edge weights per query. 
      Since n <= 100 and (T - B)/2 <= 50000, each query runs in at most 
      O(n * (T - B)/2) ≈ 5 * 10^6 basic operations, which executes in milliseconds.
───────────────────────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;
using adj = std::vector<vii>;



void dfs(const adj& tree, int v, int dest, vi& curr_path, vi& path, bool& is_finished, vi& visited) {

   if(v == dest) {
     path = curr_path;
     is_finished = true;
     return;
   }

   for(const ii& node : tree[v]) {
     if(visited[node.first]) continue;
     visited[node.first] = 1;
     curr_path.push_back(node.second);
     dfs(tree, node.first, dest, curr_path, path, is_finished, visited);
     curr_path.pop_back();
     if(is_finished) {
       return;
     }
   }
}


namespace algorithms::onlinejudge::dp::unique_world
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
        std::cin >> t_cases;
        while(t_cases--) {
          int V, E;
          std::cin >> V >> E;
          adj tree(V);
          int from, to, c;
          vi costs;
          for(int e = 0; e < E; ++e) {
            std::cin >> from >> to >> c;
            --from; --to;
            tree[from].push_back({to, c});
            tree[to].push_back({from, c});
            costs.push_back(c);
          }
          
          int queries;
          std::cin >> queries;
          while(queries--) {
            int from, to, cost;
            std::cin >> from >> to >> cost;
            --from; --to;
            vi path, curr_path;
            bool is_finished = false;
            vi visited(V, 0);
            visited[from] = 1;
            dfs(tree, from, to, curr_path, path, is_finished, visited);

            int def_cost = std::accumulate(path.begin(), path.end(), 0);
            int diff = cost - def_cost;
            if(!is_finished ||
                (diff % 2) || 
               (from == to)) {
              printf("No\n");
            } else {
              vi dp((diff / 2) + 1, INT32_MAX);
              dp[0] = 0; // 0 round-trips needed to make 0 extra cost
              path.pop_back();
              for(int c : path) {
                for(int v = c; v <= (diff / 2); ++v) {
                  if(dp[v - c] != INT32_MAX) {
                    dp[v] = std::min(dp[v], 1 + dp[v - c]);
                  }
                }
              }
              if(dp[(diff / 2)] != INT32_MAX) {
                int roads = (path.size() + 1) + 2 * dp[(diff / 2)];
                printf("Yes %d\n", roads);
              } else {
                printf("No\n");
              }
            }
          }
          if(t_cases) std::cout << std::endl;
        }
    }
}