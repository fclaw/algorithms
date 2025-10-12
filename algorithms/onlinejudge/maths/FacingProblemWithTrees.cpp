/*
───────────────────────────────────────────────────────────────
🧳 UVa 10643 Facing Problem With Trees, https://onlinejudge.org/external/106/10643.pdf, rt: s
───────────────────────────────────────────────────────────────
 * SOLUTION EXPLANATION for UVa 10643 - Facing Problem With Trees
 * 
 * This problem is a complex combinatorial counting problem that requires Dynamic Programming
 * and BigInteger arithmetic. The solution was developed in two main phases:
 * 1. Deconstructing the mathematical structure of the problem.
 * 2. Engineering an efficient implementation to handle the large constraints.
 *
 * -------------------------------------------------------------------------------------
 * Part 1: The Combinatorial Insight & Problem Decomposition
 * -------------------------------------------------------------------------------------
 *
 * 1.1. Spotting the Catalan Numbers:
 * The first clue is the problem's constraint that every node has an out-degree of either
 * 0 (a leaf) or 2 (an internal node). This is the definition of a standard ordered
 * binary tree. The number of such trees with 'k' internal nodes is the k-th Catalan
 * number, C_k. This tells us that Catalan numbers are the fundamental building blocks.
 *
 * 1.2. The Core Decomposition Model ("Nodes at Root" and "Pool of Triangles"):
 * The problem involves trees with 'm' edges. In a binary tree, 'm' edges correspond to
 * n = m/2 internal nodes. We can think of these 'n' nodes as "triangles" that need to
 * be arranged.
 *
 * The main constraint is that the root must have an even out-degree, 'e'. This is the
 * key to decomposing the problem. We can solve the problem by summing up the solutions
 * for every possible even out-degree 'e' of the root (from e=2 to e=m).
 *
 * For a given out-degree 'e', the root connects to 'e' children subtrees. This uses up
 * 'e' edges. The remaining 'm - e' edges must be distributed among these 'e' subtrees.
 * This translates to a "pool" of t = (m - e) / 2 "triangles" that must be distributed
 * among the 'e' children.
 *
 * This reframes the entire problem into a series of subproblems:
 * "For a given 'e' and 't', what is the total number of ways to distribute 't' triangles
 * among 'e' children, where each child subtree is itself a valid Catalan-numbered structure?"
 *
 * 1.3. The DP Recurrence (Sum over Partitions):
 * This distribution problem is a classic DP problem. We define a function:
 *   countTrees(nodes, triangles) = Number of ways to distribute 'triangles' among 'nodes' children.
 *
 * The recurrence is found by considering the first child: we can give it 'i' triangles
 * (where 0 <= i <= triangles), and then recursively solve for the remaining (nodes-1) children
 * and (triangles-i) triangles. The number of ways to form the first child's subtree is C_i.
 * This leads to the recurrence:
 *   countTrees(n, t) = Σ [ C_i * countTrees(n-1, t-i) ] for i from 0 to t.
 *
 * This recurrence implicitly calculates and sums over all integer partitions of 't'.
 *
 * -------------------------------------------------------------------------------------
 * Part 2: The Implementation and Optimization Strategy
 * -------------------------------------------------------------------------------------
 *
 * 2.1. The Ineffectiveness of the initial C++ BigInt Implementation:
 * The constraints (m <= 500) mean that n can be up to 250. The Catalan number C_250 and
 * the final answers have over 150 digits, making standard 64-bit integers useless.
 * A custom BigInt class is required.
 *
 * The initial C++ implementation was extremely slow (42s) and used a massive amount of
 * memory (6.8 GB). This was due to two primary flaws in the BigInt class design:
 *
 *   a) Memory Inefficiency: The class likely used a large, fixed-size buffer (e.g.,
 *      char array[200]) for every single number. When creating memoization tables of
 *      hundreds of thousands of these objects, this led to gigabytes of wasted memory.
 *      A correct implementation (like Java's BigInteger) only allocates as much memory
 *      as a number actually needs.
 *
 *   b) Time Inefficiency: The multiplication was likely a naive O(D^2) schoolbook
 *      algorithm on a base-10 representation (where D is the number of digits). This is
 *      very slow. A huge speedup is achieved by using a larger base (e.g., 10^9), which
 *      drastically reduces 'D'. Java's BigInteger is highly optimized, using these
 *      techniques and even faster algorithms like Karatsuba multiplication internally.
 *
 * The switch to Java's native, battle-tested BigInteger solved both problems instantly.
 *
 * 2.2. Global Memoization for Overlapping Subproblems:
 * A crucial optimization is realizing that a subproblem like countTrees(4, 2) is the
 * same regardless of the initial 'm'. The DP memoization table MUST be global (static in Java)
 * and computed once. This allows results calculated for an early test case (e.g., m=8)
 * to be reused instantly for a later, larger test case (e.g., m=500), which is the key
 * to passing the time limit. Creating a new memo table for each test case is too slow.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class



namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;
namespace bg = algorithms::onlinejudge::maths::utility::big_integer;
namespace mp = boost::multiprecision;

using ull = unsigned long long;
using v_bg = std::vector<mp::cpp_int>;
using vv_bg = std::vector<v_bg>;


constexpr int MAX_CAT = 250;
constexpr int MAX_NODES = 500;
constexpr int MAX_TRIANGLES = 250;


mp::cpp_int sentinel = mp::cpp_int(-1);

// You'll need a memoization table (a 2D vector of bigint)
// to store the results of count_trees to avoid re-computation.
mp::cpp_int count_trees(int nodes, int triangles, const v_bg& catalans, vv_bg& memo) {
  // Base Cases
  if(triangles == 0) return 1; // 0 triangles can be distributed in 1 way (all leaves)
  if(nodes == 0) return 0; // Cannot distribute triangles if there are no children
    
  // Check memoization table
  if(memo[nodes][triangles] != sentinel) { // Assuming -1 is your sentinel value
    return memo[nodes][triangles];
  }

  mp::cpp_int total_ways = 0;    
  //Recursive step: Iterate over the number of triangles given to the 'first' of the 'nodes' children
  for(int i = 0; i <= triangles; ++i) {
    // Ways for first child (with i triangles) * Ways for the rest (nodes-1 children, triangles-i triangles)
    total_ways += catalans[i] * count_trees(nodes - 1, triangles - i, catalans, memo);
  }

  // Store and return result
  return  memo[nodes][triangles] = total_ways;
}

namespace algorithms::onlinejudge::maths::facing_problem_with_trees
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

        // pre-compute catalans
        v_bg catalans = arithmetics::catalan_all_boost_bigint(MAX_CAT);
        vv_bg memo(MAX_NODES + 1, v_bg(MAX_TRIANGLES + 1, sentinel)); // global memo
   
        int t_cases, edges, t_case = 1;
        scanf("%d", &t_cases);
        while (t_cases--) {
          scanf("%d", &edges);
          mp::cpp_int ans = 0; // // Start with the t=0 (e=edges) case
          int max_triangles = edges / 2;
          for(int t = 0; t <= max_triangles; ++t) {
            int nodes = edges - 2 * t;
            ans += count_trees(nodes, t, catalans, memo);
          }
          printf("Case %d: %s\n", t_case++, ans.str().c_str());
        }
    }
}