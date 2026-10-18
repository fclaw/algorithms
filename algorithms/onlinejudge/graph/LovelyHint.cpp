/*
───────────────────────────────────────────────────────────────
🧳 UVa 11569 Lovely Hint, https://onlinejudge.org/external/115/11569.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 
constexpr char base = 'A';
constexpr int GRAPH_SIZE = 28;
constexpr int root = 0;

std::string removeDuplicates(std::string s) {
  std::unordered_map<char, int> exists;
  std::string ans;
  for (int i = 0; i < (int)s.size(); i++) {
    if (exists.find(s[i]) == exists.end()) {
      ans.push_back(s[i]);
      exists[s[i]]++;
    }
  }
  return ans;
}


void dfs_longest_path(int u, const vvi& graph, vi& dp) {
  for(int v : graph[u]) {
    dfs_longest_path(v, graph, dp);
    dp[u] = std::max(dp[u], 1 + dp[v]);
  }
}

void dfs_ways(int u, const vvi& graph, int depth, int& ways) {

  if(depth == 0) {
    ways++;
    return;
  }

  for(int v : graph[u]) {
    dfs_ways(v, graph, depth - 1, ways);
  }
}


namespace algorithms::onlinejudge::graph::lovely_hint
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
        stdin_read(t_cases);
        std::cin.ignore();
        while(t_cases--) {
          std::string s;
          std::getline(std::cin, s);
          s = removeDuplicates(s);
          vvi graph(GRAPH_SIZE);
          vi in_degree(GRAPH_SIZE, 0);
          std::unordered_set<char> letters;
          for(char from_c : s) {
            for(char to_c : s) {
              if(std::isalpha(from_c) && 
                 std::isalpha(to_c)) {
                int from = (from_c - base) + 1;
                int to = (to_c - base) + 1;
                letters.insert(from_c);
                letters.insert(to_c);
                if(5 * from <= 4 * to) {
                  graph[from].push_back(to);
                  in_degree[to]++;
                }
              }
            }
          }
          for(int n = 1; n < GRAPH_SIZE; ++n) {
            if(!in_degree[n] && 
               letters.count((n - 1) + base)) {
              graph[root].push_back(n);
            }
          }

          vi dp(GRAPH_SIZE, 0);
          dfs_longest_path(root, graph, dp);
          int ways = 0;
          dfs_ways(root, graph, dp[root], ways);
          std::cout << dp[root] << " " << ways << "\n";
        }
    }
}
