/*
───────────────────────────────────────────────────────────────
🧳 UVa 610 StreetDirections, rt: s
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


namespace algorithms::onlinejudge::graph::streets
{
    /** https://onlinejudge.org/external/6/610.pdf */
    int V, E, t_cases = 1;
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
        
        while(while_read(V, E) && V && E) {
          tools::vv_def_node g(V);
          int from, to;
          std::vector<tools::Edge> streets;
          loop(E, [&](int _) {
            while_read(from, to);
            --from; --to;
            g[from].push_back({to, {}});
            g[to].push_back({from, {}});
            streets.push_back({from, to});
          });
        
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::init_cut_points(V);
          dfs_s.on_discover = 
            [](tools::Node<>& u) 
            { tools::init_ancestor(u.node); };
          dfs_s.process_tree_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) -> bool { 
              tools::incr_tree_out_degree(u.node); 
              return true; 
            };
          dfs_s.process_back_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) { 
              tools::set_ancestor(u.node, v.node, dfs_s);
            };
          dfs_s.on_exit = 
             [&dfs_s](tools::Node<>& u) 
             { tools::detect_cut_points(u.node, dfs_s); };

          tools::Node<> start_v = {tools::start_vertex, {}};
          tools::dfs<>(g, dfs_s, start_v);


          std::cout << t_cases++ << std::endl << std::endl;
          for(const auto& s : streets) {
            printf("%d %d\n", s.from + 1, s.to + 1);
            if(tools::cut_edges.count(s))
              printf("%d %d\n", s.to + 1, s.from + 1);
          }
          std::cout << "#" << std::endl;
        }  
    }
}