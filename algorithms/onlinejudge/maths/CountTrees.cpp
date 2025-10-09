/*
───────────────────────────────────────────────────────────────
🧳 UVa 10007 Count the Trees, https://onlinejudge.org/external/100/10007.pdf, rt: s
───────────────────────────────────────────────────────────────
 *
 * This problem asks for the number of different LABELED ordered rooted trees
 * with N nodes.
 *
 * The solution is a two-part combinatorial insight:
 *
 * 1.  UNLABELED TREES: The number of unique SHAPES of ordered rooted trees
 *     with N nodes is given by the (N-1)-th Catalan number, C_{N-1}.
 *
 * 2.  LABELING: For any given tree shape, there are N nodes. The N distinct labels
 *     can be assigned to these N nodes in N! (N factorial) ways.
 *
 * The final formula is therefore the product of these two values:
 *   Total Ways = C_{N-1} * N!
 *
 * Since N can be up to 300, both the Catalan number and the factorial will be
 * immense, requiring the use of the BigInteger class. This solution pre-computes
 * both sequences up to the maximum N.
*/

#include "../debug.h"
#include "../../aux.h"
#include "../../timeout.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>



namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

using ll = long long;
using ull = unsigned long long;
using v_bg = std::vector<bg::bigint>;


constexpr int MAX_NODES = 300;

std::unordered_map<int, bg::bigint> memo;

bg::bigint count_ways(int nodes) {
  if(nodes == 0) return 1;

  if(memo.count(nodes)) 
    return memo[nodes];

  bg::bigint ways(0);
  // C_n = Sum C_i * C_{n-1-i}, Catalan recurrence 
  for(int i = 0; i < nodes; ++i) {
    // Break the problem into a left subtree of 'i' nodes
    // and a right subtree of 'num_nodes - 1 - i' nodes.
    ways += count_ways(i) * count_ways(nodes - 1 - i);
  }
  return memo[nodes] = ways;
}

namespace algorithms::onlinejudge::maths::count_trees
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
 
        v_bg catalans(MAX_NODES + 1);
        for(int i = 0; i <= MAX_NODES; ++i)
          catalans[i] = count_ways(i);

        int nodes;
        while(scanf("%d", &nodes) == 1 && nodes) {
          bg::bigint num(nodes);
          bg::bigint fact = num._big_fact(num);
          bg::bigint trees = catalans[nodes] * fact;
          printf("%s\n", trees.getRawRep().c_str());
        }
    }
}