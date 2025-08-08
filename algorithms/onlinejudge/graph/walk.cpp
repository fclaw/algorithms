 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10596 Morning Walk, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v_seti = std::vector<std::set<int>>;


bool is_connected(int start, const v_seti& roads) {
 
    // --- Step 1: Count the total number of "active" vertices ---
    // An active vertex is one that is part of at least one bead (edge).
    int total_active_nodes = 0;
    for (int i = 0; i < (int)roads.size(); ++i) {
        if (!roads[i].empty()) {
            total_active_nodes++;
        }
    }

   uint64_t visited = 0;
   std::function<void(int)> do_dfs =
     [&](int node) {
      visited |= (1LL << node);      
       for(int neigh : roads[node]) {
         if(!(visited & (1LL << neigh)))
           do_dfs(neigh);
       }
     };
   do_dfs(start);
   return __builtin_popcountll(visited) == total_active_nodes;
}



namespace algorithms::onlinejudge::graph::walk
{
    /** https://onlinejudge.org/external/105/10596.pdf */
    int points_n, roads_n;
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
        
        while(while_read(points_n, roads_n)) {
          v_seti roads(points_n);
          vi in_degree(points_n);
          vi out_degree(points_n);
          for(int road_id = 0; road_id < roads_n; ++road_id) {
            int from, to;
            while_read(from, to);
            roads[from].insert(to);
            roads[to].insert(from);
            in_degree[to]++;
            out_degree[from]++;
          }

          bool is_even_degree = roads_n > 0;
          int start = -1;
          for(int point_id = 0; point_id < points_n; ++point_id) {
            int in = in_degree[point_id];
            int out = out_degree[point_id];
            int degree = in + out;
            if((degree % 2)) {
              is_even_degree = false;
              break;
            }
            if(start == -1 && degree > 0 && !(degree % 2))
              start = point_id;
          }

          bool is_circuit = start != -1 && is_connected(start, roads);
          bool is_eulerian = (is_even_degree && is_circuit);
          printf(is_eulerian ? "Possible\n" : "Not Possible\n");
        }
    }
}