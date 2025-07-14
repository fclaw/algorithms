/*
───────────────────────────────────────────────────────────────
🧳 UVa 567 Risk, rt: s
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


constexpr int V = 20;
constexpr int inf = 1e5;

namespace algorithms::onlinejudge::graph::risk
{
    /** https://onlinejudge.org/external/5/567.pdf  */
    int t_cases = 1, Q;
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
  
        int num_neighbors;
        // The main loop condition: try to read the very first integer of a new test set.
        // This will fail cleanly at the end of the file. `std::cin >> var` is a robust way
        // to handle leading whitespace, blank lines, etc.
        while (std::cin >> num_neighbors) {
          wg::WGraph<> graph(V); // The graph always has 20 countries (1-20)
          // We already read the number of neighbors for country 1.
          for(int i = 0; i < num_neighbors; ++i) {
            int neighbor;
            std::cin >> neighbor;
            // Add undirected edge from 1 to neighbor (0-indexed vs 1-indexed)
            wg::pair(graph, 1 - 1, neighbor - 1, 1, true);
          }

          // Now, read the definitions for countries 2 through 19.
          for(int u = 2; u <= 19; ++u) {
            std::cin >> num_neighbors;
            for(int i = 0; i < num_neighbors; ++i) {
              int neighbor;
              std::cin >> neighbor;
              wg::pair(graph, u - 1, neighbor - 1, 1, true);
            }
          }

          fd::FloydWarshall<> fw_s(V, 0, inf);
          fw_s.mappend = [](int u, int v) { return u + v; };
          fd::floyd_warshall(graph, fw_s);

          printf("Test Set #%d\n", t_cases++);
          std::cin >> Q;
          while(Q--) {
            int start, end;
            while_read(start, end);
            int how_many = fw_s.getPath(start - 1, end - 1).size() - 1;
            printf("%2d to %2d: %d\n", start, end, how_many);
          }
          std::cout << std::endl;
        }
    }
}