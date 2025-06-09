/*
───────────────────────────────────────────────────────────────
🧳 UVa 796 Critical Links , rt: s
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
#include <set>



namespace tools = algorithms::onlinejudge::graph::tools;


namespace algorithms::onlinejudge::graph::critical_links
{
    /** https://onlinejudge.org/external/7/796.pdf */
    int V;
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
         
        while(while_read(V)) {
          tools::vv_def_node network(V);
          loop(V, [&] (int _) {
            int from, C;
            scanf("%d",&from);
            char c;
            scanf("%c%c%d%c",&c,&c,&C,&c);
            tools::v_def_node nodes(C, tools::def_node);
            loop(C, [&nodes](int i) { while_read(nodes[i].node); });
            if(!nodes.empty()) network[from] = nodes;
          });

          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
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

          std::set<std::pair<int, int>> res;
          for(int v = 0; v < V; ++v) {
            if(dfs_s.state[v] == tools::Unvisited) {
              tools::init_cut_points(V);
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::dfs<>(network, dfs_s, start_v);
              for(auto& e : tools::cut_edges) res.insert({e.from, e.to});
            }
          }

        
          printf("%d critical links\n", (int)res.size());
          for(auto& r : res) printf("%d - %d\n", r.first, r.second);
          std::cout << std::endl;
        }
    }
}