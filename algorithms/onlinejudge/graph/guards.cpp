/*
───────────────────────────────────────────────────────────────
🧳 UVa 11080 Placet he Guards, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>



namespace tools = algorithms::onlinejudge::graph::tools;


enum Junction { NotAssigned, Guarded, Free};
typedef std::unordered_map<int, Junction> mi_junction;


Junction set_guard(Junction j) { return j == NotAssigned || j == Free ? Guarded : Free; }

namespace algorithms::onlinejudge::graph::guards
{
    /** https://onlinejudge.org/external/1/118.pdf */
    int V, E, t_cases;
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

          while_read(V, E);
          tools::vv_def_node g(V);
          loop(E, [&g](int _) {
            int u, v;
            while_read(u, v);
            g[u].push_back({v, {}});
            g[v].push_back({u, {}});
          });

          bool is_row_free = true;
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);

          int min_guards = 0;
          for(int v = 0; v < V; ++v) {
            if(dfs_s.state[v] == 
               tools::Unvisited && 
               is_row_free) {

              mi_junction junctions;
              int cnt_guarded = 0;
              int cnt_free = 0;
              dfs_s.on_discover =
                [&](tools::Node<>& v) {
                  int p = dfs_s.parent[v.node];
                  if(p == -1) { 
                    junctions[v.node] = Guarded; 
                    ++cnt_guarded; 
                  }
                  else {
                    junctions[v.node] = set_guard(junctions[p]);
                    if(junctions[p] == Guarded) 
                      ++cnt_free;
                    else ++cnt_guarded;
                  }
                };
              dfs_s.process_back_edge =
                [&junctions, &dfs_s, &is_row_free]
                (const tools::Node<>& u, 
                 const tools::Node<>& v) {
                  if(v.node != dfs_s.parent[u.node] &&
                     junctions[u.node] == 
                     junctions[v.node]) {
                    dfs_s.is_finished = true;
                    is_row_free = false;
                  }
                };
               tools::Node<> start_v = {v, {}};
               tools::dfs<>(g, dfs_s, start_v);
               if(junctions.size() == 1) ++min_guards;
               else min_guards += std::min(cnt_guarded, cnt_free);
            }
          }

          std::cout << (is_row_free ? min_guards : -1) << std::endl;
        }
    }
}