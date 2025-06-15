/*
───────────────────────────────────────────────────────────────
🧳 UVa 852 Deciding victory in Go, rt: s
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

enum Board { White, Black, Empty, NaN };
enum Region { Is_White, Is_Black, Contestend, NotAssigned };


namespace algorithms::onlinejudge::graph::go_game
{
    /** https://onlinejudge.org/external/8/852.pdf */
    int t_cases;
    const int B = 9, V = B * B;
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
          tools::GridGraph<Board> graph = 
            tools::init_grid_graph<Board>(B, B);
          graph.cell_to_value = 
            [](char d) {
              switch(d) {
                case 'X': return Black;
                case 'O': return White;
                case '.': return Empty;
                default: return NaN;
              }
            };
          tools::vvc grid(B, tools::vc(B));
          for(int i = 0; i < B; ++i)
            for(int j = 0; j < B; ++j)
              while_read(grid[i][j]);

          int black_points;
          int white_points;
          Region region;

          tools::grid_to_adj_list(graph, grid, tools::dirs_4, true);
          tools::Dfs<Board> dfs_s = tools::init_dfs<Board>(V);

          dfs_s.on_discover = 
            [&](tools::Node<Board>& node) {
              if(region == NotAssigned) {
                if(node.value == White)
                  region = Is_White;
                else if(node.value == Black)
                  region = Is_Black;
              }
              else {
                if((node.value == Black &&
                    region == Is_White) || 
                   (node.value == White && 
                    region == Is_Black)) {   
                  region = Contestend;
                }
              }
            };

          dfs_s.on_leaving =
            [&](tools::Node<Board>& node) {
              if(node.value == Empty) {
                if(region == Is_White) { 
                  white_points++;
                }
                else if(region == Is_Black)
                  black_points++;
              }
            };

          dfs_s.process_tree_edge =
            [](const tools::Node<Board>& u,
               const tools::Node<Board>& _) {
              return u.value == Empty;
            };

          dfs_s.process_cross_edge = 
            [&](const tools::Node<Board>& u,
               const tools::Node<Board>& v) {
              if(v.value == Black && 
                 region == NotAssigned) 
                region = Is_Black;
              else if(v.value == White && 
                      region == NotAssigned) 
                region = Is_White;
              return u.value == Empty;
            };

          int blacks = 0;
          int whites = 0;
          for(int v = 0; v < V; ++v) {
            Board board = graph.vertex_value.at(v);
            if (board == Black) {
              blacks++;
              continue;
            } else if (board == White) {
              whites++;
              continue;
            }
            if(dfs_s.state[v] == tools::Unvisited) {
              if(board == Empty) {
                region = NotAssigned;
                white_points = 0;
                black_points = 0;
                tools::Node<Board> start = {v, board};
                tools::dfs<Board>(graph.adj, dfs_s, start);
                if(region != Contestend) {
                  whites += white_points;
                  blacks += black_points;
                }
              }
            }
          }

          printf("Black %d White %d\n", blacks, whites);
        }
    }
}