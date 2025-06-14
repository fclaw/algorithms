/*
───────────────────────────────────────────────────────────────
🧳 UVa 11953 Battleships, rt: s
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

enum World { IntactDeck, DamagedDeck, Water, NaN };



namespace algorithms::onlinejudge::graph::battleships
{
    /** https://onlinejudge.org/external/119/11953.pdf  */
    int t_case, S, V, c = 1;
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
        
        while_read(t_case);
        while(t_case--) {
          while_read(S);
          tools::GridGraph<World> graph = tools::init_grid_graph<World>(S, S);
          graph.cell_to_value = 
            [](char d) {
              switch(d) {
                case '.': return Water;
                case 'x': return IntactDeck;
                case '@': return DamagedDeck;
                default: return NaN;
              }
            };
          std::vector<std::vector<char>> grid(S, std::vector<char>(S));
          for(int i = 0; i < S; ++i)
            for(int j = 0; j < S; ++j)
              while_read(grid[i][j]);

          V = S * S;
          tools::grid_to_adj_list(graph, grid, tools::dirs_4, true);
          tools::Dfs<World> dfs_s = tools::init_dfs<World>(V);

          bool in_ship = false;
          int entry_node = tools::sentinel;
          int alive_ships = 0;
          int damaged_deck = 0;
          int num_decks = 0;
          auto is_ship = 
            [](const tools::Node<World>& node) -> bool { 
              return node.value == IntactDeck || 
                     node.value == DamagedDeck; 
            };
          dfs_s.on_discover =
            [&](tools::Node<World>& node) {  
              if(is_ship(node) && !in_ship) {
                in_ship = true;
                entry_node = node.node;
                if(node.value == DamagedDeck) {
                  damaged_deck = 1;
                }
            num_decks = 1;
              } else if(is_ship(node)) {
                  if(node.value == DamagedDeck) {
                    damaged_deck++;
                  }
                  num_decks++;  
                }
            };

          dfs_s.process_tree_edge = 
            [&is_ship]
            (const tools::Node<World>& u,
             const tools::Node<World>& v) {  
              return is_ship(u) && is_ship(v); 
            };

          dfs_s.on_leaving = 
            [&] 
            (tools::Node<World>& node) {
              if(node.node == entry_node) {
                if(damaged_deck < num_decks) alive_ships++;
                in_ship = false;
                damaged_deck = 0;
                num_decks = 0;
                entry_node = tools::sentinel;
              }
            };
           
          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == tools::Unvisited) {
              World world = graph.vertex_value.at(v);
              tools::Node<World> start = {v, world};
              tools::dfs<World>(graph.adj, dfs_s, start);
            }
            
          printf("Case %d: %d\n", c++, alive_ships);
        }
    }
}