/*
───────────────────────────────────────────────────────────────
🧳 UVa 10987 AntiFloyd, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int inf = 1e5;

struct Cable
{
    int comp1;
    int comp2;
    int latency;
    bool operator < (const Cable& other) const  { return comp1 < other.comp1 || (comp1 == other.comp1 && comp2 < other.comp2); }
};


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>; // Adjacency list with weights
using v_cable = std::vector<Cable>;



vi dijkstra_with_ignored_edge(
  int start_node,
  int n,
  const vvii& adj,
  const ii& ignored_edge) {
  
  vi dist(n, inf);
  dist[start_node] = 0;

  // Min-priority queue: {distance, vertex}
  std::priority_queue<ii, vii, std::greater<ii>> pq;
  pq.push({0, start_node});

  while(!pq.empty()) {
    auto state = pq.top();
    int d = state.first;
    int u = state.second;
    pq.pop();

    if(d > dist[u]) {
      continue; // Stale entry
    }

    for(const auto& edge : adj[u]) {
      int v = edge.first;
      int weight = edge.second;

      // --- THE KEY LOGIC ---
      // Check if the current edge u->v is the one we should ignore.
      if((u == ignored_edge.first && 
          v == ignored_edge.second) ||
         (u == ignored_edge.second && 
          v == ignored_edge.first)) {
        continue; // Skip this edge
      }
            
      if(dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

enum TryCable { Cable, Route, IsAmbiguous };


TryCable try_cable(int i, int j, int original_latency, const vvi& latencies, const vvii& network) {
  int n = latencies.size();

  // 1. Run Dijkstra from i, but tell it to IGNORE the direct edge (i, j).
  //    This will find the shortest path from i to all other nodes using
  //    any path that doesn't immediately use the (i, j) cable.
  vi dists_from_i = dijkstra_with_ignored_edge(i, n, network, {i, j});

  // 2. Get the new shortest path cost from i to j.
  int alternative_path_cost = dists_from_i[j];

  // 3. Make the final decision.
  // The cable is necessary if the alternative path is strictly worse (longer)
  // than the original given latency. If they are equal, the original path
  // could have been explained by this alternative, so the cable is redundant.
  if(alternative_path_cost < original_latency) {
    return IsAmbiguous;
  } else if(alternative_path_cost == original_latency) {
    return Route;
  }
  else return Cable;
}


namespace algorithms::onlinejudge::graph::antifloyd
{
    /** https://onlinejudge.org/external/109/10987.pdf */
    int t_cases, comps_n, t_case = 1;
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
          while_read(comps_n);
          vvi latencies(comps_n, vi(comps_n, inf));
          for(int i = 1; i < comps_n; ++i) {
            for(int j = 0; j < i; ++j) {
              while_read(latencies[i][j]);
              latencies[j][i] = latencies[i][j];
            }
          }

          vvii network(comps_n);
          for(int u = 0; u < comps_n; ++u) {
            for(int v = u + 1; v < comps_n; ++v) {
              network[u].push_back({v, latencies[u][v]});
              network[v].push_back({u, latencies[u][v]});
            }
          } 
          
          v_cable cables;
          bool is_ambiguous = false;
          for(int comp_i = 0; comp_i < comps_n; ++comp_i) {
            for(int comp_j = 0; comp_j < comp_i; ++comp_j) {
              if(auto latency = latencies[comp_i][comp_j];
                 comp_i != comp_j && latency != inf) {
                TryCable try_res = try_cable(comp_i, comp_j, latency, latencies, network);
                if(try_res == Cable) {
                  int comp1 = std::min(comp_i, comp_j);
                  int comp2 = std::max(comp_i, comp_j);
                  cables.push_back({comp1, comp2, latency});
                } else if(try_res == IsAmbiguous) {
                  is_ambiguous = true;
                  goto is_ambiguous_res;
                }
              }
            }
          }

          if(!is_ambiguous) {
            printf("Case #%d:\n", t_case++);
            if(cables.empty()) {
              printf("Need better measurements.\n"); 
            } else {
              std::sort(cables.begin(), cables.end());
              printf("%d\n", (int)cables.size());
              for(const auto& cable : cables) {
                printf("%d %d %d\n", cable.comp1 + 1, cable.comp2 + 1, cable.latency);
              }
            } 
          } else { 
            is_ambiguous_res: printf("Case #%d:\nNeed better measurements.\n", t_case++);
          }
          std::cout << std::endl;
        }
    }
}