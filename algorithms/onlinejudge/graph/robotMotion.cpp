/*
───────────────────────────────────────────────────────────────
🧳 UVa 10116 Robot Motion, rt: s
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

enum D { N, S, E, W, NaN};


namespace algorithms::onlinejudge::graph::robot_motion
{
    /** https://onlinejudge.org/external/101/10116.pdf */
    int R, C, P, V;
    std::pair<int, int> node_to_rc(int node, int C) {
      return {node / C, node % C}; // (row, column)
    }
    std::pair<int, int> move_in_direction(int r, int c, D dir) {
        switch (dir) {
            case N:   return {r - 1, c};
            case S:   return {r + 1, c};
            case E:   return {r, c + 1};
            case W:   return {r, c - 1};
            default:  return {r, c}; // NaN or invalid direction
        }
    }
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
        
        while(while_read(R, C, P) && R && C && P) {
          tools::GridGraph<D> graph = tools::init_grid_graph<D>(R, C);
          graph.cell_to_value = 
            [](char d) {
              switch(d) {
                case 'N': return N;
                case 'S': return S;
                case 'E': return E;
                case 'W': return W;
                default: return NaN;
              }
            };
          
          std::vector<std::vector<char>> grid(R, std::vector<char>(C));  
          for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j)
              while_read(grid[i][j]);
                          
          V = R * C;

          tools::grid_to_adj_list(graph, grid, tools::dirs_4, true);
          tools::vi steps(V, 0);
          steps[P - 1] = 1;
          tools::Dfs<D> dfs_s = tools::init_dfs<D>(V);
          
          int last_node = tools::sentinel;
          int cycle_length = 0;

          dfs_s.process_tree_edge = 
            [&last_node, &dfs_s, grid, &steps]
            (const tools::Node<D>& u,
             const tools::Node<D>& v) {  
              auto [r, c] = node_to_rc(u.node, C);
              auto [nr, nc] = move_in_direction(r, c, u.value);
              auto [tr, tc] = node_to_rc(v.node, C);
              if(nr == tr && nc == tc)
                steps[v.node] = steps[u.node] + 1;
              return nr == tr && nc == tc;
            };

          dfs_s.process_back_edge = 
            [&last_node, &cycle_length, &dfs_s, &steps]
            (const tools::Node<D>& u, 
             const tools::Node<D>& v) {
              auto [r, c] = node_to_rc(u.node, C);
              auto [nr, nc] = move_in_direction(r, c, u.value);
              auto [tr, tc] = node_to_rc(v.node, C);
              if(nr == tr && nc == tc) { 
                cycle_length = steps[u.node] - steps[v.node] + 1;
                last_node = v.node;
                dfs_s.is_finished = true;
              }
            };

          dfs_s.on_leaving = [&last_node](tools::Node<D>& n) {
            if(last_node == tools::sentinel)
               last_node = n.node;
          };

          D d = graph.vertex_value.at(P - 1);
          tools::Node<D> start = {P - 1, d};
          tools::dfs<D>(graph.adj, dfs_s, start);

          if(cycle_length > 0) printf("%d step(s) before a loop of %d step(s)\n", steps[last_node] - 1, cycle_length);
          else printf("%d step(s) to exit\n", steps[last_node]);
        }
    }
}