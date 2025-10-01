/*
───────────────────────────────────────────────────────────────
🧳 UVa 10862 Connect the Cable Wires, the pattern ends up ≈ Fibonacci, https://onlinejudge.org/external/108/10862.pdf,
  A001906 F(2n) = bisection of Fibonacci sequence: a(n) = 3*a(n-1) - a(n-2), rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../graph/tools/uf.cpp"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>


namespace uf = algorithms::onlinejudge::graph::tools;
namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

using ull = unsigned long long;
using ii = std::pair<int, int>;
using s_ii = std::set<ii>;
using v_ii = std::vector<ii>;
using v_sii = std::vector<std::set<ii>>;
using v_bg = std::vector<bg::bigint>;


bool backtrack(int pos, const v_ii& edges, uf::UnionFind uf, s_ii& curr_topology, v_sii& topologies) {
  if(uf.numDisjointSets() == 1) {
    if(std::find(topologies.begin(), topologies.end(), curr_topology) != topologies.end()) {
      return false; // Already seen this configuration
    }
    topologies.push_back(curr_topology);
    return true; // Found a valid configuration
  }

  for(int it_pos = pos; it_pos < (int)edges.size(); ++it_pos) {
    ii e = edges[it_pos];
    uf::UnionFind uf_copy = uf; // Create a copy to preserve the original state
    if(!uf_copy.isSameSet(e.first, e.second)) {
      uf_copy.unionSet(e.first, e.second);
      curr_topology.insert(e);
      if(backtrack(pos + 1, edges, uf_copy, curr_topology, topologies)) {
        curr_topology.erase(e);
        return true; // Found a valid configuration
      } else curr_topology.erase(e);
    }
  }

  return false; // No valid configuration found from this state
}


namespace algorithms::onlinejudge::maths::connect_the_cable_wires
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        v_bg bis_fibs(2001);
        bis_fibs[0] = bg::bigint(0);
        bis_fibs[1] = bg::bigint(1);
        for(int i = 2; i <= 2000; i++) {
          bis_fibs[i] = 3 * bis_fibs[i - 1] - bis_fibs[i - 2];
        }    

        int houses;
        while(scanf("%d", &houses) == 1 && houses != 0) {
        //   v_ii edges;
        //   for(int i = 1; i <= houses; i++) {
        //     if(i < houses) edges.push_back(std::make_pair(i, i + 1));
        //     edges.push_back(std::make_pair(0, i));
        //   }
        //   v_sii topologies;
        //   uf::UnionFind uf(houses + 1);
        //   s_ii curr_topology;
        //   while(backtrack(0, edges, uf, curr_topology, topologies));
        //   printf("%d\n", (int)topologies.size());
            printf("%s\n", bis_fibs[houses].getRawRep().c_str());
        }
    }
}