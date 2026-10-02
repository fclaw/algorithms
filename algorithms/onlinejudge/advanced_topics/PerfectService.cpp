/*
───────────────────────────────────────────────────────────────
🧳 UVa 1218 Perfect Service, https://onlinejudge.org/external/12/1218.pdf, rt: s
───────────────────────────────────────────────────────────────
 * Category: Tree DP (Minimum Dominating Set variant with Exact-1 Coverage)
 *
 * ============================================================================
 * PROBLEM RULES & INVARIANTS:
 * ============================================================================
 * 1. Every machine is either a SERVER (S) or a CLIENT (C).
 * 2. SERVERS (S): Have NO restrictions on connectivity.
 *    - A server can connect to any number of servers and clients.
 * 3. CLIENTS (C): Have a STRICT QUOTA of EXACTLY ONE server neighbor!
 *    - Touching 0 servers is ILLEGAL (unserviced).
 *    - Touching >= 2 servers is ILLEGAL (over-serviced).
 *
 * ============================================================================
 * THE 4-CASE TRUTH TABLE (PARENT -> CURRENT NODE):
 * ============================================================================
 * A node's neighbor pool consists of its PARENT (above) and its CHILDREN (below).
 *
 * +------+--------+-------+--------------------+--------------------------------+---------+
 * | Case | Parent | curr  | Who Serves 'curr'? | What Are Children Allowed To Be?| DP State|
 * +------+--------+-------+--------------------+--------------------------------+---------+
 * |  1   |   S    |   S   | None (curr is S)   | Both S and C allowed freely    | State 0 |
 * |  2   |   C    |   S   | None (curr is S)   | Both S and C allowed freely    | State 0 |
 * |  3   |   S    |   C   | Parent above (S)   | ZERO S allowed! ALL must be C! | State 1 |
 * |  4   |   C    |   C   | Must be from below | EXACTLY ONE child is S, rest C | State 2 |
 * +------+--------+-------+--------------------+--------------------------------+---------+
 *
 * ============================================================================
 * THE 3-STATE COLLAPSE:
 * ============================================================================
 * Notice that Cases 1 & 2 are identical (a Server does not care what its parent is).
 * Thus, the 4 cases collapse into 3 clean DP states:
 *
 * enum State {
 *     SERVER               = 0, // Node u IS a Server
 *     CLIENT_PARENT_SERVER = 1, // Node u is a Client, served from ABOVE by parent
 *     CLIENT_PARENT_CLIENT = 2  // Node u is a Client, must be served from BELOW by 1 child
 * };
 *
 * ============================================================================
 * MATHEMATICAL TRANSITIONS (POST-ORDER DFS):
 * ============================================================================
 *
 * 1. State 0: dp[u][SERVER]
 *    - Node u is chosen as a Server (Cost = +1).
 *    - Since u is a Server, each child v can either be:
 *        * A Server: dp[v][SERVER]
 *        * A Client whose parent is a server: dp[v][CLIENT_PARENT_SERVER]
 *    Formula:
 *        dp[u][SERVER] = 1 + Sum_{v} min( dp[v][SERVER], dp[v][CLIENT_PARENT_SERVER] )
 *
 * 2. State 1: dp[u][CLIENT_PARENT_SERVER]
 *    - Node u is a Client, and its quota is ALREADY SATISFIED by parent above!
 *    - Cost = +0.
 *    - ZERO children can be Servers! (Otherwise u would touch >= 2 servers).
 *    - Every child v sees that its parent u is a Client, so all children are in State 2.
 *    Formula:
 *        dp[u][CLIENT_PARENT_SERVER] = Sum_{v} dp[v][CLIENT_PARENT_CLIENT]
 *
 * 3. State 2: dp[u][CLIENT_PARENT_CLIENT]
 *    - Node u is a Client, but parent is NOT a server. Quota NOT satisfied!
 *    - Cost = +0.
 *    - Node u MUST pick EXACTLY ONE child v* to be a Server (State 0).
 *    - All other children w != v* must remain Clients (State 2).
 *    Formula:
 *        dp[u][CLIENT_PARENT_CLIENT] = min_{v*} ( dp[v*][SERVER] + Sum_{w != v*} dp[w][CLIENT_PARENT_CLIENT] )
 *
 *    O(1) Optimization Trick:
 *    Notice that Sum_{w != v*} dp[w][CLIENT_PARENT_CLIENT] = dp[u][CLIENT_PARENT_SERVER] - dp[v*][CLIENT_PARENT_CLIENT].
 *    Therefore:
 *        dp[u][CLIENT_PARENT_CLIENT] = dp[u][CLIENT_PARENT_SERVER] + min_{v*} ( dp[v*][SERVER] - dp[v*][CLIENT_PARENT_CLIENT] )
 *
 * ============================================================================
 * ROOT EVALUATION & ANSWER:
 * ============================================================================
 * The Root of the tree has NO parent!
 * It can never be in State 1 (cannot be served by a non-existent parent).
 *
 * Therefore:
 *    Answer = min( dp[root][SERVER], dp[root][CLIENT_PARENT_CLIENT] )
 *
 * (If Answer >= INF, output -1 if impossible, though on trees a valid config exists).
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - Time Complexity:  O(N) — single-pass post-order DFS.
 * - Space Complexity: O(N) for tree adjacency and 3xN DP table.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int INF = (int)1e9;


using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int root = 1; // Root node for the tree (0-indexed)


enum State {
  SERVER               = 0, // Node u IS a Server
  CLIENT_PARENT_SERVER = 1, // Node u is a Client, served from ABOVE by parent
  CLIENT_PARENT_CLIENT = 2  // Node u is a Client, must be served from BELOW by 1 child
 };



void dfs(int u, int parent, const vvi& tree, vvi& dp) {
  dp[u][SERVER] = 1;
  dp[u][CLIENT_PARENT_SERVER] = 0;
  dp[u][CLIENT_PARENT_CLIENT] = INF;

  bool is_leaf = true;

  // ------------------------------------------------------------------------
  // Step 1: Solve children and compute State 0 & State 1
  // ------------------------------------------------------------------------
  for(int v : tree[u]) {
    if (v != parent) {
      is_leaf = false;
      dfs(v, u, tree, dp);

      // State 0: min(Server, Client served by u)
      dp[u][SERVER] += std::min(dp[v][SERVER], dp[v][CLIENT_PARENT_SERVER]);

      // State 1: Client served by parent
      dp[u][CLIENT_PARENT_SERVER] += dp[v][CLIENT_PARENT_CLIENT];
      if (dp[u][CLIENT_PARENT_SERVER] > INF) {
        dp[u][CLIENT_PARENT_SERVER] = INF; // Clamp to prevent overflow!
      }
    }
  }

  if (dp[u][SERVER] > INF) dp[u][SERVER] = INF;

  if(is_leaf) {
    return;
   }

  // ------------------------------------------------------------------------
  // Step 2: Compute State 2 safely (Pick 1 child to be Server)
  // ------------------------------------------------------------------------
  // If we make child v the server, all OTHER children must be valid State 2!
  for (int v : tree[u]) {
    if (v != parent) {
      // Child v must be capable of being a server
      if (dp[v][SERVER] >= INF) continue;

      // Sum of all OTHER children in State 2
      int other_children_cost = 0;
      bool valid = true;

      for(int other : tree[u]) {
        if(other != parent && other != v) {
          if (dp[other][CLIENT_PARENT_CLIENT] >= INF) {
            valid = false;
            break;
          }
          other_children_cost += dp[other][CLIENT_PARENT_CLIENT];
        }
      }

      if (valid) {
        dp[u][CLIENT_PARENT_CLIENT] = std::min(dp[u][CLIENT_PARENT_CLIENT], dp[v][SERVER] + other_children_cost);
      }
    }
  }
}


int get_perfect_service_number(int V, const vvi& tree) {
  if(V == 1) return 1; // If there's only one node, it must be a server    
  vvi dp(V + 1, vi(3, 0)); // dp[node][state] = min servers needed for subtree rooted at node with given state
  dfs(root, -1, tree, dp); // Start DFS from root node 0 with no parent
  return std::min(dp[root][SERVER], dp[root][CLIENT_PARENT_CLIENT]); // Return the minimum servers needed for the whole tree
}


namespace algorithms::onlinejudge::advanced_topics::perfect_service
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

        int V;
        while(std::cin >> V) {
            // Process each test case
          if(V == 0) continue; // Next test case if V is 0
          if(V == -1) break; // End of input if V is -1
          vvi tree(V + 1); // Graph representation (1-indexed)
          for(int i = 0; i < V - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);  // tree is undirected 
          }
          printf("%d\n", get_perfect_service_number(V, tree));
        }
    }
}