/*
───────────────────────────────────────────────────────────────
🧳 UVa 247 Calling Circles, rt: s
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


namespace algorithms::onlinejudge::graph::calling_circles
{
    /** https://onlinejudge.org/external/2/247.pdf  */
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

        bool is_first = true;  
        while(while_read(V, E) && V) {
          if(!is_first) std::cout << std::endl; 
          else is_first = false;
          std::unordered_map<std::string, int> name;
          std::unordered_map<int, std::string> indices;
          tools::vi edges(V, -1);
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node circle(V);

          int idx = 0;
          loop(E, [&](int _) {
            std::string from_n, to_n;
            while_read(from_n, to_n);
            auto it = name.find(from_n);
            int from, to;

            if(it == name.end()) { 
              from = idx; 
              name[from_n] = idx++;
              indices[from] = from_n;
            }
            else from = it->second;

            it = name.find(to_n);
            if(it == name.end()) { 
              to = idx; 
              name[to_n] = idx++;
              indices[to] = to_n;
            }
            else to = it->second;
            
            if(edges[from] != to) { 
              edges[from] = to; 
              circle[from].push_back({to, {}}); 
            }
          });

          tools::SCC<> scc(V);
          dfs_s.process_back_edge = 
           [&dfs_s, &scc](
             const tools::Node<>& u, 
             const tools::Node<>& v) {
               tools::handle_back_edge(dfs_s, scc, u, v);
           };
          dfs_s.process_cross_edge =
            [&dfs_s, &scc](
              const tools::Node<>& u, 
              const tools::Node<>& v) {
              tools::handle_cross_edge(dfs_s, scc, u, v);
            };
          dfs_s.on_discover = [&scc](tools::Node<>& u) { tools::handle_on_discover(scc, u); };
          dfs_s.on_leaving = [&dfs_s, &scc](tools::Node<>& u) { tools::handle_on_leaving(scc, dfs_s, u); };

          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == 
               tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              tools::dfs<>(circle, dfs_s, start_v);
            }
           
          printf("Calling circles for data set %d:\n", t_cases++);
          std::unordered_map<int, std::string> ans;
          for(int v = 0; v < V; ++v)
            ans[scc.components[v]] += indices[v] + ", ";

          for(auto a : ans) {
            a.second.pop_back();
            a.second.pop_back();
            std::cout << a.second << std::endl;
          }
        }
    }
}