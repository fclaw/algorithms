#pragma once

#include "dfs.cpp"
#include "../../debug.h"


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::wg
{
    template <typename T = tools::Unit, typename W = int>
    struct WNode
    {
        int node;
        W weight;
        T value;
    };

    template <typename T, typename W>
    std::ostream& operator << 
    (std::ostream& out, const WNode<T, W>& node) 
    { return out << "{n: " << node.node << ", w: "  << node.weight << "}"; }

    template <typename T = tools::Unit, typename W = int>
    using WGraph = std::vector<std::vector<WNode<T, W>>>;

    template <typename T = tools::Unit, typename W = int>
    WNode<T, W> mkWNode(int n, W w, T v = tools::Unit{}) { return {n, w, v}; }


    // Function to setup a WGraph from a grid of weights
    template <typename T = tools::Unit, typename W = int>
    WGraph<T, W> setupGraph(
      const std::vector<std::vector<W>>& grid, 
      bool is_unidirectional = false) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        int V = rows * cols;
        WGraph<T, W> graph(V + 1);

        graph[0].push_back(mkWNode(1, grid[0][0]));

        auto in_bounds = [&](int r, int c) { return r >= 0 && r < rows && c >= 0 && c < cols; };

         // Fill the graph with nodes and their neighbors
        for(int r = 0; r < rows; ++r) {
          for(int c = 0; c < cols; ++c) {
             int node = r * cols + c + 1;  // Calculate the node index based on row and column
             W w = grid[r][c];
             for(const tools::Dir& d : tools::dirs_4) {
               int nr = r + d.r_shift;
               int nc = c + d.c_shift;
               int neigh = nr * cols + nc + 1;
               if(in_bounds(nr, nc)) {
                 W nw = grid[nr][nc];
                 if(is_unidirectional) {
                   // For unidirectional graph, ensure we don't revisit the reverse edge
                     graph[node].push_back(mkWNode(neigh, nw));  // Add edge in one direction
                 } else {
                   // For bidirectional graph, add both directions
                   graph[node].push_back(mkWNode(neigh, nw));  // Add edge in both directions
                   graph[neigh].push_back(mkWNode(node, w));  // Add reverse edge
                 }
               }
             }
          }
        }
       return graph;
    }
}