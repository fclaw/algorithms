/*
───────────────────────────────────────────────────────────────
🧳 UVa 12442 Forwarding Emails, rt: s
───────────────────────────────────────────────────────────────
======================= Memoisation Insight =======================
Problem: UVa 12442 - Forwarding Emails
Type   : Directed Graph + DFS + Memoisation

Key Insight:
-------------
In problems where each node leads to another in a singly-linked fashion 
(e.g., a forwarding chain), traversing blindly leads to redundant work 
and possible TLE on large graphs.

The clever optimisation lies in **memoising** the number of reachable 
nodes from any given node — especially important when multiple DFS paths 
converge onto the same cycle or sub-path.

Example:
---------
If 1 → 2 → 3 → 1 forms a cycle of length 3, then:
  dp[1] = dp[2] = dp[3] = 3

Any other node (e.g., 4 → 1) just adds +1 to dp[1]:
  dp[4] = 1 + dp[1] = 4

This avoids recomputing the same cycle repeatedly from multiple entry points.

Cycle detection is integrated by tracking the DFS discovery order 
and using it to identify and annotate the entire cycle when a back edge 
is encountered.

Result:
--------
This memoisation ensures each node is processed at most once, 
bringing down total complexity to O(V) over all test cases.

Combined with fast I/O, this makes even the 50,000-node case 
runnable well within time limits.

===============================================================
*/

#include "../debug.h"
#include "../../aux.h"
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
#include <unordered_set>




namespace tools = algorithms::onlinejudge::graph::tools;


namespace algorithms::onlinejudge::graph::forwarding_emails
{
    /** https://onlinejudge.org/external/124/12442.pdf  */
    int t_cases, V, c = 1;
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
          while_read(V);

          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node community(V);
          
          loop(V, [&](int _) {
            int from, to;
            while_read(from, to);
            --from; --to;
            community[from].push_back(tools::mkDefNode(to));
          });

          int dp[V]; // stores longest path length from each node
          std::memset(dp, -1, sizeof(dp));
          tools::vi cycle_nodes;

          int max_martians = 0;
          int curr_martians;
          int start_martian = 0;

          dfs_s.on_discover = 
            [&]
            (tools::Node<>& node) {
              cycle_nodes.push_back(node.node);
              ++curr_martians; 
            };

          dfs_s.on_leaving = 
            [&cycle_nodes]
            (tools::Node<>& node) {
              cycle_nodes.pop_back();
            };

          dfs_s.process_tree_edge = 
            [&](
              const tools::Node<>& u, 
              const tools::Node<>& v) -> bool {
              if(~dp[v.node]) {
                dp[u.node] = dp[v.node] + 1;
                curr_martians += dp[v.node];
                dfs_s.is_finished = true;
                return false;
              }
              return true;
            };
    
          dfs_s.process_back_edge = 
            [&](
              const tools::Node<>& u, 
              const tools::Node<>& v) {
              // update all nodes involved
              int cycle_len = 1;
              tools::vi cycle;

              auto it = cycle_nodes.rbegin();
              for(; it != cycle_nodes.rend(); ++it) {
                cycle.push_back(*it);
                if(*it == v.node) break;
                ++cycle_len;
              }

              for(int n : cycle) dp[n] = cycle_len;
               dfs_s.is_finished = true; // early stop if needed
            };

          for(int v = 0; v < V; ++v) {
            if(~dp[v]) continue;  // already computed, skip
            curr_martians = 0;
            dfs_s.is_finished = false;
            std::fill(dfs_s.state.begin(), dfs_s.state.end(), tools::Unvisited);
            cycle_nodes.clear();
            tools::start_vertex = v;
            auto start = tools::mkDefNode(v);
            tools::dfs<>(community, dfs_s, start);
            dp[v] = curr_martians;     // store result for this root
            if(max_martians < curr_martians) {
              start_martian = v;
              max_martians = curr_martians;
            } else if(curr_martians == max_martians) {
                start_martian = std::min(start_martian, v);
            }
          }

          printf("Case %d: %d\n", c++, start_martian + 1);  
        }
    }
}