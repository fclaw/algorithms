/*
───────────────────────────────────────────────────────────────
🧳 UVa 1222 Bribing FIPA, https://onlinejudge.org/external/12/1222.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int Inf = (int)1e9;
constexpr int root = 0;

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;

/**
 * Represents the pure topological structure of a country in the domination tree.
 * 
 * Weights (diamonds) and DP states (dp table) are decoupled and stored in 
 * external flat vectors for O(1) random access and instant resets between test cases.
 */
struct Node
{
    // Unique identifier of this country (1 to N, or 0 for the dummy root)
    int id;

    // IDs of subordinate countries directly dominated by this country.
    // Replaces nested object trees with flat, lightweight integer references.
    vi children;
};

using Tree = std::vector<Node>;



// Global or per-testcase City ID Mapper
std::unordered_map<std::string, int> country_to_id;
int unique_country_counter;

int get_id(const std::string& raw_country) {
  auto it = country_to_id.find(raw_country);
  if (it != country_to_id.end()) return it->second;
  country_to_id[raw_country] = unique_country_counter++;
  return country_to_id.at(raw_country);
}

void dfs(int u, const Tree& forest, const vi& diamonds, vi& subtree_size, vvi& dp, int countries_n) {

  // base case
  dp[u][0] = 0;
  int& max_votes = subtree_size[u];
  max_votes = 1;

  // collect the result from children
  for(int v : forest[u].children) {
    dfs(v, forest, diamonds, subtree_size, dp, countries_n);
    // merge subtree result into root
    vi next_dp(countries_n + 2, Inf);
    for (int p_v = 0; p_v <= max_votes; ++p_v) {
      for (int c_v = 0; c_v <= max_votes && p_v + c_v <= countries_n; ++c_v) {
        next_dp[p_v + c_v] = std::min(next_dp[p_v + c_v], dp[u][p_v] + dp[v][c_v]);
      }
    }

    max_votes += subtree_size[v];
    for (int v = 0; v <= max_votes; ++v) {
      dp[u][v] = next_dp[v];
    }
  }

  if(u != root) {
    // whether it is cheaper to bribe the root
    dp[u][max_votes] = std::min(dp[u][max_votes], diamonds[u]);
  }

}


int run_dp(const Tree& forest, const vi& diamonds, vi& subtree_size, vvi& dp, int votes, int countries_n) {
  dfs(root, forest, diamonds, subtree_size, dp, countries_n);
  // Take the minimum over all counts >= votes
  int ans = Inf;
  for (int v = votes; v <= countries_n; ++v) {
    ans = std::min(ans, dp[root][v]);
  }
  return ans;
}

namespace algorithms::onlinejudge::advanced_topics::bribing_FIPA
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

        std::string in;
        while(std::getline(std::cin, in) && in != "#") {

          // reset global vars
          country_to_id.clear();
          unique_country_counter = 1;

          int countries_n, votes;
          std::stringstream ss(in);
          ss >> countries_n >> votes;
          // 1. Graph Topology:
          Tree forest(countries_n + 2);
          
          forest.front() = {root, {}};

          // 2. Problem Weights (Decoupled):
          vi diamonds(countries_n + 2);
          vb has_parent(countries_n + 2, false);
          for(int n = 0; n < countries_n; ++n) {
            std::string str;
            std::getline(std::cin, str);
            std::stringstream ss(str);
            int d;
            std::string name;
            ss >> name >> d;
            int node_id = get_id(name);
            diamonds[node_id] = d;
            std::string child;
            forest[node_id] = {node_id, {}};
            while(ss >> child) {
              forest[node_id].children.push_back(get_id(child));
              has_parent[get_id(child)] = true;
            }
          }

          // assign trees to the dummy root
          for(const Node& node : forest) {
            if(node.id != root && 
               !has_parent[node.id]) {
              forest.front().children.push_back(node.id);
            }
          }

          // 3. Subtree sizes:
          vi subtree_size(countries_n + 2, 0);

          // 4. DP State Table (Decoupled):
          // dp[u][v] = min diamonds to get 'v' votes from subtree of node 'u'
          vvi dp(countries_n + 2, vi(countries_n + 2, Inf));

          printf("%d\n", run_dp(forest, diamonds, subtree_size, dp, votes, countries_n));
        }
    }
}