/*
───────────────────────────────────────────────────────────────
🧳 UVa 11838 Come and Go, rt: s
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


namespace algorithms::onlinejudge::graph::come_and_go
{
    /** https://onlinejudge.org/external/118/11838.pdf */
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
          loop(E, [&roads_network] (int _) {
            int from, to, is_b;
            scanf("%d %d %d\n", &from, &to, &is_b);
            --from; --to;
            bool is_bidirectional = (bool)(--is_b);
            roads_network[from].push_back(tools::mkDefNode(to));
            if(is_bidirectional) roads_network[to].push_back(tools::mkDefNode(from));
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
              tools::dfs<>(roads_network, dfs_s, start_v);
            }

          std::cout << (scc.count == 1 ? 1 : 0) << std::endl;
        }
    }
}