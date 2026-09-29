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

/**
 * Post-Order Tree Knapsack DP (Subtree Convolution)
 *
 * ============================================================================
 * DP STATE DEFINITION:
 * ============================================================================
 * dp[u][v] = Minimum diamonds needed to acquire AT LEAST 'v' votes
 *            from the subtree rooted at node 'u'.
 *
 * ============================================================================
 * CONNECTION TO THE NOTEBOOK DRAWING:
 * ============================================================================
 * At each node 'u', we merge its children iteratively.
 * Imagine an expanding bar of total available votes:
 *
 *   |<---------------------------- L --------------------------->|
 *   [==== Accumulated Votes (u) ====][==== New Child Votes (v) ====]
 *              'max_votes'                   'max_v_votes'
 *              (Left Bar)                     (Right Bar)
 *
 * - Left Bar  (max_votes)   : All vote counts currently reachable from node 'u'
 *                             and previously processed children.
 * - Right Bar (max_v_votes) : All vote counts reachable from new child 'v'.
 * - Combined  (Length L)    : The bar naturally expands to (max_votes + max_v_votes).
 *
 * ----------------------------------------------------------------------------
 * COMPLEXITY: WHY THIS IS O(N^2) (NOT O(N^3)):
 * ----------------------------------------------------------------------------
 * The two nested loops execute (max_votes * max_v_votes) times.
 * Geometrically, this is a rectangle of pairs: (Node in Subtree A, Node in Subtree B).
 * Any two nodes x and y in the tree are merged in this rectangle EXACTLY ONCE
 * across the entire algorithm—specifically, at their Lowest Common Ancestor (LCA).
 * Therefore, Total Operations across the tree = Sum of pairs = N*(N-1)/2 = O(N^2)!
 * ============================================================================
 */
void dfs(int u, const Tree& forest, const vi& diamonds, vi& subtree_size, vvi& dp, int countries_n) {

  // ------------------------------------------------------------------------
  // 1. BASE INITIALIZATION (Leaf State / Self-State)
  // ------------------------------------------------------------------------
  // Getting 0 votes costs 0 diamonds (universal invariant).
  dp[u][0] = 0;

  // 'max_votes' is a reference to subtree_size[u].
  // Initially, node 'u' represents only itself (Left Bar begins at size 1).
  int& max_votes = subtree_size[u];
  max_votes = 1;

  // ------------------------------------------------------------------------
  // 2. POST-ORDER TRAVERSAL & SIBLING MERGING
  // ------------------------------------------------------------------------
  for(int v : forest[u].children) {
    // Step 2a: Recursively solve child 'v' first (dive down to leaves).
    // By post-order property, child 'v' will have its entire 'dp[v]' table
    // fully computed and finalized before we touch it here.
    dfs(v, forest, diamonds, subtree_size, dp, countries_n);

    // Step 2b: Prepare temporary buffer to compute the expanded bar L.
    // We use a fresh buffer initialized to INF so that combinations
    // from this step do not accidentally overwrite and read from the same state.
    vi dp_buffer(countries_n + 2, Inf);
    int max_v_votes = subtree_size[v];
    // --------------------------------------------------------------------
    // Step 2c: The 2-Loop Convolution (Expanding from Drawing)
    // --------------------------------------------------------------------
    // Loop 1: Iterate over all vote counts achieved so far in Left Bar [0 .. max_votes]
    for (int u_votes = 0; u_votes <= max_votes; ++u_votes) {
      // Loop 2: Iterate over all vote counts possible in Right Bar [0 .. max_v_votes]
      for (int v_votes = 0; v_votes <= max_v_votes; ++v_votes) {
        if(u_votes + v_votes <= countries_n) {
          int sum = u_votes + v_votes;
          // Transition Formula:
          // Take the best way to get 'u_votes' from previous children
          // + the best way to get 'v_votes' from the new child 'v'.
          dp_buffer[sum] = std::min(dp_buffer[sum], dp[u][u_votes] + dp[v][v_votes]);
        }
      }
    }

    // --------------------------------------------------------------------
    // Step 2d: Expand the Bar to Length L
    // --------------------------------------------------------------------
    // The parent's subtree size naturally grows by the size of the merged child.
    max_votes += max_v_votes;
    for (int v = 0; v <= max_votes; ++v) {
      dp[u][v] = dp_buffer[v];
    }
  }

  // ------------------------------------------------------------------------
  // 3. THE MASTER OVERRIDE (Node u's Direct Bribe Choice)
  // ------------------------------------------------------------------------
  // After considering all combinations of cherry-picking its children,
  // node 'u' has one final superpower:
  // It can pay 'diamonds[u]' directly to instantly buy the ENTIRE subtree!
  //
  // This gives all 'max_votes' at once for a flat price of 'diamonds[u]'.
  // Note: We skip this for 'root' (Dummy Node 0) because Node 0 is an imaginary
  // placeholder unifying the forest; it cannot be bought directly!
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