
 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 11159 Factors and Multiples, MIS, but answer is the MCBM,  rt: s
 ───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: UVa 11159 - Factors and Multiples
 * =====================================================================================
 *
 * This problem asks for the minimum number of integers to remove from two sets, A and B,
 * such that no remaining number in B is a multiple of any remaining number in A.
 * At first glance, this is a complex optimization problem. The key is to correctly
 * model it using graph theory, which reveals a direct path to an efficient solution.
 *
 * --- Step 1: Re-framing as a Minimum Vertex Cover Problem ---
 *
 * The core of the problem is a set of "conflicts." A conflict exists between a number
 * `a` from set A and `b` from set B if `b % a == 0`. We want to eliminate all such
 * conflicts by removing the minimum number of numbers (from A or B).
 *
 * This is a perfect mapping to the MINIMUM VERTEX COVER (MVC) problem:
 *   - The numbers in sets A and B are the VERTICES of a graph.
 *   - The "conflicts" are the EDGES of the graph.
 *   - Removing a number is equivalent to removing a VERTEX.
 *   - The goal is to select the minimum number of vertices such that every edge is
 *     "touched" or "covered" by at least one selected vertex.
 *
 * --- Step 2: Recognizing the Bipartite Structure ---
 *
 * The graph we've defined has a special structure. Edges only exist between numbers
 * from set A and numbers from set B. There are no edges connecting two numbers within
 * set A, or two numbers within set B. This is the definition of a BIPARTITE GRAPH.
 *   - Left Set (L): The `n` numbers from set A.
 *   - Right Set (R): The `m` numbers from set B.
 *
 * The problem is now: "Find the size of the MVC on a Bipartite Graph."
 *
 * --- Step 3: The "Dual" Problem - Maximum Independent Set (MIS) ---
 *
 * An alternative way to view the problem is to ask: "What is the maximum number
 * of elements we can KEEP such that no conflicts exist?" A set of vertices with
 * no edges between them is an INDEPENDENT SET. This dual view frames the problem
 * as finding the MAXIMUM INDEPENDENT SET (MIS).
 *
 * By Gallai's Identity, for any graph: `Size(MIS) + Size(MVC) = |V|`.
 * This means `Size(MVC) = |V| - Size(MIS)`. Maximizing the "keeps" (MIS) is the
 * same as minimizing the "removals" (MVC).
 *
 * --- Step 4: The Final Leap - Konig's Theorem and MCBM ---
 *
 * Finding MVC or MIS is NP-hard for general graphs. However, for BIPARTITE graphs,
 * there is a powerful shortcut provided by Konig's Theorem:
 *
 *     Size(Minimum Vertex Cover) = Size(Maximum Cardinality Bipartite Matching)
 *
 * This is the crucial insight. Instead of solving the difficult MVC problem directly,
 * we can solve for the MAXIMUM CARDINALITY BIPARTITE MATCHING (MCBM), for which
 * efficient polynomial-time algorithms (like the augmenting path method) exist.
 *
 * The size of the MCBM is our final answer. It directly gives us the size of the
 * MVC, which is the minimum number of elements we need to remove.
 *
 */

#include "../debug.h"
#include "../../aux.h"
#include "tools/mcbm.cpp"
#include <bits/stdc++.h>


namespace mcmb = algorithms::onlinejudge::graph::tools::mcmb;


using vi = std::vector<int>;

/**
 * Checks if 'p' is a multiple of 'q' according to the problem's definition.
 * p = K * q for some integer K.
 */
bool is_multiple(int p, int q) {
    // Case 1: The factor 'q' is 0
    // Case 2: The factor 'q' is non-zero.
    return (q == 0 && p == 0) || (q != 0 && p % q == 0);
}


namespace algorithms::onlinejudge::graph::factors_and_multiples
{
    /** https://onlinejudge.org/external/111/11159.pdf */
    int t_cases, t_case = 1, factors_n, multiplies_n;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(factors_n);
          vi factors(factors_n);
          for(int fac = 0; fac < factors_n; ++fac)
            while_read(factors[fac]);
          while_read(multiplies_n);
          vi multiplies(multiplies_n);
          for(int mul = 0; mul < multiplies_n; ++mul)
            while_read(multiplies[mul]);
          
          mcmb::vvi graph(factors_n);
          for(int factor_id = 0; factor_id < factors_n; ++factor_id) {
            for(int multiply_id = 0; multiply_id < multiplies_n; ++multiply_id) {
              int factor = factors[factor_id];
              int multiply = multiplies[multiply_id];
              if(is_multiple(multiply, factor)) {
                graph[factor_id].push_back(multiply_id);
              }
            }

          }

          int L_SIZE = factors_n;
          int R_SIZE = multiplies_n;
          int min_removals = 0;
          mcmb::kuhn kuhn_s(R_SIZE);
          for(int factor_id = 0; factor_id < L_SIZE; ++factor_id) {
            kuhn_s.visited.assign(L_SIZE, false);
            bool is_matched = mcmb::try_kuhn(factor_id, graph, kuhn_s);
            if(is_matched) min_removals++;
          }

          // By Gallai's Identity, for any graph: `Size(MIS) + Size(MVC) = |V|`
          printf("Case %d: %d\n", t_case++, min_removals);
        }
    }
}