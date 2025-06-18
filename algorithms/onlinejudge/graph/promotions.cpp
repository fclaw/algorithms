/*
───────────────────────────────────────────────────────────────
🧳 UVa 13015 Promotions, rt: s
───────────────────────────────────────────────────────────────
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


namespace algorithms::onlinejudge::graph::promotions
{
    /** https://onlinejudge.org/external/130/13015.pdf */
    int L, U, V, E;
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
        
        while(while_read(L, U, V, E)) {
          tools::Dfs<> dfs_s = tools::init_dfs<>(V);
          tools::vv_def_node staff(V);

          loop(E, [&](int _) {
            int from, to;
            while_read(from, to);
            staff[from].push_back(tools::mkDefNode(to));
          });

        //   int dp[V]; // stores longest path length from each node
        //   std::memset(dp, -1, sizeof(dp));
          tools::vi dp(V, -1);

          dfs_s.process_tree_edge = 
            [&](const tools::Node<>& u, 
                const tools::Node<>& v) -> bool {
              if(~dp[v.node]) {
                dp[v.node] += 1;
                dfs_s.is_finished = true;
                return false;
              } else dp[v.node] = 1;
              return true;
            };

          for(int v = 0; v < V; ++v) {
            if(~dp[v]) continue;  // already computed, skip
            dfs_s.is_finished = false;
            std::fill(dfs_s.state.begin(), dfs_s.state.end(), tools::Unvisited);
            tools::start_vertex = v;
            auto start = tools::mkDefNode(v);
            tools::dfs<>(staff, dfs_s, start);
          }
          
          dbg(dp);
        }
    }
}