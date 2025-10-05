/*
───────────────────────────────────────────────────────────────
🧳 UVa 11069, A Graph Problem, https://onlinejudge.org/external/110/11069.pdf, rt: s
   https://oeis.org/A000931: Padovan sequence (or Padovan numbers): a(n) = a(n-2) + a(n-3) with a(0) = 1, a(1) = a(2) = 0.
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vull = std::vector<ull>;


constexpr int MAX_NODES = 76;
constexpr int offset = 7;


ull backtrack(int node, int V, vi& set, vvi& subsets) {
  if(node > V) {
    bool is_subset = false;
    for(auto& s : subsets) {
      if(std::includes(s.begin(), s.end(), set.begin(), set.end())) {
        is_subset = true;
        break;
      }
    }
    if(!is_subset) {
      subsets.push_back(set);
      return 1;
    } else return 0;
  }

  ull ways = 0;
  for(int n = node; n <= V; ++n) {
    set.push_back(n);
    ways += backtrack(n + 2, V, set, subsets);
    set.pop_back();
  }
  return ways;
}



namespace algorithms::onlinejudge::maths::graph_problem
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

        vull dp(MAX_NODES + offset + 1);
        dp[0] = 1;
        dp[1] = 0;
        dp[2] = 0;
        for(int i = 3; i <= MAX_NODES + offset; ++i) {
          dp[i] = dp[i - 2] + dp[i - 3];
        }

        int nodes;
        while(scanf("%d", &nodes) == 1) {
          printf("%llu\n", dp[nodes + offset - 1]);
        }
    }
}