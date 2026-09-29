/*
───────────────────────────────────────────────────────────────
🧳 UVa 10243 Fire! Fire!!Fire!!!, https://onlinejudge.org/external/102/10243.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int Inf = (int)1e9;

using vi = std::vector<int>;
using vvi = std::vector<vi>;


void dfs(int u, int parent, const vvi& tree, vvi& dp) {

  dp[u][1] = 1; // placing a guard at u costs 1
  dp[u][0] = 0; // placing no guard at u costs 0

  for (int v : tree[u]) {
    if (v != parent) {
      dfs(v, u, tree, dp);

      // If u has NO guard, child v MUST have a guard to cover corridor (u, v)
      dp[u][0] += dp[v][1];

      // If u HAS a guard, corridor (u, v) is safe!
      // Child v is free to either have a guard or not (pick the cheaper one!)
      dp[u][1] += std::min(dp[v][0], dp[v][1]);
    }
  }

}


int min_fire_exits_required(const vvi& tree, int rooms_n) {
  // Special Edge Case: Single room castle requires 1 exit!
  if (rooms_n == 1) {
    return 1;
  }

  vvi dp(rooms_n + 1, vi(2, 0));
  dfs(1, -1, tree, dp);
  return std::min(dp[1][1], dp[1][0]);
}

namespace algorithms::onlinejudge::advanced_topics::fire
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

        int rooms_n;
        while(stdin_read(rooms_n) && rooms_n) {
          int n;
          vvi tree(rooms_n + 1);
          for(int u = 1; u <= rooms_n; ++u) {
            stdin_read(n);
            while(n--) {
              int v;
              stdin_read(v);
              tree[u].push_back(v);
            }
          }
          printf("%d\n", min_fire_exits_required(tree, rooms_n));
        }
    }
}