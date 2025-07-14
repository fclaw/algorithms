/*
───────────────────────────────────────────────────────────────
🧳 UVa 821 Page Hopping, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/w_graph.cpp"
#include "tools/floyd_warshall.cpp"

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



namespace fd = algorithms::onlinejudge::graph::tools::floyd_warshall;
namespace wg = algorithms::onlinejudge::graph::tools::wg;

constexpr int MAX = 100;
constexpr int inf = 1e5;


namespace algorithms::onlinejudge::graph::page_hopping
{
    /** https://onlinejudge.org/external/8/821.pdf  */
    int t_cases = 1;
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
  
        int u, v;
        while(while_read(u, v) && u && v) {
          std::unordered_set<int> nodes;
          wg::WGraph<> graph(MAX);
          nodes.insert(u - 1);
          nodes.insert(v - 1);
          wg::pair(graph, u - 1, v - 1, 1, false);
          while(while_read(u, v) && u && v) {
            nodes.insert(u - 1);
            nodes.insert(v - 1);
            wg::pair(graph, u - 1, v - 1, 1, false);
          }

          fd::FloydWarshall<> fw_s(MAX, 0, inf);
          fw_s.mappend = [](int u, int v) { return u + v; };
          fd::floyd_warshall(graph, fw_s);

          int sum_of_clicks = 0;
          for(int u = 0; u < MAX; ++u) {
            for(int v = 0; v < MAX; ++v) {
              if(fw_s.matrix[u][v] != inf) {
                sum_of_clicks += fw_s.matrix[u][v];
              }
            }
          }

          // total number of such ordered pairs is given 
          // by the formula for permutations of n items 
          // taken 2 at a time, denoted P(n, 2)
          // P(n, 2) = n * (n - 1)
          int V = (int)nodes.size();
          int num_of_pairs = V * (V - 1);
          printf("Case %d: average length between pages = %0.3f clicks\n", t_cases++, (double)sum_of_clicks / num_of_pairs);
        }
    }
}