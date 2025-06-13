/*
───────────────────────────────────────────────────────────────
🧳 UVa 12783 Weak Links , rt: 0.440s
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


namespace algorithms::onlinejudge::graph::weak_links
{
    /** https://onlinejudge.org/external/127/12783.pdf  */
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
          tools::vv_def_node network(V);
          loop(E, [&network] (int _) {
            int from, to;
            while_read(from, to);
            network[from].push_back(tools::mkDefNode(to));
            network[to].push_back(tools::mkDefNode(from));
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
          dfs_s.on_leaving = 
             [&dfs_s](tools::Node<>& u) 
             { tools::detect_cut_points(u.node, dfs_s); };

          for(int v = 0; v < V; ++v) {
            if(dfs_s.state[v] == tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              tools::dfs<>(network, dfs_s, start_v);
            }
          }

          std::string ans;
          ans += std::to_string(tools::cut_edges.size()) + " ";
          for(tools::Edge e : tools::cut_edges)
            ans += std::to_string(e.from) + " " + std::to_string(e.to) + " ";
          ans.pop_back();
          std::cout << ans << std::endl;  
        }  
    }
}