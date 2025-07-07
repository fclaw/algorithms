/*
───────────────────────────────────────────────────────────────
🧳 UVa  11338 Minefield, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/w_graph.cpp"
#include "tools/dijkstra.cpp"

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
#include <queue>
#include <cctype>
#include <utility>
#include <functional>
#include <set>
#include <sstream>
#include <cmath>




namespace wg = algorithms::onlinejudge::graph::tools::wg;
namespace dijkstra = algorithms::onlinejudge::graph::tools::dijkstra;

typedef std::pair<double, double> pdd;

constexpr double epsilon = 1e-6;


namespace algorithms::onlinejudge::graph::minefield
{
    /** https://onlinejudge.org/external/113/11338.pdf */
    int W, H, P;
    double safe_walk;
    double gap(const pdd& first, const pdd& second) {
      double fx = first.first;
      double fy = first.second;
      double sx = second.first;
      double sy = second.second;
      double x_diff = std::abs(fx - sx);
      double y_diff = std::abs(fy - sy);
      return x_diff * x_diff + y_diff * y_diff;
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
        
        while(while_read(W, H)) {
          while_read(P);
          std::vector<pdd> points(P);
          for(int p = 0; p < P; ++p) {
            pdd coord;
            while_read(coord);
            points[p] = coord;
          }
          points.push_back({0, 0});
          points.push_back({W, H});
          while_read(safe_walk);

          wg::WGraph<double> graph(P + 2);
          for(int u = 0; u < P + 2; ++u)
            for(int v = 0; v < P + 2; ++v)
              if(u != v) {
                double d = gap(points[u], points[v]);
                wg::pair(graph, u, v, std::sqrt(d));
              }
          
          tools::vi path(P + 2, -1);
          wg::WNode<double> start = wg::mkWNode(P, 0.0);
          dijkstra::Dijkstra<double> dijkstra_s(P + 2, start);
          dijkstra_s.mappend = [](double w, double a) { return w + a; };
          dijkstra_s.on_relaxation = [&](int u, int v) { path[v] = u; };
          dijkstra_s.on_tied_path = [&](int u, int v) { path[v] = u; };
          dijkstra::dijkstra(graph, dijkstra_s);

          bool is_passable = true;
          int idx = P + 1;
          for(; path[idx] != -1; idx = path[idx]) {
            if(dijkstra_s.dist[idx] > 
               safe_walk + epsilon) {
              is_passable = false; break;
            }
          }
          std::cout << (is_passable ? "I am lucky!" : "Boom!") << std::endl;
        }
    }
}