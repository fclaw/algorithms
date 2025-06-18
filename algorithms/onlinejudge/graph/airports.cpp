/*
───────────────────────────────────────────────────────────────
🧳 UVa 11733 Airports, rt: s
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


namespace algorithms::onlinejudge::graph::airports
{
    /** https://onlinejudge.org/external/117/11733.pdf */
    int t_cases, V, E, A, c = 1;
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
          while_read(V, E, A);
          mst::VEdge<> roads;
          loop(E, [&](int _) {
            int from, to, w;
            while_read(from, to, w);
            --from; --to;
            roads.push_back(mst::mkDefEdge(from, to, w));
          });

          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)roads.size(), 0);
          int airports = 0;
          kruskal_s.mappend = 
            [&](int& acc, int c) {
              if(c >= A) {
                acc += A;
                airports++;
              } else acc += c;
            };  
          mst::kruskal(roads, kruskal_s);
          printf("Case #%d: %d %d\n", c++, kruskal_s.uf.numDisjointSets() * A + kruskal_s.min_cost, airports + kruskal_s.uf.numDisjointSets());
        }
    }
}