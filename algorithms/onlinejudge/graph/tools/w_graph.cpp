#pragma once

#include "dfs.cpp"
#include "../../debug.h"


namespace tools = algorithms::onlinejudge::graph::tools;

namespace algorithms::onlinejudge::graph::tools::wg
{
    template <typename W = int, typename T = tools::Unit>
    struct WNode
    {
        int node;
        W weight;
        T value;
    };

    template <typename W, typename T>
    std::ostream& operator << 
    (std::ostream& out, const WNode<W, T>& node) 
    { return out << "{n: " << node.node << ", w: "  << node.weight << "}"; }

    template <typename W = int, typename T = tools::Unit>
    using WGraph = std::vector<std::vector<WNode<W, T>>>;

    template <typename W = int, typename T = tools::Unit>
    WNode<W, T> mkWNode(int n, W w, T v = tools::Unit{}) { return {n, w, v}; }

    template <typename W = int>
    using WGrid = std::vector<std::vector<W>>;

    template <typename W = int, typename T = tools::Unit>
    void pair(WGraph<W, T>& graph, int u, int v, W w, bool is_bidirectional = true) {
      graph[u].push_back(wg::mkWNode(v, w));
      if(is_bidirectional) 
        graph[v].push_back(wg::mkWNode(u, w));
    }

    template <typename W = int, typename T = tools::Unit>
    void pair_cond(WGraph<W, T>& graph, int u, int v, W w, std::function<bool()> cond) {
      graph[u].push_back(wg::mkWNode(v, w));
      if(cond) graph[v].push_back(wg::mkWNode(u, w));
    }

    // Function to setup a WGraph from a grid of weights
    template <typename W = int, typename T = tools::Unit>
    WGraph<W, T> setupGraph(const WGrid<W>& grid, bool is_unidirectional = false) {
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
            if(in_bounds(nr, nc))
              pair(graph, node, neigh, grid[nr][nc], !is_unidirectional);
          }
        }
      }
      return graph;
    }
}