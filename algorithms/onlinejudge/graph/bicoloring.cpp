/*
───────────────────────────────────────────────────────────────
🧳 UVa  10004 Bicoloring, rt: s
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

enum Colour { None, Black, White};
typedef std::vector<Colour> v_colour;

Colour set_op_colour(Colour cl) 
{
    if(cl == None) return None;
    else if(cl == Black) return White;
    else return Black;
}


namespace algorithms::onlinejudge::graph::bicoloring
{
    /** https://onlinejudge.org/external/100/10004.pdf */
    int V, E;
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
        
        while(while_read(V, E) && V) {

          v_colour clr(V, None);
          bool is_bipartite = true;

          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          dfs_s.on_discover = 
            [&clr, &dfs_s](tools::Node<>& v) {
              int p = dfs_s.parent[v.node];
              if(p == -1) clr[v.node] = White;
              else clr[v.node] = set_op_colour(clr[p]);
            };
          dfs_s.process_back_edge = 
            [&clr, &dfs_s, &is_bipartite]
            (const tools::Node<>& u, 
             const tools::Node<>& v) {
              // Ignore the parent edge in undirected graph
              if(v.node != dfs_s.parent[u.node] && 
                 clr[u.node] == clr[v.node]) {
                dfs_s.is_finished = true;
                is_bipartite = false;
              }
          };

          tools::vv_def_node adj_list(V);
          loop(E, [&adj_list](int _) {
            int u, v;
            while_read(u, v);
            adj_list[u].push_back({v, {}});
            adj_list[v].push_back({u, {}});
          });

          tools::Node<> start_v = {tools::start_vertex, {}};
          tools::dfs<>(adj_list, dfs_s, start_v);
          printf("%s.\n", is_bipartite ? "BICOLORABLE" : "NOT BICOLORABLE");
        }
    }
}