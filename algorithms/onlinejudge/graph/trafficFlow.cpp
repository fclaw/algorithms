/*
───────────────────────────────────────────────────────────────
🧳 UVa 10842 Traffic Flow, rt: s
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


namespace algorithms::onlinejudge::graph::traffic_flow
{
    /** https://onlinejudge.org/external/108/10842.pdf */
    int t_cases, V, E, c = 1;
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
          wg::WGraph<> roads(V);
          loop(E, [&roads] (int _) {
            int from, to, cap;
            while_read(from, to, cap);
            roads[from].push_back(wg::mkWNode(to, cap));
            roads[to].push_back(wg::mkWNode(from, cap));
          });

          int min_cap = INT32_MAX;
          mst::Prim<> prim_s = mst::initPrim(V);
          prim_s.is_min = false;
          prim_s.on_adding_point = 
            [&min_cap](const wg::WNode<>& node) 
            { min_cap = std::min(min_cap, node.weight); };
          wg::WNode<> start = wg::mkWNode(0, INT32_MAX);
          mst::prim(roads, prim_s, start);
          printf("Case #%d: %d\n", c++, min_cap);
        }  
    }
}