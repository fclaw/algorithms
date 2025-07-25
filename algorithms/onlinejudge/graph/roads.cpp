 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 10308 Roads in the North, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

struct Node
{
    int node_id;
    ll w;
};


using v_node = std::vector<Node>;
using map_v_node = std::unordered_map<int, v_node>;

struct Ans 
{
    int u;
    ll w;
    bool operator == (const Ans& other) const { 
      return u == other.u && w == other.w; 
    }
    bool operator < (const Ans& other) const { 
      return w < other.w;
    }
};

Ans def = {0, 0};

Ans find_farthest_village(
  int village_id,
  int parent,
  const map_v_node& roads) {
  // Start by assuming this node is the farthest in its subtree.
  Ans best = {village_id, 0};
  for(auto& v : roads.at(village_id)) {
    if(v.node_id == parent) continue;
    Ans farthest_in_child_subtree = 
      find_farthest_village(v.node_id, village_id, roads);
    farthest_in_child_subtree.w += v.w;
    best = std::max(best, farthest_in_child_subtree);
  }
  return best;
}

void solve(const map_v_node& roads) {
  Ans first_distant_village = find_farthest_village(roads.begin()->first, -1, roads);
  int village_id = first_distant_village.u;
  Ans second_distant_village = find_farthest_village(village_id, -1, roads);
  std::cout << second_distant_village.w << std::endl;
}

namespace algorithms::onlinejudge::graph::roads
{
    /** https://onlinejudge.org/external/103/10308.pdf */
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
        
        int u, v; ll w;
        std::string line;
        map_v_node roads;
        // The main loop reads every line in the input
        while(std::getline(std::cin, line)) {  
          // --- End-of-Case Condition ---
          if(line.empty()) {
            if(!roads.empty()) {
              solve(roads);
              roads.clear();
            }
            continue; // Move to the next line
          }
          // --- Parse the line ---
          std::stringstream ss(line);
          if (ss >> u >> v >> w) {
            roads[u].push_back({v, w});
            roads[v].push_back({u, w});
          }
        }

        // --- THE CRUCIAL FIX ---
        // After the loop ends, the last test case is still in the 'roads' buffer.
        // We must process it here.
        if (!roads.empty()) { solve(roads); }
    }
}