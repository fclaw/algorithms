/*
───────────────────────────────────────────────────────────────
🧳 UVa 1281 Bus Tour, https://onlinejudge.org/external/12/1281.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


int V, E;

int t_case = 1;

enum Point { HQ, ATTR };



void runFloydWarshall(vvi& dist) {
  // Run Floyd-Warshall in O(V^3) time
  for(int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for(int j = 0; j < V; ++j) {
        if(dist[i][k] != INT32_MAX && 
           dist[k][j] != INT32_MAX) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
}


// Extracts the 0-based vertex indices from a bitmask
vi restore_hotels(int mask) {
  vi hotels;
  while (mask) {
   // Find the index of the lowest set bit
   int idx = __builtin_ctz(mask);
   hotels.push_back(idx);     
   // Clear the lowest set bit
   mask &= (mask - 1);
  }
  return hotels;
}


int tsp(int u, int target, const vi& hotels, const vvi& dist, int visited, vvi& cache) {
   
  int S = (int)hotels.size();
  if(__builtin_popcount(visited) == S) {
    return (cache[u][visited] = (u == target ? 0 : INT32_MAX));
  }

  if(~cache[u][visited]) {
    return cache[u][visited];
  }

  int best = INT32_MAX;
  for(int i = 0; i < S; ++i) {
    int bit = (1 << i);
    int v = hotels[i];
    if(!(visited & bit)) {
      int next = tsp(v, target, hotels, dist, visited | bit, cache);
      if(next != INT32_MAX) {
        best = std::min(best, dist[u][v] + next);
      }
    }
  }
 
  return (cache[u][visited] = best);

}


namespace algorithms::onlinejudge::dp::bus_tour
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


        while(std::cin >> V >> E) {
          vvii graph(V);
          vvi apsp(V, vi(V));
         
          for(int i = 0; i < V; ++i) {
            for(int j = 0; j < V; ++j) {
              if (i == j) {
                apsp[i][j] = 0;
              } else {
                apsp[i][j] = INT32_MAX;
              }
            }
          }

          int from, to, c;
          for(int e = 0; e < E; ++e) {
            std::cin >> from >> to >> c;
            graph[from].push_back({to, c});
            graph[to].push_back({from, c});
            apsp[from][to] = apsp[to][from] = c;
          }

          runFloydWarshall(apsp);

          // generate all possible hotels of the size of h / 2
          int hq = 0;
          int attr = V - 1;
          int SIZE = (V - 2) / 2;
          
          // Mask containing 1s for all hotel vertices (excluding hq=0 and attraction=V-1)
          int all_hotels_mask = ((1 << V) - 1) ^ (1 << hq) ^ (1 << attr);
          vi first_half_masks;

          for(int set = 0; set < (1 << V); ++set) {
            // Ensure set is of size SIZE and contains ONLY hotel vertices
            if (__builtin_popcount(set) == SIZE && 
                (set & all_hotels_mask) == set) {
              first_half_masks.push_back(set);
            }
          }


          vvvi dp(2, vvi(all_hotels_mask, vi(V, INT32_MAX)));
          for(int mask : first_half_masks) {
            vi hotels = restore_hotels(mask | (1 << hq));
            int S = hotels.size();
            vvi cache(V, vi(1 << S, -1));
            for(int i = 1; i < (int)hotels.size(); ++i) {
              int dist = tsp(hq, hotels[i], hotels, apsp, 0 | (1 << 0), cache);
              dp[HQ][mask][hotels[i]] = dist;
            }
            
            cache = vvi(V, vi(1 << S, -1));
            hotels = restore_hotels(mask | (1 << attr));
            for(int i = 0; i < (int)hotels.size() - 1; ++i) {
              int dist = tsp(attr, hotels[i], hotels, apsp, 0 | (1 << ((int)hotels.size() - 1)), cache);
              dp[ATTR][mask][hotels[i]] = dist;
            }

            int s_mask = all_hotels_mask ^ mask;
            hotels = restore_hotels(s_mask | (1 << attr));
            S = hotels.size();
            cache = vvi(V, vi(1 << S, -1));
            for(int i = 0; i < (int)hotels.size() - 1; ++i) {
              int dist = tsp(attr, hotels[i], hotels, apsp, 0 | (1 << ((int)hotels.size() - 1)), cache);
              dp[ATTR][s_mask][hotels[i]] = dist;
            }

            cache = vvi(V, vi(1 << S, -1));
            hotels = restore_hotels(s_mask | (1 << hq));
            for(int i = 1; i < (int)hotels.size(); ++i) {
              int dist = tsp(hq, hotels[i], hotels, apsp, 0 | (1 << 0), cache);
              dp[HQ][s_mask][hotels[i]] = dist;
            }
          }
        

          int min_tour_time = INT32_MAX;
          for(int mask : first_half_masks) {
            int s_mask = all_hotels_mask ^ mask;
            for(int u : restore_hotels(mask)) {
              for(int v : restore_hotels(s_mask)) {
                int forward_leg = dp[HQ][mask][u] + apsp[u][v] + dp[ATTR][s_mask][v];
                int backward_leg = dp[ATTR][mask][u] + apsp[u][v] + dp[HQ][s_mask][v];
                min_tour_time = std::min(min_tour_time, forward_leg + backward_leg);
              }
            }
          }
          printf("Case %d: %d\n", t_case++, min_tour_time);
        }
    }
}