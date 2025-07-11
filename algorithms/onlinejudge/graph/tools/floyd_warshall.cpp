/* courtesy of https://github.com/stevenhalim/cpbook-code/blob/master/ch4/sssp/bellman_ford.cpp */

#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>
#include <string>


namespace wg = algorithms::onlinejudge::graph::tools::wg;


constexpr int MAX_V = 450; // if |V| > 450, you cannot use Floyd Washall's

namespace algorithms::onlinejudge::graph::tools::floyd_warshall
{
    template<typename W = int, typename T = tools::Unit>
    struct FloydWarshall
    {
        int aj_mat[MAX_V][MAX_V];
        int V;
        FloydWarshall(int V, const wg::WGraph<W, T>& graph, W inf) {
          std::memset(aj_mat, inf, sizeof aj_mat);
          this->V = V;
          for(int v = 0; v < V; ++v) 
            aj_mat[v][v] = 0;
          
          for(int u = 0; u < V; ++u)
            for(const wg::WNode<W, T>& n : graph[v]) {
              int v = n.node;
              W w = n.weight;
              aj_mat[u][v] = w; 
            }
        }
    };

    template<typename W, typename T>
    void floyd_warshall(FloydWarshall<W, T>& fw_s) {
      int V = fw_s.V;
      auto& matrix = fw_s.aj_mat;
      for (int k = 0; k < V; ++k)                    // loop order is k->u->v
        for(int u = 0; u < V; ++u)
          for (int v = 0; v < V; ++v)
            matrix[u][v] = std::min(matrix[u][v], matrix[u][k] + matrix[k][v]);
    }
}