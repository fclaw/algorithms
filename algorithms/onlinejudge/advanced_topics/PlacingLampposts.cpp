/*
───────────────────────────────────────────────────────────────
🧳 UVa 10859 Placing Lampposts, https://onlinejudge.org/external/108/10859.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int Inf = (int)1e9;

using vi = std::vector<int>;
using vvi = std::vector<vi>;


struct State {
  // Primary Goal: Minimize lampposts
  int lampposts;

  // Secondary Goal: Maximize roads lit by 2 lampposts
  int double_lit_roads;

  // Comparator for std::min:
  // "Is this state strictly better than state 's'?"
  bool operator < (const State& s) const {
    if (lampposts != s.lampposts) {
     return lampposts < s.lampposts; // Fewer lampposts is strictly better
    }
    return double_lit_roads > s.double_lit_roads; // More double-lit roads is strictly better!
  }

  // Adding states together when merging subtrees
  State operator + (const State& s) const {
    return {lampposts + s.lampposts, double_lit_roads + s.double_lit_roads};
  }
  State operator += (const State& s) {
    return (*this = *this + s);
  }
};

using v_state = std::vector<State>;
using vv_state = std::vector<v_state>;


void dfs(int u, int parent, const vvi& network, vv_state& dp) {

  dp[u][1] = {1, 0}; // lamppost installed
  dp[u][0] = {0, 0}; 

  for(int v : network[u]) {
    if(v != parent) {
      dfs(v, u, network, dp);

      dp[u][0] += dp[v][1];

      State tmp = dp[v][1];
      tmp.double_lit_roads++;
      dp[u][1] += std::min(dp[v][0], tmp);
    }
  }

}


State get_min_lampposts_installed(const vvi& network, int V) {

  if(V == 1) {
    return {0, 0};
  }

  vv_state dp(V, v_state(2, {0, 0})); // 0/1
  dfs(0, -1, network, dp);
  return std::min(dp[0][0], dp[0][1]);
}



namespace algorithms::onlinejudge::advanced_topics::lampposts
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

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int V, E;
          stdin_read(V, E);
          vvi network(V);
          for(int e = 0; e < E; ++e) {
            int from, to;
            stdin_read(from, to);
            network[from].push_back(to);
            network[to].push_back(from);
          }
          State ans = get_min_lampposts_installed(network, V);
          printf("%d %d %d\n", ans.lampposts, ans.double_lit_roads, E - ans.double_lit_roads);
        }
    }
}