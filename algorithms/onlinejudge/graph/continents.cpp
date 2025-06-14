/*
───────────────────────────────────────────────────────────────
🧳 UVa 11094 Continents, rt: s
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
#include <set>



namespace tools = algorithms::onlinejudge::graph::tools;

enum World { Land, Water, NaN };

namespace algorithms::onlinejudge::graph::continents
{
    /** https://onlinejudge.org/external/110/11094.pdf */
    int R, C, V, KR, KC;
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
        
        while(while_read(R, C)) {
          std::vector<std::vector<char>> grid(R, std::vector<char>(C));
          for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j)
              while_read(grid[i][j]);
          
          while_read(KR, KC);
          char land_mark = grid[KR][KC];

          tools::GridGraph<World> graph = tools::init_grid_graph<World>(R, C);
          graph.cell_to_value = 
            [land_mark](char d) {
              if(d == land_mark) return Land;
              else return  Water;
            };
          V = R * C;  
          tools::grid_to_adj_list(graph, grid, tools::dirs_4, true, true);
          tools::Dfs<World> dfs_s = tools::init_dfs<World>(V);

          std::set<int> kings_continent;
          int kv = KR * C + KC;
          World world = graph.vertex_value.at(kv);
          tools::Node<World> start = {kv, world};

          dfs_s.on_discover = 
            [&](tools::Node<World>& node) 
            { kings_continent.insert(node.node); };

          dfs_s.process_tree_edge =
            []
            (const tools::Node<World>& u,
             const tools::Node<World>& v) {
              return u.value == v.value;  
            };

          tools::dfs<World>(graph.adj, dfs_s, start);
          
          int max_continent = 0;
          int curr_max = 0;
          int start_node = tools::sentinel;
          dfs_s.on_discover = 
            [&](tools::Node<World>& node) {
              if(start_node == tools::sentinel)
                start_node = node.node;
              curr_max++;
            };

          dfs_s.on_leaving =
            [&](tools::Node<World>& node) {
              if(node.node == start_node) {
                max_continent = std::max(max_continent, curr_max);
                curr_max = 0;
                start_node = tools::sentinel;
              }              
            };

          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == tools::Unvisited) {
              int r = v / C;
              int c = v % C;
              if(grid[r][c] == land_mark && 
                 !kings_continent.count(v)) {
                World world = graph.vertex_value.at(v);
                tools::Node<World> start = {v, world};
                tools::dfs<World>(graph.adj, dfs_s, start);
              }
            }
          
          std::cout << max_continent << std::endl;
        }  
    }
}