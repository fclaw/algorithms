/*
───────────────────────────────────────────────────────────────
🧳 UVa 1112 Mice and Maze, rt: s
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

namespace algorithms::onlinejudge::graph::mice_and_maze
{
    /** https://onlinejudge.org/external/11/1112.pdf */
    int t_cases, V, E, exit, timer;
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
        
        bool is_first = true;  
        while_read(t_cases);
        std::cin.ignore();
        while(t_cases--) {
          while_read(V);
          while_read(exit);
          while_read(timer);
          while_read(E);

          wg::WGraph<> graph(V);
          loop(E, [&] (int _) {
            int from, to, w;
            while_read(from, to, w);
            --from; --to;
            // reverse order
            graph[to].push_back(wg::mkWNode(from, w));
          });
          
          --exit;
          wg::WNode<> start = wg::mkWNode(exit, 0);
          auto mappend = [](int w, int a) { return w + a; };
          dijkstra::Dijkstra<> dijkstra_s(V, start, mappend);
          dijkstra::dijkstra(graph, dijkstra_s);
          int mouse_escaped = 0;
          for(int t : dijkstra_s.dist)
            if(t <= timer) mouse_escaped++;
          if(!is_first) std::cout << std::endl; else is_first = false;  
          std::cout << mouse_escaped << std::endl; 
        }
    }
}