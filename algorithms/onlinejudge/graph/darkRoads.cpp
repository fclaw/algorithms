/*
───────────────────────────────────────────────────────────────
🧳 UVa 11631 Dark roads, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/mst.cpp"

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


namespace mst = algorithms::onlinejudge::graph::tools::mst;


namespace algorithms::onlinejudge::graph::dark_roads
{
    /** https://onlinejudge.org/external/116/11631.pdf */
    int V, E;
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
        
        while(while_read(V, E) && V && E) {
          
          int max_cost = 0;
          mst::VEdge<> roads;
          loop(E, [&](int _) {
            int from, to, w;
            while_read(from, to, w);
            max_cost += w;
            roads.push_back(mst::mkDefEdge(from, to, w));
          });
 
          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)roads.size(), 0);
          kruskal_s.mappend = [](int& acc, int x) { acc += x; };
          mst::kruskal(roads, kruskal_s);
          printf("%d\n", max_cost - kruskal_s.min_cost);
        }
    }
}