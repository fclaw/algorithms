/*
───────────────────────────────────────────────────────────────
🧳 UVa 929 Number Maze, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dijkstra.cpp"
#include "tools/w_graph.cpp"

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


namespace dijkstra = algorithms::onlinejudge::graph::tools::dijkstra;
namespace wg = algorithms::onlinejudge::graph::tools::wg;

namespace algorithms::onlinejudge::graph::numbered_maze
{
    /** https://onlinejudge.org/external/9/929.pdf */
    int t_cases, N, M;
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
          while_read(N);
          while_read(M);
          std::cin.ignore();
          tools::vvi maze(N);
          std::string s;
          loop(N, [&] (int i) {
            std::getline(std::cin, s);
            for(int j = 0; j < (int)s.size(); ++j) 
              if(std::isdigit(s[j])) 
                maze[i].push_back(s[j] - '0');
          });

          wg::WGraph<> graph = wg::setupGraph(maze);
          int V = N * M;
          wg::WNode<> start = wg::mkWNode(0, 0);
          dijkstra::Dijkstra<> dijkstra_s(V + 1, start);
          dijkstra::dijkstra(graph, dijkstra_s);
          std::cout << dijkstra_s.dist[V] << std::endl;
        }
    }
}