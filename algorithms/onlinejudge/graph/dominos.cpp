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


namespace algorithms::onlinejudge::graph::dominos
{
    /** https://onlinejudge.org/external/115/11504.pdf */
    int t_cases, V, E;
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
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(V, E);
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node dominos(V);
          loop(E, [&] (int _) {
            int from, to;
            scanf("%d %d\n", &from, &to);
            --from; --to;
            dominos[from].push_back(tools::mkDefNode(to));
          });

          // // nodes with 1 or more outgoing edges;
          tools::vvi in_degree(V);
          for(int v = 0; v < V; ++v)
            for(tools::Node<>& u : dominos[v])
              in_degree[u.node].push_back(v);

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
              tools::dfs<>(dominos, dfs_s, start_v);
            }
          
          int num_scc = *std::max_element(scc.components.begin(), scc.components.end());
          std::vector<int> in_deg_scc(num_scc + 1, 0); // 1-based SCC IDs

          // Step: Count incoming edges between SCCs (Strongly Connected Components).
          // ------------------------------------------------------------
          // Each SCC is a "group of dominos" that can knock each other over internally.
          // If any one domino in an SCC is pushed, the whole component will fall.
          //
          // However, to knock over dominos in *another* SCC, there must be a directed edge
          // (i.e., a "cross edge") going from one component to another.
          //
          // In this loop, we iterate over each edge in the original graph.
          // For an edge v -> u:
          //   - If v and u are in different SCCs (i.e., scc[v] != scc[u]),
          //     it means u's component can be reached from v's component.
          //   - Hence, we increment the in-degree count of u's component.
          //
          // After processing all edges, the SCCs with in-degree == 0 are
          // the ones that cannot be reached by any other SCC —
          // these are the SCCs we must *manually push* to start the domino chain.
          for(int v = 0; v < V; ++v) {
            for(tools::Node<>& n : dominos[v]) {
              int u = n.node;
              int cu = scc.components[u];
              int cv = scc.components[v];
              if(cu != cv) in_deg_scc[cu]++;
            }
          }

          int min_dominos = 0;
          for (int i = 1; i <= num_scc; ++i) {
            if(in_deg_scc[i] == 0)
              min_dominos++; // This SCC has no incoming edge ⇒ needs a push
          }
          std::cout << min_dominos << std::endl;
        }
    }
}