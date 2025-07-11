/*
───────────────────────────────────────────────────────────────
🧳 UVa 558 Wormholes, rt: 0.440s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bellman_ford.cpp"

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



namespace bf = algorithms::onlinejudge::graph::tools::bellman_ford;
namespace wg = algorithms::onlinejudge::graph::tools::wg;


namespace algorithms::onlinejudge::graph::wormholes
{
    /** https://onlinejudge.org/external/5/558.pdf */
    int t_cases, V, E;
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
          while_read(V, E);
          wg::WGraph<> graph(V);
          for(int e = 0; e < E; ++e) {
            int u, v, time;
            while_read(u, v, time);
            wg::pair(graph, u, v, time);
          }
           
          wg::WNode<> start = wg::mkWNode(0, 0);
          bf::BellmanFord<> bf_s(V, start, [](int d, int w) { return d + w; });
          bool is_source_in_cycle = false;
          bf_s.on_cycle = [&](int u, int v) { is_source_in_cycle = u == 0 || v == 0; };
          bf::bellman_ford(graph, bf_s);

          std::cout << (bf_s.hasNegativeCycle && !is_source_in_cycle ? "possible" : "not possible") << std::endl;
        }  
    }
}