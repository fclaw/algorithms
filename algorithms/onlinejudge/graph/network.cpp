/*
───────────────────────────────────────────────────────────────
🧳 UVa  315 Network, rt: s
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


namespace algorithms::onlinejudge::graph::network
{
    /** https://onlinejudge.org/external/3/315.pdf */
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
        
        while(while_read(V) && V) {

          tools::vv_def_node adj_list(V);
          std::string line;
          while(std::getline(std::cin, line) && 
                line != "0") {
           std::istringstream iss(line);
            int u;
            iss >> u; // This is the current vertex
            int v;
            --u;
            while (iss >> v) {
              --v;
              adj_list[u].push_back({v, {}});
              adj_list[v].push_back({u, {}}); // Because it's undirected
            }
          }

          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::init_cut_nodes(V);
          dfs_s.on_discover = [](tools::Node<>& u) { tools::init_ancestor(u.node); };
          dfs_s.process_tree_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) -> bool { 
              tools::incr_tree_out_degree(u.node); return true; 
            };
          dfs_s.process_back_edge = 
            [&dfs_s](const tools::Node<>& u, 
                     const tools::Node<>& v) { 
              tools::set_ancestor(u.node, v.node, dfs_s);
            };
          dfs_s.after_discover = [&dfs_s](tools::Node<>& u) { tools::detect_cut_node(u.node, dfs_s); };

          tools::Node<> start_v = {tools::start_vertex, {}};
          tools::dfs<>(adj_list, dfs_s, start_v);

          int count_ap = 0;
          for(auto n : tools::cut_nodes)
            if(n.count(tools::Parent) || 
               n.count(tools::Root) || 
               n.count(tools::Bridge))
              count_ap++;
          std::cout << count_ap << std::endl;
        }
    }
}