/*
───────────────────────────────────────────────────────────────
🧳 UVa 103 Stacking Boxes, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"
#include "tools/bfs.cpp"

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




namespace tools = algorithms::onlinejudge::graph::tools;

using vi = std::vector<int>;

struct Box
{
    int idx;
    vi sides;
    // Your operator> would then change to this to match:
    bool operator < (const Box& other) const { // Naming it '<' is more intuitive
      for(int i = 0; i < (int)sides.size(); ++i)
        if(sides[i] >= other.sides[i]) return false; // Note the >=
      return true; 
    }
};

using v_box = std::vector<Box>;


namespace algorithms::onlinejudge::graph::stacking_boxes
{
    /** https://onlinejudge.org/external/1/103.pdf */
    int N, D;
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
        
        while(while_read(N, D)) {
          v_box boxes(N);
          for(int idx = 0; idx < N; ++idx) {
            Box box;
            box.idx = idx;
            auto& xs = box.sides; 
            xs.resize(D);
            for(int d = 0; d < D; ++d)
              while_read(xs[d]);
            std::sort(xs.begin(), xs.end());
            boxes[idx] = box;
          }
  
          tools::Graph<> graph(N);
          for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j) {
              if(i != j && boxes[j] < boxes[i]) {
                int u = boxes[i].idx; 
                int v = boxes[j].idx;
                graph[u].push_back(tools::mkDefNode(v));
              }
            }
             
          tools::TopSortKahn khan = tools::top_sort_kahn(N, graph);
          // dp[i] will store the LENGTH of the longest path ending at node i.
          vi dp(N, 1); // Initialize all paths to length 1 (the box itself)
          // parent[i] will store the predecessor of node i on its current longest path.
          // This is needed to reconstruct the final path.
          vi parent(N, -1);

          //Iterate through the nodes in the order given by the topological sort.
          for(int u : khan.top_sort) {   
            // For each neighbor v of u...
            for(const auto& neigh : graph[u]) {
              int v = neigh.node;     
              //Check if the path through u creates a longer path to v.
              if(dp[u] + 1 > dp[v]) {
                // We found a better path to v!
                dp[v] = dp[u] + 1;
                parent[v] = u; // The best way to get to v is now from u.
              }
            }
          }


          // 1. Find the length of the longest path and where it ends.
          int max_len = 0;
          int end_node = -1;
          for(int i = 0; i < N; ++i) {
            if(dp[i] > max_len) {
              max_len = dp[i];
              end_node = i;
            }
          }

          // 2. Reconstruct the path by backtracking using the parent array.
          vi path;
          int current_node = end_node;
          while(current_node != -1) {
            path.push_back(current_node);
            current_node = parent[current_node];
          }

          // std::string s;
          // for(int n : path) s += std::to_string(n + 1) + " ";
          // s.pop_back();
          // printf("%d\n%s\n", max_len, s.c_str());


          vi memo(N, -1);
          int ans = calculate_max_stack(0, khan.top_sort, graph, memo);
          dbg(ans);
        }
    }
}