/*
───────────────────────────────────────────────────────────────
🧳 UVa 1247 Interstar Transport, rt: s
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

constexpr int inf = 1e5;

struct Route 
{
    int cost;
    int hopes;
    bool operator < (const Route& other) const { return cost < other.cost || (cost == other.hopes && hopes < other.hopes); }
    bool operator == (const Route& other) const { return cost == other.cost && hopes == other.hopes; }
    bool operator != (const Route& other) const { return !(*this == other); }
};


namespace algorithms::onlinejudge::graph::interstar_transport
{
    /** https://onlinejudge.org/external/12/1247.pdf */
    int V, E, Q;
    int getIdx(char c) { return c - '0' - 17; }
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
        
        while(while_read(V, E)) {
          std::vector<char> planets(V);
          wg::WGraph<Route> graph(V);
          for(int e = 0; e < E; ++e) {
            char s_u, s_v;
            int cost;
            while_read(s_u, s_v, cost);
            int u = getIdx(s_u);
            int v = getIdx(s_v);
            planets[u] = s_u;
            planets[v] = s_v;
            wg::pair(graph, u, v, {cost, 1});
          }

          fd::FloydWarshall<Route> fw_s(V, {0, 0}, {inf, inf});
          fw_s.mappend = 
            [](const Route& u, const Route& v) 
            { return (Route){u.cost + v.cost, u.hopes + v.hopes}; };
          fd::floyd_warshall(graph, fw_s);

          while_read(Q);
          while(Q--) {
            char s_start, s_end;
            while_read(s_start, s_end);
            int start = getIdx(s_start);
            int end = getIdx(s_end);

            auto xs = fw_s.getPath(start, end);
            std::string path;
            for(int idx : xs) {
              path += std::string(1, planets[idx]) + " ";
            }
            path.pop_back();
            std::cout << path << std::endl;
          }
        }
    }
}