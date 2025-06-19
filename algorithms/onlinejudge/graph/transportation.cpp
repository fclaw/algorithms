/*
───────────────────────────────────────────────────────────────
🧳 UVa 11228 Transportation system, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/mst.cpp"
#include "tools/dfs.cpp"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cmath>

namespace mst = algorithms::onlinejudge::graph::tools::mst;
namespace tools = algorithms::onlinejudge::graph::tools;

typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;


namespace algorithms::onlinejudge::graph::transportation
{
    /** https://onlinejudge.org/external/112/11228.pdf */
    int t_cases, V, threshold, c = 1;
    int mk_cartesian_dist(const ii& p1, const ii& p2) 
    {
        int x_diff = std::abs(p1.first - p2.first);
        int y_diff = std::abs(p1.second - p2.second);
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

        while_read(t_cases);
        while(t_cases--) {
          while_read(V, threshold);

          vii points;
          loop(V, [&points](int _) {
            int x, y;
            while_read(x, y);
            points.push_back({x, y});
          });

          mst::VEdge<> distances;
          for(int i = 0; i < V; ++i)
            for(int j = i + 1; j < V; ++j) {
              ii from = points[i];
              ii to = points[j];
              distances.push_back(mst::mkDefEdge(i, j, mk_cartesian_dist(from, to)));
            }
  
          threshold *= threshold;
          double min_roads_ext = 0;
          double min_rails_ext = 0;
          int regions = 1;
          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)distances.size(), 0);
          kruskal_s.on_adding_edge =
            [&min_roads_ext, 
             &min_rails_ext,
             &regions]
            (const mst::Edge<int>& edge) {
              if(edge.weight < threshold)
               min_roads_ext += std::sqrt(edge.weight);
              else { 
                regions++;
                min_rails_ext += std::sqrt(edge.weight);
              }
            };
        
          mst::kruskal(distances, kruskal_s);

          printf("Case #%d: %d %0.f %0.f\n", c++, regions, min_roads_ext, min_rails_ext);
        }
    }
}