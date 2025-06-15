/*
───────────────────────────────────────────────────────────────
🧳 UVa 11749 PoorTradeAdvisor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

#include <optional>
#include <iostream>
#include <sstream>
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


namespace algorithms::onlinejudge::graph::trade_advisor
{
    /** https://onlinejudge.org/external/117/11749.pdf  */
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
        
        while(while_read(V, E) && V && E) {
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node roads_network(V);
          tools::vvi roads_ppa(V, tools::vi(V, INT32_MIN));
          int max_ppa = INT32_MIN;
          loop(E, [&](int _) {
            int from, to, ppa;
            while_read(from, to, ppa);
            --from; --to;

            // Update the maximum PPA for the edge between from and to
            roads_ppa[from][to] = std::max(roads_ppa[from][to], ppa);
            roads_ppa[to][from] = std::max(roads_ppa[to][from], ppa);

            // Update the global maximum PPA
            max_ppa = std::max(max_ppa, ppa);

            roads_network[from].push_back(tools::mkDefNode(to));
            roads_network[to].push_back(tools::mkDefNode(from));
          });

          int curr_cities;
          dfs_s.on_discover = [&](const tools::Node<>& node) { curr_cities++; };
           
          dfs_s.process_tree_edge =
            [&](const tools::Node<>& u, 
                const tools::Node<>& v) -> bool {
              return !(dfs_s.parent[u.node] == v.node || roads_ppa[u.node][v.node] != max_ppa);
            };

          int max_cities = 0;
          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == 
               tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              curr_cities = 0;
              tools::dfs<>(roads_network, dfs_s, start_v);
              max_cities = std::max(max_cities, curr_cities);
            }
           
          std::cout << max_cities << std::endl;
        }
    }
}