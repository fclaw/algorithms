/*
───────────────────────────────────────────────────────────────
🧳 UVa 11396 Claw Decomposition, rt: s
───────────────────────────────────────────────────────────────
  Claw Decomposition Insight – UVa 11396

  A claw is a star graph with 4 nodes: one central node (the "black" vertex)
  connected to three leaf nodes (the "white" vertices).

  Problem constraint:
    - Each vertex in the graph has degree exactly 3.

  Mathematical Conditions for a valid claw decomposition:

    1. The graph must be **bipartite**:
       This allows us to colour the graph using two colours (say, black and white)
       such that no adjacent nodes share the same colour.

    2. The number of nodes must be divisible by 4:
       Since each claw involves 4 nodes, total vertices (V) must satisfy V % 4 == 0.

    3. Colour Count Ratio:
       In a valid decomposition:
         - Every claw has 1 black (center) and 3 white (leaves).
         - Let B = number of black nodes
         - Let W = number of white nodes
         - Let V = total number of nodes (B + W)
       Then:
         B * 4 = V      (1 black per claw → total claws = B)
         W * 4 = 3 * V  (3 whites per claw → total claws = W / 3)

    These two imply:
      → B = V / 4
      → W = 3V / 4

  If all three conditions are met, the graph can be decomposed into claws.
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


enum Claw { NotAssigned, Root, Subject};
typedef std::unordered_map<int, Claw> mi_claw;


Claw set_claw(Claw c) { return c == NotAssigned || c == Subject ? Root : Subject; }

namespace algorithms::onlinejudge::graph::claw
{
    /** https://onlinejudge.org/external/113/11396.pdf */
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

          tools::vv_def_node g(V);
          int u, v;
          while(while_read(u, v) && u && v) {
            --u; --v;
            g[u].push_back({v, {}});
            g[v].push_back({u, {}});
          };

          bool is_claw_decomposed = true;
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);

          for(int v = 0; v < V; ++v) {
            if(dfs_s.state[v] == 
               tools::Unvisited && 
               is_claw_decomposed) {

              mi_claw nodes;
              dfs_s.on_discover =
                [&](tools::Node<>& v) {
                  int p = dfs_s.parent[v.node];
                  if(p == -1) nodes[v.node] = Root;
                  else nodes[v.node] = set_claw(nodes[p]);
                };
              dfs_s.process_back_edge =
                [&nodes, &dfs_s, &is_claw_decomposed]
                (const tools::Node<>& u, 
                 const tools::Node<>& v) {
                  if(v.node != dfs_s.parent[u.node] &&
                     nodes[u.node] == 
                     nodes[v.node]) {
                    dfs_s.is_finished = true;
                    is_claw_decomposed = false;
                  }
                };
               tools::Node<> start_v = {v, {}};
               tools::dfs<>(g, dfs_s, start_v);
            }
          }

          std::cout << (is_claw_decomposed ? "YES" : "NO") << std::endl;
        }
    }
}