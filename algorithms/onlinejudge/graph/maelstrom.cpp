/*
───────────────────────────────────────────────────────────────
🧳 UVa 423 MPI Maelstrom, rt: s
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


bool is_number(const std::string &s) {
  auto is_digit = [](char ch) { return std::isdigit(static_cast<unsigned char>(ch)); };
  return !s.empty() && std::all_of(s.begin(), s.end(), is_digit);
}

namespace algorithms::onlinejudge::graph::maelstrom
{
    /** https://onlinejudge.org/external/4/423.pdf */
    int V;
    constexpr int inf = 1e5;
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
        
        while(while_read(V)) {
          std::string s;
          wg::WGraph<> graph(V);
          for(int u = 1; u < V; ++u) {
            for(int v = 0; v < u; ++v) {
              while_read(s);
              if(is_number(s)) {
                int latency = std::stoi(s);
                wg::pair(graph, u, v, latency);
              }
            }
          }
          
          fd::FloydWarshall<> fw_s(V, 0, inf);
          fw_s.mappend = [](int u, int v) { return u + v; };
          fd::floyd_warshall(graph, fw_s);

          int min_broadcast_tm = 0;
          for(int n = 1; n < V; ++n) {
            min_broadcast_tm = std::max(min_broadcast_tm, fw_s.matrix[0][n]);
          }
          std::cout << min_broadcast_tm << std::endl;
        }  
    }
}