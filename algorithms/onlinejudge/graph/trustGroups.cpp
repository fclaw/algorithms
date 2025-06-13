/*
───────────────────────────────────────────────────────────────
🧳 UVa  11504 Dominos, rt: 0.190s
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


namespace algorithms::onlinejudge::graph::trust_groups
{
    /** https://onlinejudge.org/external/117/11709.pdf  */
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
          std::cin.ignore(); // Ignore leftover '\n' from previous input line
          std::unordered_map<std::string, int> name_to_node;
          loop(V, [&name_to_node] (int node) {
            std::string name;
            std::getline(std::cin, name);
            name_to_node[name] = node;
          });

          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node people(V);
          loop(E, [&people, name_to_node] (int _) {
            std::string from_n, to_n;
            std::getline(std::cin, from_n);
            std::getline(std::cin, to_n);
            if(!from_n.empty() && !to_n.empty()) {
              int from = name_to_node.at(from_n);
              int to = name_to_node.at(to_n);
              people[from].push_back(tools::mkDefNode(to));
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
          dfs_s.on_discover = 
            [&scc](tools::Node<>& u) 
            { tools::handle_on_discover(scc, u); };
          dfs_s.on_leaving = 
            [&dfs_s, &scc](tools::Node<>& u) 
            { tools::handle_on_leaving(scc, dfs_s, u); };

          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == 
               tools::Unvisited) {
              tools::Node<> start_v = tools::def_node;
              start_v.node = v;
              tools::start_vertex = v;
              tools::dfs<>(people, dfs_s, start_v);
            }

          std::cout << scc.count << std::endl;
        }
    }
}