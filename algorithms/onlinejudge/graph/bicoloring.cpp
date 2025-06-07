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
    int v, e;
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
        
        while(while_read(v, e) && v) {

          v_colour clr(v, None);
          bool is_bipartite = true;

          tools::Dfs dfs_s;
          dfs_s.is_finished = false;
          dfs_s.state = tools::v_state(v, tools::Unvisited);
          dfs_s.time = 1;
          dfs_s.entry_t = tools::vi(v);
          dfs_s.exit_t = tools::vi(v);
          dfs_s.parent = tools::vi(v, -1);
          dfs_s.on_discover = 
            [&clr, &dfs_s](int v) {
              int p = dfs_s.parent[v];
              if(p == -1) clr[v] = White;
              else clr[v] = set_op_colour(clr[p]);
            };
          dfs_s.process_back_edge = 
            [&clr, &dfs_s, &is_bipartite](int u, int v) {
              // Ignore the parent edge in undirected graph
              if(v != dfs_s.parent[u] && 
                 clr[u] == clr[v]) {
                dfs_s.is_finished = true;
                is_bipartite = false;
              }
          };

          tools::vvi adj_list(v);
          loop(e, [&adj_list](int _) {
            int u, v;
            while_read(u, v);
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
          });

          tools::dfs(adj_list, dfs_s, 0);
          printf("%s.\n", is_bipartite ? "BICOLORABLE" : "NOT BICOLORABLE");
        }
    }
}