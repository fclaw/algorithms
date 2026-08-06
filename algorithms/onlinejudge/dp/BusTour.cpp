/*
───────────────────────────────────────────────────────────────
🧳 UVa 1281 Bus Tour, https://onlinejudge.org/external/12/1281.pdf, rt: s
───────────────────────────────────────────────────────────────
🗺️ Incremental TSP Builder using Bottom-Up Bitmask Dynamic Programming
   Formal Name: The Held-Karp Algorithm (1962)
   Complexity: Time O(2^N * N^2) | Space O(2^N * N)

   Algorithmic Summary & Design Principles:

   1. State Representation (dp[mask][v]):
      The DP table is a 2D array indexed by:
        - 'mask' (uint): Bitmask representing the exact subset of visited vertices.
                         The i-th bit is 1 if vertex i is visited, 0 otherwise.
        - 'v'    (int) : The specific vertex where the path currently terminates.
      
      dp[mask][v] stores the minimal path distance starting from the source 
      (e.g., HQ/Start), visiting every vertex in 'mask' exactly once, and 
      ending at vertex 'v'.

   2. Automatic Topological Order (Incremental Mask Building):
      Instead of using recursion or explicit level-by-level sorting, we iterate 
      'mask' numerically from 1 to (1 << N) - 1. 
      
      Mathematical Property:
         For any mask M, any proper sub-mask M' ⊂ M has a strictly smaller 
         numerical integer value (M' < M).
      
      Therefore, an ascending integer loop over 'mask' automatically processes 
      all smaller subsets before larger subsets, guaranteeing that subproblems 
      are fully calculated before they are needed.

   3. State Transition Logic:
      To extend a path to an unvisited vertex 'v' (where !(mask & (1 << v))):
         
         next_mask = mask | (1 << v)
         dp[next_mask][v] = min_{u in mask} ( dp[mask][u] + dist[u][v] )
      
      where 'u' is the previous endpoint in 'mask', and 'dist[u][v]' is the 
      shortest distance (from Floyd-Warshall or graph weights) between u and v.

   4. Performance & Memory Advantages:
      - Zero Heap Allocations: No vectors or maps are created or resized inside 
        the loops. All lookups use O(1) direct 2D array indexing.
      - High Cache Locality: Sequential iteration over contiguous memory arrays 
        maximizes CPU L1/L2 cache hits.
      - Alphabet/Graph Independence: Performance depends purely on N (vertices)
        and is independent of edge density.
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vvi = std::vector<vi>;


int V, E;

int t_case = 1;


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

          int total_cost = 0;
          int from, to, c;
          for(int e = 0; e < E; ++e) {
            std::cin >> from >> to >> c;
            apsp[from][to] = std::min(apsp[from][to], c);
            apsp[to][from] = std::min(apsp[to][from], c);
            total_cost += c;
          }

          // Handle the special case when V == 3 (HQ, ATTR, and one hotel)
          if(V == 3) {
            printf("Case %d: %d\n", t_case++, 2 * total_cost);
            continue;
          }

          runFloydWarshall(apsp);

          // generate all possible hotels of the size of h / 2
          int HQ = 0;
          int ATTR = V - 1;
          int masks = (1 << V) - 1; // All possible subsets of vertices
          vvi dp_hq(masks + 1, vi(V, INT32_MAX));
          dp_hq[1 << HQ][HQ] = 0; // Starting point at HQ
          for(int mask = 0; mask <= masks; ++mask) {
            if((mask & (1 << HQ))) {
              for(int v = 0; v < V; ++v) {
                if(mask & (1 << v)) {
                  // If vertex v is included in the mask, we can consider it as a hotel
                  // Here you can implement your logic to handle the hotel selection
                  int prev_mask = mask ^ (1 << v); // Remove v from the mask
                  vi hotels = restore_hotels(prev_mask);
                  for(int u : hotels) {
                    if(dp_hq[prev_mask][u] != INT32_MAX && 
                       apsp[u][v] != INT32_MAX) {
                      dp_hq[mask][v] = std::min(dp_hq[mask][v], dp_hq[prev_mask][u] + apsp[u][v]);
                    }
                  }
                }
              }
            }
          }

          vvi dp_attr(masks + 1, vi(V, INT32_MAX));
          dp_attr[1 << ATTR][ATTR] = 0; // Starting point at ATTR
          for(int mask = 0; mask <= masks; ++mask) {
            if((mask & (1 << ATTR))) {
              for(int v = 0; v < V; ++v) {
                if (mask & (1 << v)) {
                  int prev_mask = mask ^ (1 << v); // Remove v from the mask
                  vi hotels = restore_hotels(prev_mask);
                  for(int u : hotels) {
                    if(dp_attr[prev_mask][u] != INT32_MAX && 
                       apsp[u][v] != INT32_MAX) {
                      dp_attr[mask][v] = std::min(dp_attr[mask][v], dp_attr[prev_mask][u] + apsp[u][v]);
                    }
                  }
                }
              }
            }
          }


         int min_time = INT32_MAX;
         int HALF_SIZE = (V - 2) / 2;

         for (int mask = 0; mask <= masks; ++mask) {
           // 1. Ensure HQ is in mask, and the hotel count is EXACTLY h / 2
           int hotel_count = __builtin_popcount(mask ^ (1 << HQ));
          if ((mask & (1 << HQ)) && hotel_count == HALF_SIZE) {
                
            int s_mask = masks ^ mask; 
            if (!(s_mask & (1 << ATTR))) continue;
              
            int mask_to_attr = (mask ^ (1 << HQ)) | (1 << ATTR);
            int s_mask_to_hq = (s_mask ^ (1 << ATTR)) | (1 << HQ);

            int min_forward = INT32_MAX;
            int min_return = INT32_MAX;

            vi mask_hotels = restore_hotels(mask ^ (1 << HQ));
            vi s_mask_hotels = restore_hotels(s_mask ^ (1 << ATTR));

            // Forward Leg Minimum (Independent)
            for (int v : mask_hotels) {
              for (int u : s_mask_hotels) {
                if (dp_hq[mask][v] != INT32_MAX && 
                    dp_attr[s_mask][u] != INT32_MAX && 
                    apsp[v][u] != INT32_MAX) {
                  int forward_time = dp_hq[mask][v] + apsp[v][u] + dp_attr[s_mask][u];
                  min_forward = std::min(min_forward, forward_time);
                }
              }
            }

            // Return Leg Minimum (Independent)
            for (int x : mask_hotels) {
              for (int y : s_mask_hotels) {
                if (dp_attr[mask_to_attr][x] != INT32_MAX && 
                    dp_hq[s_mask_to_hq][y] != INT32_MAX && 
                    apsp[x][y] != INT32_MAX) {
                  int return_time = dp_attr[mask_to_attr][x] + apsp[x][y] + dp_hq[s_mask_to_hq][y];
                  min_return = std::min(min_return, return_time);
                }
              }
            }

            if (min_forward != INT32_MAX && 
                min_return != INT32_MAX) {
              min_time = std::min(min_time, min_forward + min_return);
            }
          }
        }
        printf("Case %d: %d\n", t_case++, min_time);
      }
    }
}