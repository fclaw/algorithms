/*
───────────────────────────────────────────────────────────────
🧳 UVa 871 Counting Cells in a Blob, rt: s
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

enum Blob { Zero, One, NaN };



namespace algorithms::onlinejudge::graph::blobs
{
    /** https://onlinejudge.org/external/8/871.pdf */
    int t_cases, R, C, V;
     bool is_first = true;
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
        std::cin.ignore();
        std::cin.ignore();

        while(t_cases--) {       
          std::string line;
          std::vector<std::vector<char>> grid;
          while (std::getline(std::cin, line) && !line.empty()) {
            std::vector<char> row(line.begin(), line.end());
            grid.push_back(row);
          }

          R = grid.size();
          C = R > 0 ? grid[0].size() : 0;                
          V = R * C;

          tools::GridGraph<Blob> graph = tools::init_grid_graph<Blob>(R, C);
          graph.cell_to_value = 
            [](char d) {
              switch(d) {
                case '1': return One;
                case '0': return Zero;
                default: return NaN;
              }
            };
          tools::grid_to_adj_list(graph, grid, tools::dirs_8, true);
          tools::Dfs<Blob> dfs_s = tools::init_dfs<Blob>(V);

          int start_node = tools::sentinel;
          bool is_in_blob = false;
          int max_blob = 0;
          int curr_blob_size = 0;
          dfs_s.on_discover = 
            [&](tools::Node<Blob>& node) {
              if(node.value == One &&
                 !is_in_blob) {   
                is_in_blob = true;
                start_node = node.node;
                curr_blob_size = 1;
              } else if(node.value == One) curr_blob_size++;
            };

          dfs_s.process_tree_edge = 
            []
            (const tools::Node<Blob>& u,
             const tools::Node<Blob>& v) {  
              return u.value == One && u.value == v.value;
            };

          dfs_s.on_leaving = 
            [&] 
            (tools::Node<Blob>& node) {
              if(is_in_blob && 
                  node.node == 
                  start_node) {
                max_blob = std::max(max_blob, curr_blob_size);
                curr_blob_size = 0;
                is_in_blob = false;
                start_node = tools::sentinel;
              }
            };

          for(int v = 0; v < V; ++v)
            if(dfs_s.state[v] == tools::Unvisited) {
              Blob blob = graph.vertex_value.at(v);
              tools::Node<Blob> start = {v, blob};
              tools::dfs<Blob>(graph.adj, dfs_s, start);
            }
          
          if(!is_first)
            std::cout << std::endl;
          else is_first = false;
          std::cout << max_blob << std::endl;
        }
    }
}