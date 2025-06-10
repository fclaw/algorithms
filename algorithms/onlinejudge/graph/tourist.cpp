/*
───────────────────────────────────────────────────────────────
🧳 UVa 10199 Tourist Guide, rt: s
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


namespace algorithms::onlinejudge::graph::tourist
{
    /** https://onlinejudge.org/external/101/10199.pdf */
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
        
        std::unordered_map<std::string, int> city_id;
        while(while_read(V) && V) {
          city_id.clear();
          tools::vv_def_node roads(V);
          loop(V, [&](int i) {
            std::string place;
            while_read(place);
            city_id[place] = i;
          });

          while_read(E);
          loop(E, [&roads, city_id](int i) {
            std::string from_l, to_l;
            while_read(from_l, to_l);
            int from = city_id.at(from_l);
            int to = city_id.at(to_l);
            roads[from].push_back({to, {}});
            roads[to].push_back({from, {}});
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
              tools::dfs<>(roads, dfs_s, start_v);
            }
          }

          std::set<std::string> locs;
          for(int u = 0; u < V; ++u) {
            tools::s_cut_node n = tools::cut_nodes[u];
              if(n.count(tools::Bridge)) {
                for(auto& p : city_id) 
                  if(p.second == u)
                    locs.insert(p.first);
                }
              }
          printf("City map #%d: %d camera(s) found\n", t_cases++, (int)locs.size());
          for(auto l : locs) printf("%s\n", l.c_str());
          std::cout << std::endl;
        }  
    }
}