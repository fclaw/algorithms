/*
───────────────────────────────────────────────────────────────
🧳 UVa 12022 OrderingT-shirts, https://onlinejudge.org/external/120/12022.pdf,  rt: s
   https://oeis.org/A000670: 
   Fubini numbers: number of preferential arrangements of n labeled elements; 
   or number of weak orders on n labeled elements; or number of ordered partitions of [n].
   1
   3
   13
   75
   541
   4683
───────────────────────────────────────────────────────────────
 * --- The Challenge: Comparing Semantic Equivalence of Expressions ---
 *
 * This problem, "Ordering T-shirts", requires us to count the number of UNIQUE
 * arrangements. The core challenge is that multiple different written expressions
 * can represent the exact same underlying order.
 *
 * For example, with items A, B, C:
 * - Expression 1: "A = B < C"
 * - Expression 2: "B = A < C"
 *
 * Syntactically, these are different. They use different permutations of the items.
 * However, semantically, they mean the same thing: "Items A and B are tied for
 * the smallest size, and item C is larger than both."
 *
 * To solve the problem, we need a robust way to determine if two expressions like
 * these are semantically equal.
 *
 * --- The Solution: Conversion to a Canonical Form ---
 *
 * A "canonical form" is a standard, unique representation for an object that may
 * have many other, equivalent representations. By converting two objects to their
 * canonical form, we can test for equivalence with a simple, direct comparison.
 * If their canonical forms are identical, the objects are equivalent.
 *
 * For this problem, the perfect canonical form is an "Ordered Partition".
 *
 * 1.  Ordered Partition Definition:
 *     An ordered partition is a sequence of sets, where the sets contain all the
 *     items, and the sequence of sets represents the strict ordering (<). The items
 *     within each set are considered tied (=).
 *
 * 2.  Example Conversion to Canonical Form:
 *     - "A = B < C"  ->  ({A, B}, {C})
 *       This means: "The group {A, B} comes before the group {C}".
 *     - "B = A < C"  ->  ({B, A}, {C})
 *       This means: "The group {B, A} comes before the group {C}".
 *
 * 3.  The Final Canonicalization Step:
 *     To make the form truly unique, we must enforce a standard order *within* each
 *     group. The standard is to sort the elements.
 *     - Canonical("A = B < C")  ->  ({A, B}, {C})  -> sort group {A,B} ->  ({A, B}, {C})
 *     - Canonical("B = A < C")  ->  ({B, A}, {C})  -> sort group {B,A} ->  ({A, B}, {C})
 *
 *     Now, the canonical forms are IDENTICAL. This proves the original expressions
 *     were semantically equal.
 *
 * --- Implementation: The `to_canonical` function ---
 *
 * The `to_canonical` function implements this conversion. It takes an encoded
 * expression (e.g., a vector like `{item_A, EQUAL, item_B, LESS, item_C}`) and
 * returns a `vector<vector<int>>` representing the canonical ordered partition.
 *
 * Algorithm:
 * 1.  Create an empty result `partition` (a vector of vectors).
 * 2.  Create an empty `current_group` (a vector).
 * 3.  Iterate through the expression:
 *     - Add the first item to `current_group`.
 *     - When an '=' operator is found, add the next item to `current_group`.
 *     - When a '<' operator is found:
 *         a. The current tie group is finished. Sort `current_group`.
 *         b. Push `current_group` into the `partition`.
 *         c. Clear `current_group` and add the next item to it to start a new group.
 * 4.  After the loop, sort and push the final `current_group`.
 *
 * The `is_semantically_equal(exp1, exp2)` function then simply becomes:
 * `return to_canonical(exp1) == to_canonical(exp2);`
 *
 * This robustly solves the problem of identifying equivalent arrangements.
*/

#include "../debug.h"
#include "../../aux.h"
#include "../../timeout.h"
#include <bits/stdc++.h>



constexpr int MAX_OBJ = 11;

enum Operator { EQUAL = -2,  LESS = -1 };

