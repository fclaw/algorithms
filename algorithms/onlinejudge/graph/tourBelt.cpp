/*
───────────────────────────────────────────────────────────────
🧳 UVa 1265 Tour Belt, rt: s
───────────────────────────────────────────────────────────────
  MST Constraint Commentary Block

  The problem requires building a structure similar to a 
  Maximum Spanning Tree (MST), but with an extra condition:
  
    For each component B in the resulting forest:
      Every internal edge of B must have strictly greater
      weight than any edge connecting B to the outside 
      (border edge).

  ⚠️ Implication:
    We cannot merge two components with an edge of weight w
    if there still exists a border edge of weight w, 
    because:
      -> The synergy (weight) of internal edge (w)
         is NOT strictly greater than border edge (w)
      -> This violates the constraint

  ✅ Correct Strategy:
    - Sort all edges by non-increasing weight
    - Process edges in groups of equal weight
    - For each group of weight w:
        1. Mark which pairs of components can be merged
        2. Delay the actual union operations
        3. After all safe merges are known, apply them
    - After this group is processed:
        -> All components that remain disjoint are final 
           (cannot be merged without violating constraints)
        -> Their sizes can be recorded

  🧠 Insight:
    This strategy ensures no component includes a border 
    edge of equal or higher weight than any of its internal 
    edges.
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
#include <set>

namespace mst = algorithms::onlinejudge::graph::tools::mst;
namespace tools = algorithms::onlinejudge::graph::tools;

enum Edge { Internal, External };


namespace algorithms::onlinejudge::graph::tour_belt
{
    /** https://onlinejudge.org/external/12/1265.pdf */
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
          tools::vvi synergies(V, tools::vi(V, tools::sentinel));
          mst::VEdge<> islands;
          loop(E, [&](int _) {
            int from, to, synergy;
            while_read(from, to, synergy);
            --from; --to;
            islands.push_back(mst::mkDefEdge(from, to, synergy));
            synergies[from][to] = synergies[to][from] = synergy;
          });

          mst::Kruskal<> kruskal_s = mst::initKruskal(V, (int)islands.size(), 0);
          kruskal_s.cmp = 
            [](const mst::Edge<>& lhs, 
               const mst::Edge<>& rhs) 
            { return lhs.weight > rhs.weight; };

          std::set<mst::Edge<>> used;  
          kruskal_s.check_edge =  
            [&](const mst::Edge<>& e) 
              -> mst::EdgeAction {
  
            used.insert(e);    
            // Find the representatives of e.from and e.to
            int fromRep = kruskal_s.uf.findSet(e.from);
            int toRep = kruskal_s.uf.findSet(e.to);

            if(kruskal_s.uf.sizeOfSet(fromRep) < 2 && 
               kruskal_s.uf.sizeOfSet(toRep) < 2)
              return mst::GoOn;

            tools::vi merged_members = kruskal_s.uf.getMembers(fromRep);
            tools::vi to_merge = kruskal_s.uf.getMembers(toRep);
            merged_members.insert(merged_members.end(), to_merge.begin(), to_merge.end());
            std::unordered_set<int> region(merged_members.begin(), merged_members.end());


            // Assume: `region` is a set containing all nodes in the merged component
            // `synergies[u][v]` is the adjacency matrix, -1 means no edge
            std::set<std::pair<Edge, int>> edge_classes;

            int w = e.weight;

            for(int u : region) {
              for(int v = 0; v < V; ++v) {
                if(u == v || synergies[u][v] == tools::sentinel) continue;
                if (u > v) continue; // Avoid double-counting

                // Skip the edge being evaluated
                auto curr_edge = mst::mkDefEdge(u, v, synergies[u][v]);
                if(curr_edge == e)
                  continue;

                bool u_in = region.count(u);
                bool v_in = region.count(v);
                if(u_in && v_in)
                  edge_classes.emplace(Edge::Internal, synergies[u][v]);
                else if(!used.count(curr_edge))
                  edge_classes.emplace(Edge::External, synergies[u][v]);
              }
            }

            if(edge_classes.empty()) return mst::Skip;
            for (auto& [type, weight] : edge_classes) {
              if(type == Edge::Internal && w > weight) {
                return mst::Skip; // internal edge violates synergy condition
              }
              if(type == Edge::External && w <= weight) {
                return mst::Skip; // border edge violates synergy condition
              }
            }
            return mst::GoOn;
          };
          int candidates = 0;
          kruskal_s.on_adding_edge =
            [&](int i, const mst::Edge<>& e) {
              int rep = kruskal_s.uf.findSet(e.from);
              int size = kruskal_s.uf.sizeOfSet(rep);
              candidates += size;
              synergies[e.from][e.to] = synergies[e.to][e.from] = tools::sentinel;
            };
          mst::kruskal(islands, kruskal_s);
          if(kruskal_s.uf.numDisjointSets() > 1) candidates += V;
          std::cout << candidates << std::endl;
        } 
    }
}