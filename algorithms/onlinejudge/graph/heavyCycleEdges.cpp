/*
───────────────────────────────────────────────────────────────
🧳 UVa 11747 Heavy Cycle Edges, rt: s
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


namespace algorithms::onlinejudge::graph::heavy_cycle_edges
{
    /** https://onlinejudge.org/external/117/11747.pdf */
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
        
        while(while_read(V, E) && V) {
          mst::VEdge<> edges;
          loop(E, [&](int _) {
            int from, to, w;
            while_read(from, to, w);
            edges.push_back(mst::mkDefEdge(from, to, w));
          });
 
          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)edges.size(), 0);
          kruskal_s.mappend = [](int& acc, int x) { acc += x; };
          std::unordered_set<int> used;
          kruskal_s.on_adding_edge = [&used] (int i) { used.insert(i); };
          mst::kruskal(edges, kruskal_s);

          if(used.size() == edges.size() || !E) 
            printf("forest\n");
          else {
            std::string s;
            for(int i = 0; i < (int)edges.size(); ++i)
              if(!used.count(i))
                s += std::to_string(edges[i].weight) + " ";
            s.pop_back();
            std::cout << s << std::endl;
          }
        }
    }
}