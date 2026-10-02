/*
───────────────────────────────────────────────────────────────
🧳 UVa 10308 Roads in the North, https://onlinejudge.org/external/103/10308.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int MAX_VILLAGES = 10001;

using ll = long long;
using vll = std::vector<ll>;
using vvll = std::vector<vll>;
using pil = std::pair<int, ll>;
using vpil = std::vector<pil>;
using vvpil = std::vector<vpil>;
using pll = std::pair<ll, ll>;


enum Choice { ROOT_AS_START, GOES_THROUGH_ROOT };


// Helper lambda: updates pair {first_max, second_max} with a new value
auto update_top2 = 
  [](std::pair<ll, ll>& p, ll val) {
    if(val > p.first) {
      p.second = p.first;
      p.first = val;
    } else if (val > p.second) {
      p.second = val;
    }
  };


/**
 * Tree Diameter via Single-Pass Dynamic Programming
 * Reference: Problem 2 in Codeforces Blog (entry/20935)
 *
 * ============================================================================
 * THE TWO PATH TOPOLOGIES (THE "2-OPTIONS" MODEL):
 * ============================================================================
 * Any simple path in a rooted tree that has node 'u' as its highest point
 * must take one of two geometric shapes:
 *
 * 1. ROOT_AS_START (Single Branch):
 *    The path starts at node 'u' and goes strictly downwards into ONE child's subtree.
 *
 *         (u)           Length = weight(u, v) + dp[v][ROOT_AS_START]
 *          |
 *         (v)
 *          |
 *        [leaf]
 *
 * 2. GOES_THROUGH_ROOT (Two Branches Meeting at Apex 'u'):
 *    The path comes UP from one child's subtree, peaks at 'u', and goes DOWN 
 *    into a DIFFERENT child's subtree.
 *
 *        [leaf_1] ---> (v_1)           (v_2) ---> [leaf_2]
 *                         \             /
 *                          \           /
 *                              ( u )   <-- Apex (LCA)
 *
 *    Length = best_branch_1 + best_branch_2
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - Time Complexity:  O(V + E) — single-pass post-order traversal!
 * - Space Complexity: O(V) for the DP table and recursion stack.
 * ============================================================================
 */
void dfs(int u, int parent, const vvpil& graph, vvll& dp, ll& max_diameter) {
  // ------------------------------------------------------------------------
  // 1. BASE INITIALIZATION
  // ------------------------------------------------------------------------
  // A leaf node with no children has 0 downward path length.
  dp[u][ROOT_AS_START] = 0;
  dp[u][GOES_THROUGH_ROOT] = 0;

  // Stores the top 2 longest downward branches from children:
  // best.first  = longest branch length
  // best.second = second longest branch length
  // Initialized to -1 to represent "no branch yet".
  pll best = {-1, -1};

  // ------------------------------------------------------------------------
  // 2. POST-ORDER DFS & CHILD BRANCH COLLECTION
  // ------------------------------------------------------------------------
  for (const auto& p : graph[u]) {
    int v = p.first;
    if (v == parent) continue; // Do not traverse back up to parent!

    ll dist = p.second; // Edge weight between u and child v

    // Step 2a: Recursively solve child 'v' completely before inspecting it
    dfs(v, u, graph, dp, max_diameter);

    // Step 2b: A branch going into child 'v' connects edge (u, v) with
    // the single longest downward path starting from child 'v'.
    ll vu_dist = dp[v][ROOT_AS_START] + dist;

    // Step 2c: Update the top 2 longest branches among all children of u
    update_top2(best, vu_dist);
  }

  // ------------------------------------------------------------------------
  // 3. EVALUATE THE TWO OPTIONS AT NODE 'u'
  // ------------------------------------------------------------------------
  // Check if at least ONE child exists (Bitwise trick: ~(-1) == 0, valid >= 0)
  if (~best.first) { 
    // Option 1: Path starts at 'u' and takes the single longest branch down
    dp[u][ROOT_AS_START] = std::max(dp[u][ROOT_AS_START], best.first);

    // Check if at least TWO distinct children exist
    if (~best.second) {
      // Option 2: Path peaks at 'u', connecting the two longest branches!
      // child_1 -> ... -> u -> ... -> child_2
      dp[u][GOES_THROUGH_ROOT] = std::max(dp[u][GOES_THROUGH_ROOT], best.first + best.second);
    }
  }

  // ------------------------------------------------------------------------
  // 4. UPDATE GLOBAL DIAMETER
  // ------------------------------------------------------------------------
  // The true diameter of the tree could peak at this node 'u'!
  // We compare both options against the current global best.
  max_diameter = std::max({max_diameter, dp[u][ROOT_AS_START], dp[u][GOES_THROUGH_ROOT]});
}


void solve_and_reset(vvpil& graph, int root) {

  vvll dp(MAX_VILLAGES, vll(2, 0));

  ll max_diameter = 0;
  dfs(root, -1, graph, dp, max_diameter);

  printf("%lld\n", max_diameter);

  root = 1;
  // PROPER RESET: Clear only the inner lists!
  // This retains the outer size and capacity without crashing.
  for (int i = 0; i < MAX_VILLAGES; ++i) {
    graph[i].clear();
  }
}


namespace algorithms::onlinejudge::advanced_topics::roads_in_the_north
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

        int u, v; ll w, root = 1;
        std::string line;
        vvpil graph(MAX_VILLAGES);
        bool has_data = false;
        bool is_root_set = false;
        // The main loop reads every line in the input
        while(std::getline(std::cin, line)) {  
          // --- End-of-Case Condition ---
          if(line.empty()) {
            solve_and_reset(graph, root);
            is_root_set = false;
            continue; // Move to the next line
          }
          // --- Parse the line ---
          std::stringstream ss(line);
          if (ss >> u >> v >> w) {
            if(!is_root_set) {
              root = u;
              is_root_set = true;
            }
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
            has_data = true;
          }
        }

        // --- THE CRUCIAL FIX ---
        // After the loop ends, the last test case is still in the 'roads' buffer.
        // We must process it here.
        if(has_data) {
          solve_and_reset(graph, root);
        }
    }
}