/*
───────────────────────────────────────────────────────────────
🧳 UVa 572 OilDeposits, rt: s
───────────────────────────────────────────────────────────────

  This solution models the grid as a graph where '@' (Oil) and '*' (Barren) 
  are converted into values in the enum Plot. It uses 8-directional adjacency 
  to ensure diagonal connections are considered.

  DFS traversal is customised with:
    - `on_discover`: Marks the start of a new oil pocket when an Oil cell is first seen.
    - `process_tree_edge`: Only allows DFS continuation if both connected nodes are Oil.
    - `on_leaving`: Recognises the completion of a connected Oil component rooted at `entry_node`, 
                    marking it in the `pockets` array.

  Finally, the number of unique oil deposits is computed by counting how many 
  entries in `pockets` were marked (i.e., equal to 1).

  Cleverness:
    - The `in_pocket` flag and `entry_node` make component marking minimal and efficient.
    - Custom `process_tree_edge` effectively prunes DFS to just Oil-connected regions.
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

enum Plot { Barren, Oil, NaN };



namespace algorithms::onlinejudge::graph::oil_deposits
{
    /** https://onlinejudge.org/external/5/572.pdf */
    int R, C, V;
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
        
        while(while_read(R, C) && R && C) {
          tools::GridGraph<Plot> graph = tools::init_grid_graph<Plot>(R, C);
          graph.cell_to_value = 
            [](char d) {
              switch(d) {
                case '*': return Barren;
                case '@': return Oil;
                default: return NaN;
              }
            };
          
          std::vector<std::vector<char>> grid(R, std::vector<char>(C));  
          for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j)
              while_read(grid[i][j]);
                          
          V = R * C;

          tools::grid_to_adj_list(graph, grid, tools::dirs_8, true);
          tools::Dfs<Plot> dfs_s = tools::init_dfs<Plot>(V);

          tools::vb pockets(V, false);
          bool in_pocket = false;
          int entry_node = tools::sentinel;
          dfs_s.on_discover = 
            [&](tools::Node<Plot>& node) { 
              if(node.value == Oil &&
                 !in_pocket) {   
                in_pocket = true;
                entry_node = node.node;
              }
            };

          dfs_s.process_tree_edge = 
            []
            (const tools::Node<Plot>& u,
             const tools::Node<Plot>& v) {  
              if(u.value == Barren) return false;
              if(u.value == Oil && v.value == Oil) return true;
              return false;
            };

          dfs_s.on_leaving = 
            [&pockets, &in_pocket, &entry_node] 
            (tools::Node<Plot>& node) {
              if(node.node == entry_node) {
                in_pocket = false;
                if(!pockets[node.node]) 
                  pockets[node.node] = true;
                entry_node = tools::sentinel;
              }
            };

          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == tools::Unvisited) {
              Plot plot = graph.vertex_value.at(v);
              tools::Node<Plot> start = {v, plot};
              tools::dfs<Plot>(graph.adj, dfs_s, start);
            }

          std::cout << std::count(pockets.begin(), pockets.end(), true) << std::endl;  
        }
    }
}