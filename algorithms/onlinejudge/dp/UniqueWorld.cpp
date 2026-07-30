/*
────────────────────────────────────────────────────────────────────────────────
🧳 UVa 10448 - Unique World
   URL: https://onlinejudge.org/external/104/10448.pdf
   Verdict: Accepted | Runtime: ~0.010 0s
────────────────────────────────────────────────────────────────────────────────
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