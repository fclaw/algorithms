/* courtesy of https://github.com/stevenhalim/cpbook-code/blob/master/ch4/mcbm.cpp 
 * =====================================================================================
 * ALGORITHMIC STRATEGY: Kuhn's Algorithm for Bipartite Matching
 * =====================================================================================
 *
 * This problem is a classic application of Maximum Cardinality Bipartite Matching (MCBM).
 * The solution uses Kuhn's algorithm, which is an efficient implementation of the
 * augmenting path method, typically realized with a Depth-First Search (DFS).
 *
 * --- The Augmenting Path Principle ---
 *
 * An augmenting path is a path in the graph that starts at an unmatched node in the
 * left set (L), ends at an unmatched node in the right set (R), and alternates
 * between edges NOT in the current matching and edges that ARE in the matching.
 * Finding and "flipping" such a path increases the matching size by exactly one.
 * The algorithm repeatedly finds and flips these paths until none remain.
 *
 * --- The Elegance of the DFS Implementation (`try_kuhn`) ---
 *
 * The brilliance of the recursive `try_kuhn` function lies in how it constructs
 * this alternating path without needing an explicit reversed graph.
 *
 * 1.  THE FORWARD EDGE (Moving L -> R):
 *     The loop `for (int v : graph[u])` explores potential "forward" steps.
 *     These are edges that are NOT currently in the matching. It's a trial move
 *     from the current left-side node `u` to a right-side node `v`.
 *
 * 2.  THE "IMPLICIT" REVERSE EDGE (Moving R -> L):
 *     This is the key insight. An alternating path must follow a matched edge
 *     backwards from R to L. The recursive call `try_kuhn(match[v], ...)`
 *     achieves this beautifully and implicitly.
 *
 *       - If `v` is already matched ("saturated"), `match[v]` holds the
 *         left-side node `u_prime` that `v` is paired with.
 *       - The call `try_kuhn(u_prime, ...)` is equivalent to traversing the
 *         matched edge `(u_prime, v)` in REVERSE. It jumps back to the left
 *         side to continue the search for the rest of the alternating path.
 *
 * The DFS call stack, therefore, naturally builds the augmenting path by chaining
 * these explicit forward traversals and implicit reverse "jumps" until it either
 * finds an unmatched node in R (success) or exhausts all possibilities (failure).
 *
 */


#pragma once

#include <bits/stdc++.h>


namespace algorithms::onlinejudge::graph::tools::mcmb
{
    using vi = std::vector<int>;
    using vvi = std::vector<vi>;
    using vb = std::vector<bool>;
    struct kuhn
    {
        // k - the number of vertices in the right set
        int k;
        // total number of vertices in the graph
        int v;
        vi match;
        vb visited;
        kuhn(int k) : k(k), match(k, -1) {}
    };

    // Function to find a matching in a bipartite graph using the Kuhn algorithm
    // Returns true if a matching for v is found, false otherwise
    bool try_kuhn(int v, const vvi& graph, kuhn& kuhn_s) {
      if(kuhn_s.visited[v]) 
        return false;
      kuhn_s.visited[v] = true;
      for(int to : graph[v]) {
        if(kuhn_s.match[to] == -1 ||
           try_kuhn(kuhn_s.match[to], graph, kuhn_s)) {
          kuhn_s.match[to] = v;
          return true;
        }
      }
      return false;
    }
}