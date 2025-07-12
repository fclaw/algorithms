/* courtesy of https://github.com/stevenhalim/cpbook-code/blob/master/ch4/sssp/bellman_ford.cpp */

#pragma once

#include "w_graph.cpp"

#include <queue>
#include <functional>
#include <cstring>
#include <algorithm>
#include <vector>


namespace wg = algorithms::onlinejudge::graph::tools::wg;

using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int MAX_V = 450; // if |V| > 450, you cannot use Floyd Washall's


namespace algorithms::onlinejudge::graph::tools::floyd_warshall
{
    template<typename W = int, typename T = tools::Unit>
    struct FloydWarshall
    {
        vvi matrix;
        vvi path;
        W inf;
        W def;
        std::function<W(W, W)> mappend;
        FloydWarshall(int V, W def, W inf) {
          if(V > MAX_V) throw std::runtime_error("floyd warshall: cannot support the size greater then 450!");
          this->inf = inf;
          this->def = def;
          matrix.assign(V, vi(V, inf));
          for(int v = 0; v < V; ++v) 
            matrix[v][v] = def; // base neutral element in W (for int is 0)
        }

        vi getPath(int start, int end) const {
          // Check if a path exists first
          if(matrix[start][end] == inf) {
            return {}; // Return an empty vector for no path
          }

          vi p;
          int current = start;
          p.push_back(current);
          while (current != end) {
            // Get the next node on the path from 'current' to 'end'
            current = path[current][end];
            if (current == -1) {
              // Should not happen if matrix[start][end] != inf, but good for safety
              return {}; // Path broken
            }
            p.push_back(current);
          }
          return p;
        }

    };

    template<typename W, typename T>
    void floyd_warshall(
      const wg::WGraph<W, T>& graph,
      FloydWarshall<W, T>& fw_s) {

      if(!fw_s.mappend) 
        throw std::runtime_error("floyd warshall: mappend are not set!");

      int V = (int)graph.size();
      auto& matrix = fw_s.matrix;
      auto& path = fw_s.path;
      path.assign(V, vi(V));

      for(int i = 0; i < V; ++i) {
        for(int j = 0; j < V; ++j) {
          if (i == j) {
            path[i][j] = i;
          } else {
            path[i][j] = -1; // No path known yet
          }
        }
      }

      for(int u = 0; u < V; ++u)
        for(const wg::WNode<W, T>& n : graph[u]) {
          matrix[u][n.node] = std::min(matrix[u][n.node], n.weight);
          // The next node on the path from u to n.node is n.node itself
          path[u][n.node] = n.node;
        }

      for(int k = 0; k < V; ++k) {               // loop order is k->u->v, first fix the intermediate vertex
        for(int u = 0; u < V; ++u) {
          for(int v = 0; v < V; ++v) {
            // Check for "infinite" paths to avoid overflow
            if(matrix[u][k] != fw_s.inf && 
               matrix[k][v] != fw_s.inf) {
              W dist = fw_s.mappend(matrix[u][k], matrix[k][v]);
              if(dist < matrix[u][v]) {
                matrix[u][v] = dist;
                // The path from u to v now goes through k.
                // So, the first step from u should be the same
                // as the first step on the path from u to k.
                path[u][v] = path[u][k];
              }
            }
          }
        }
      }
    }
}