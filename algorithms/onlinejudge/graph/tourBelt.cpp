/*
───────────────────────────────────────────────────────────────
🧳 UVa 1265 Tour Belt, rt: s
───────────────────────────────────────────────────────────────

the size of a set, options

1 both size of 1
merge: always
merge condition: external edges < a single edge
2 first >= 2, second = 1,  (internal edge)
merge: conditional
merge condition: internal edge <= all internal edges (may appear several new), internal edge > external edges
3 first >= 2, second >= 2,  (external edge)
merge: conditional
merge condition: external edge > all other external edges
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


enum Merge {
    Merge_No_Contribution,   // Merge happens, but does not contribute to the total candidate count
    Merge_Valid,             // Valid merge, contributing to the total candidate count
    InvalidMerge             // Merge fails due to synergy condition violation
};

std::ostream& operator << (std::ostream& out, Merge merge) 
{
    std::string s;
    if(merge == Merge_No_Contribution) s = "Merge_No_Contribution";
    else if(merge == Merge_Valid) s = "Merge_Valid";
    else if(merge == InvalidMerge) s = "InvalidMerge";
    return out << s;
}


Merge is_candidate(
  int V,
  mst::Kruskal<>& kruskal_s,
  const tools::vvi& synergies,
  const mst::Edge<>& e) {
  
  // Find the representatives of e.from and e.to
  int fromRep = kruskal_s.uf.findSet(e.from);
  int toRep = kruskal_s.uf.findSet(e.to);

  // Get the members of the two sets (regions) involved in the merge
  tools::vi from_members = kruskal_s.uf.getMembers(fromRep);
  tools::vi to_members = kruskal_s.uf.getMembers(toRep);
  std::unordered_set<int> from_members_s(from_members.begin(), from_members.end());
  std::unordered_set<int> to_members_s(to_members.begin(), to_members.end());

  // Case 1: Both sets are of size 1
  int from_size = kruskal_s.uf.sizeOfSet(fromRep);
  int to_size = kruskal_s.uf.sizeOfSet(toRep);

  int w = e.weight;

  // Case 1: Check if the current edge creates a valid region with respect to border edges
  // if no Merge_No_Contribution
  if(from_size == 1 && to_size == 1) {
    for(int v = 0; v < V; ++v) {
      if(v == e.to || synergies[e.from][v] == tools::sentinel)
        continue;
      if(synergies[e.from][v] >= w) 
        return Merge_No_Contribution;
    }

    for(int v = 0; v < V; ++v) {
      if(e.from == v || synergies[e.to][v] == tools::sentinel)
        continue;
      if(synergies[e.to][v] >= w)
        return Merge_No_Contribution;
    }
    return Merge_Valid;
  }

  // Case 2: first set >= 2, second set = 1 therefore the edge becomes internal
  // none of internal edges must be lesser then a newly added one
  // Check the synergy condition for internal edges (internal edge must be strictly larger than border edges)
  if(from_size >= 2 && to_size == 1) {
    from_members_s.insert(e.to);
    for(int u : from_members_s)
      for(int v = 0; v < V; ++v) {
        int cw = synergies[u][v];
        if(mst::mkDefEdge(u, v, cw) == e || 
           synergies[u][v] == tools::sentinel) continue;
        if(from_members_s.count(v)) { // internal edge
          if(cw < w) return InvalidMerge;
        } else { // external edge
          if(cw >= w) return InvalidMerge;
        }
      }
    return Merge_Valid;
  } else if(to_size >= 2 && from_size == 1) {
    to_members_s.insert(e.from);
    for(int u : to_members_s)
      for(int v = 0; v < V; ++v) {
        int cw = synergies[u][v];
        if(mst::mkDefEdge(u, v, cw) == e ||
           synergies[u][v] == tools::sentinel) continue;
        if(to_members_s.count(v)) { // internal edge
          if(cw < w) return InvalidMerge;
        } else { // external edge
          if(cw >= w) return InvalidMerge;
        }
      }
    return Merge_Valid;
  }

  // Case 3: Both sets >= 2 (external edge)
  // just check whether all border edges are less then a newly added one
  if(from_size >= 2 && to_size >= 2) {
    for(int u : from_members_s)
      for(int v = 0; v < V; ++v) {
        int cw = synergies[u][v];
        if(mst::mkDefEdge(u, v, cw) == e  || 
           synergies[u][v] == tools::sentinel) continue;
        if(!from_members_s.count(v)) { // external edge
          if(cw >= w) return InvalidMerge;
        }
      }

    for(int u : to_members_s)
      for(int v = 0; v < V; ++v) {
        int cw = synergies[u][v];
        if(mst::mkDefEdge(u, v, cw) == e || 
           synergies[u][v] == tools::sentinel) continue;
        if(!to_members_s.count(v)) { // external edge
          if(cw >= w) return InvalidMerge;
        }
      }
    return Merge_Valid;
  }

  return Merge_Valid;
}


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
            {  return lhs.weight > rhs.weight || 
                      (lhs.weight == rhs.weight && 
                       std::tie(lhs.from, lhs.to) <
                       std::tie(rhs.from, rhs.to)); };

          int candidates = 0;             
          kruskal_s.check_edge =
            [&](const mst::Edge<>& e) 
              -> mst::EdgeAction {
             Merge merge = is_candidate(V, kruskal_s, synergies, e);  // Check if we can merge the regions
             // Case 1: Invalid merge, skip the edge
             if(merge == InvalidMerge)
               return mst::Skip;
             // Case 2: Merge happens but doesn't contribute to candidate count
             else if(merge == Merge_No_Contribution) 
               return mst::GoOn;
             // Case 3: Valid merge, contribute to candidate count
             else {
               // If the edge forms a valid merge, calculate the new candidates count:
               // Find the representative of the first node
              int rep_from = kruskal_s.uf.findSet(e.from);
              // Get the size of the set for 'from' node
              int from_size = kruskal_s.uf.sizeOfSet(rep_from);
              // Find the representative of the second node
              int rep_to = kruskal_s.uf.findSet(e.to);
              // Get the size of the set for 'to' node
              int to_size = kruskal_s.uf.sizeOfSet(rep_to);
              // Increment candidates by the total size of the two merged sets
              candidates += from_size + to_size;
              return mst::GoOn;
            }
          };
          mst::kruskal(islands, kruskal_s);
          if(kruskal_s.uf.numDisjointSets() > 1) candidates += V;
          std::cout << candidates << std::endl;
        } 
    }
}