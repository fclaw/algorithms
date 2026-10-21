/*
───────────────────────────────────────────────────────────────
🧳 UVa 558 Wormholes, https://onlinejudge.org/external/5/558.pdf, rt: 0s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"


struct Edge {
  int u, v, time;
};

namespace algorithms::onlinejudge::graph::wormholes
{
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
        
        int t_cases;
        stdin_read(t_cases);
        while(t_cases--) {
          int V, E;
          stdin_read(V, E);
          std::vector<Edge> edges(E);
          for(int e = 0; e < E; ++e) {
            stdin_read(edges[e].u, edges[e].v, edges[e].time);
          }
          
          vvi dp(V + 1, vi(V, Inf));
          dp[0][0] = 0;
          bool has_negative_cycle = false;
          for (int i = 1; i <= V; ++i) {
            // Step 1: Inherit distances from previous step (<= i - 1 edges)
            for (int v = 0; v < V; ++v) {
              dp[i][v] = dp[i - 1][v];
            }

            // Step 2: Try relaxing all directed edges (u -> v)
            bool any_update = false;
            for (const auto& edge : edges) {
              int u = edge.u;
              int v = edge.v;
              int time = edge.time;
              if (dp[i - 1][u] != Inf && 
                  dp[i - 1][u] + time < dp[i][v]) {
                dp[i][v] = dp[i - 1][u] + time;
                any_update = true;
              }
            }

            // If no distance changed, early exit!
            if (!any_update) {
              break;
            }

            // If distances STILL decrease on round V -> Negative Cycle exists!
            if(i == V && any_update) {
              has_negative_cycle = true;
            }
          }

          std::cout << (has_negative_cycle ? "possible" : "not possible") << "\n";
        }
    }
}