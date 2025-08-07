 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10054 The Necklace, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/eulerian.cpp"
#include <bits/stdc++.h>



namespace eulerian = algorithms::onlinejudge::graph::tools::eulerian;


constexpr int MAX_COLOUR = 50;

struct Bead
{
    int left_clr;
    int right_clr;
};

using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v_bead = std::vector<Bead>;


bool is_connected(int start, const vvi& colours) {
    
    // --- Step 1: Count the total number of "active" vertices ---
    // An active vertex is one that is part of at least one bead (edge).
    int total_active_nodes = 0;
    for (int i = 0; i < MAX_COLOUR; ++i) {
        if (!colours[i].empty()) {
            total_active_nodes++;
        }
    }
    
    // If there are 0 or 1 active nodes, the graph is trivially connected.
    if (total_active_nodes <= 1) {
        return true;
    }
  
   uint64_t visited = 0;
   std::function<void(int)> do_dfs =
     [&](int node) {
      visited |= (1LL << node);      
       for(int neigh : colours[node]) {
         if(!(visited & (1LL << neigh)))
           do_dfs(neigh);
       }
     };
   do_dfs(start);
   return __builtin_popcountll(visited) == total_active_nodes;
}


namespace algorithms::onlinejudge::graph::necklace
{
    /** https://onlinejudge.org/external/100/10054.pdf */
    int t_cases, t_case = 1, beads_n;
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
          while_read(beads_n);
          v_bead beads;
          for(int bead_id = 0; bead_id < beads_n; ++bead_id) {
            Bead bead;
            while_read(bead.left_clr);
            while_read(bead.right_clr);
            bead.left_clr--;
            bead.right_clr--;
            beads.push_back(bead);
          }

          vvi colours(MAX_COLOUR);
          vi degree(MAX_COLOUR);
          for(int bead_id = 0; bead_id < beads_n; ++bead_id) {
            int left_clr = beads[bead_id].left_clr;
            int right_clr = beads[bead_id].right_clr;
            degree[left_clr]++;
            degree[right_clr]++;
            colours[left_clr].push_back(right_clr);
            colours[right_clr].push_back(left_clr);
          }
          
          bool is_even_degree = true;
          int start = -1;
          for(int clr = 0; clr < MAX_COLOUR; ++clr) {
            if((degree[clr] % 2)) {
              is_even_degree = false;
              break;
            }
            if(start == -1 &&
               degree[clr] > 0 && 
               !(degree[clr] % 2)) 
              start = clr;
          }

          bool is_necklace = is_even_degree;
          is_necklace &= (start != -1 && is_connected(start, colours));

          if(is_necklace) {
            vi path = eulerian::hierholzer_u(start, colours);
            std::string path_s;
            for(int i = 1; i < (int)path.size(); ++i) {
              int left_clr = path[i - 1] + 1;
              int right_clr = path[i] + 1;
              path_s += std::to_string(left_clr) + " " + std::to_string(right_clr) + "\n";
            }
            printf("Case #%d\n%s", t_case++, path_s.c_str());
          } else {
            printf("Case #%d\nsome beads may be lost\n", t_case++);
          }
          if(t_cases) printf("\n");
        }
    }
}