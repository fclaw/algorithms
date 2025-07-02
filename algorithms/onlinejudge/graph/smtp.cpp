/*
───────────────────────────────────────────────────────────────
🧳 UVa  10986 Sending email, rt: s
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

namespace algorithms::onlinejudge::graph::smtp
{
    /** https://onlinejudge.org/external/109/10986.pdf */
    int t_cases, c = 1, V, E, source, sink;
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
          while_read(V, E, source, sink);
          wg::WGraph<> network(V);
          loop(E, [&] (int _) {
            int from, to, latency;
            while_read(from, to, latency);
            network[from].push_back(wg::mkWNode(to, latency));
            network[to].push_back(wg::mkWNode(from, latency));
          });

          wg::WNode<> start = wg::mkWNode(source, 0);
          auto mappend = [](int w, int a) { return w + a; };
          dijkstra::Dijkstra<> dijkstra_s(V, start, mappend);
          dijkstra::dijkstra(network, dijkstra_s);
          int min_time = dijkstra_s.dist[sink];
          std::string ans = min_time == inf<int> ? "unreachable" : std::to_string(min_time);
          printf("Case #%d: %s\n", c++, ans.c_str());
        } 
    }
}