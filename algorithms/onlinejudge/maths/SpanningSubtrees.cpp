/*
───────────────────────────────────────────────────────────────
🧳 UVa 11597 Spanning Subtrees, https://onlinejudge.org/external/115/11597.pdf, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 11597 - Spanning Subtrees ---
 *
 * The problem asks for the maximum number of edge-disjoint spanning trees that
 * can be formed within a complete graph K_n on 'n' vertices.
 *
 * 1.  Definitions:
 *     - A Complete Graph (K_n): A graph with 'n' vertices where every vertex is
 *       connected to every other vertex.
 *     - Spanning Tree: A subgraph that connects all 'n' vertices using exactly
 *       'n - 1' edges, with no cycles.
 *     - Edge-Disjoint: No two spanning trees in our collection can share an edge.
 *
 * 2.  The Upper Bound Heuristic (The Key Insight):
 *     This problem can be simplified by considering the total "edge resources"
 *     available and the "edge cost" of each spanning tree.
 *
 *     - Total Edges Available in K_n: A complete graph has C(n, 2) edges, which
 *       is calculated as n * (n - 1) / 2.
 *
 *     - Edges Required per Spanning Tree: By definition, any spanning tree on 'n'
 *       vertices requires exactly 'n - 1' edges.
 *
 *     - The maximum possible number of trees is therefore the total number of
 *       available edges divided by the number of edges each tree consumes:
 *       
 *       Max Trees = floor( (Total Edges) / (Edges per Tree) )
 *                 = floor( (n * (n - 1) / 2) / (n - 1) )
 *
 * 3.  The Simplification and Final Formula:
 *     The '(n - 1)' terms cancel out, leaving a remarkably simple formula:
 *
 *       Max Trees = floor( n / 2 )
 *
 *     Using integer division in C++, this is simply `n / 2`.
 *
 * 4.  Mathematical Justification:
 *     While this "resource division" approach is a heuristic, it provides an
 *     upper bound that, in the specific case of complete graphs, is proven to
 *     be achievable by graph theory theorems (related to the decomposition of
 *     K_n into Hamiltonian paths). Therefore, this simple formula is correct.
 *
 * The code implements this O(1) formula directly.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;



namespace algorithms::onlinejudge::maths::spanning_sub_trees
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

        ull v; 
        int t_case = 1;
        while(scanf("%llu", &v) == 1 && v) {
          ull total_num_of_edges = v * (v - 1) / 2;
          ull edges_of_tree = v - 1;
          ull total_trees = total_num_of_edges / edges_of_tree;
          printf("Case %d: %llu\n", t_case++, total_trees);
        }
    }
}