using ull = unsigned long long;
using v_operator = std::vector<Operator>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vull = std::vector<ull>;
using Mask = ull;
using MaskGroup = std::vector<Mask>;


v_operator operators = { EQUAL, LESS };


using TieGroup = vi;
using CanonicalForm = std::vector<TieGroup>;

CanonicalForm to_canonical(const vi& expression) {
  CanonicalForm partition;
  if (expression.empty()) {
    return partition;
  }

  // Start a new tie group with the first item.
  TieGroup current_group;
  current_group.push_back(expression[0]);

  // Iterate through the operators and the items that follow them.
  for (size_t i = 1; i < expression.size(); i += 2) {
    int op = expression[i];
    int item = expression[i + 1];

    if (op == EQUAL) {
      // This item is part of the current tie group.
      current_group.push_back(item);
    } else { // op == LESS_THAN
      // This is the end of the current tie group.
      // 1. Canonicalize the group by sorting its members.
      std::sort(current_group.begin(), current_group.end());
      // 2. Add the completed group to the partition.
      partition.push_back(current_group);
      // 3. Start a new group with the current item.
      current_group.clear();
      current_group.push_back(item);
    }
  }

  // Add the final group to the partition.
  if (!current_group.empty()) {
    std::sort(current_group.begin(), current_group.end());
    partition.push_back(current_group);
  }
    
  return partition;
}

/**
 * Checks if two expressions represent the same semantic arrangement.
 * For example, (A=B < C) is semantically equal to (B=A < C).
 */
bool is_semantically_equal(const vi& exp1, const vi& exp2) {
  // Convert both expressions to their canonical form and compare.
  return to_canonical(exp1) == to_canonical(exp2);
}


ull backtrack(ull mask, vi& exp, int n, std::set<vi>& seen) {
  if(__builtin_popcountll(mask) == n) {
    if(seen.find(exp) == seen.end()) {
      bool found = false;
      for(auto& e : seen) {
        if(is_semantically_equal(e, exp)) {
          found = true;
          break;
        }
      }
      if(!found) {
      seen.insert(exp);
      return 1;
      } else return 0;
    }
  }

  ull ways = 0;
  for(int i = 0; i < n; ++i) {
    if(!(mask & (1ULL << i))) {
      for(auto& op : operators) {
          exp.push_back(i);
          ull new_mask = mask | (1ULL << i);
          if(__builtin_popcountll(new_mask) != n) exp.push_back(op);
          ways += backtrack(mask | (1ULL << i), exp, n, seen);
          if(__builtin_popcountll(new_mask) != n) exp.pop_back();
          exp.pop_back();
      }
    }
  }
  return ways;
}


namespace algorithms::onlinejudge::maths::t_shirts
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

       vvi binominal(MAX_OBJ + 1, vi(MAX_OBJ + 1));
       for(int i = 0; i <= MAX_OBJ; i++) {
         for(int j = 0; j <= std::min(i, MAX_OBJ); j++) {
           if(j == 0 || j == i) binominal[i][j] = 1;
           else binominal[i][j] = binominal[i - 1][j - 1] + binominal[i - 1][j];
         }
       }

       // a(n) = Sum_{k=1..n} binomial(n, k)*a(n-k), a(0) = 1.
       vi dp(MAX_OBJ + 1);
       dp[0] = 1;
       for(int i = 1; i <= MAX_OBJ; ++i) {
         for(int j = 1; j <= i; ++j) {
           dp[i] += dp[i - j] * binominal[i][j];
         }
       }

       int t_cases, n;
       scanf("%d", &t_cases);
       while (t_cases--) {
         scanf("%d", &n);
        //  vi exp;
        //  std::set<vi> seen;
        //  ull mask = 0;
        //  auto ways = run_with_timeout(std::chrono::seconds(300), backtrack, mask, std::ref(exp), n, std::ref(seen));
         printf("%d\n", dp[n]);
       }
    }
}