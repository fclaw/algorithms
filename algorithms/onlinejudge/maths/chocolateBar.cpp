/*
───────────────────────────────────────────────────────────────
🧳 UVa 10970 Big Chocolate, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Problem-Solving Workflow: From Recurrence to Closed-Form Solution ---
 *
 * This file solves the problem using a simple O(1) mathematical formula. However,
 * this formula was not derived by a magic guess. It was discovered through a
- * rigorous process of modeling, exploring, and proving. This workflow is a powerful
 * template for solving many dynamic programming problems that hide a simpler pattern.
 *
 *
 * ### STAGE 1: COMPUTATIONAL EXPLORATION & HYPOTHESIS GENERATION ###
 *
 * The goal of this stage is to create a trusted, correct-but-slow solution and
 * use it to generate data, from which we can infer a pattern.
 *
 *
 * Step 1.1: Formalize the problem with a Recurrence Relation.
 *
 * Let C(w, h) be the minimum number of cuts to divide a w x h rectangle into
 * w*h unit squares. The cost of each cut is 1.
 *
 *   - Base Case: A 1x1 rectangle needs no cuts. C(1, 1) = 0.
 *
 *   - Recursive Step: To cut a w x h rectangle, we must make a first cut.
 *     This cut can be vertical or horizontal. The optimal solution is the minimum
 *     cost over all possible first cuts.
 *
 *     C(w, h) = 1 + min(
 *                       min_{1<=k<w} [C(k, h) + C(w-k, h)],  // Best vertical cut
 *                       min_{1<=k<h} [C(w, k) + C(w, h-k)]   // Best horizontal cut
 *                     )
 *     for w>1 or h>1.
 *
 *
 * Step 1.2: Implement the Recurrence (The "Mighty Tool").
 *
 * We implement the above recurrence directly using recursion with memoization. This
 * results in a DP solution with a time complexity of roughly O(w*h*(w+h)) or
 * O(N^5) for an N x N grid. While too slow for the problem's constraints (N<=300),
 * it is provably correct and perfect for generating data for small N.
 *
 * (See function `do_min_cutting` for an example of this implementation).
 *
 *
 * Step 1.3: Generate Data using the DP implementation.
 *
 * We run our trusted DP code on various small inputs to create a "truth table".
 *
 *   Input (w,h) | DP Output | w*h
 *   ------------|-----------|----
 *   2 x 2       | 3         | 4
 *   4 x 5       | 19        | 20
 *   4 x 6       | 23        | 24
 *   5 x 10      | 49        | 50
 *
 *
 * Step 1.4: Formulate a Hypothesis from the Data.
 *
 * By observing the generated data, a clear and simple pattern emerges. In every
 * single case, the output is one less than the product of the dimensions.
 *
 *   HYPOTHESIS: C(w, h) = w * h - 1
 *
 *
 * ### STAGE 2: MATHEMATICAL VERIFICATION ###
 *
 * The goal of this stage is to rigorously prove that our hypothesis is not a mere
 * coincidence, but the correct closed-form solution to our recurrence relation.
 *
 *
 * Step 2.1: Prove the Hypothesis using Mathematical Induction.
 *
 *   - Base Case: For w=1, h=1, our formula gives C(1,1) = 1*1 - 1 = 0. This matches
 *     the known base case. The hypothesis holds.
 *
 *   - Inductive Hypothesis (IH): Assume for any rectangle w' x h' smaller than
 *     w x h, the formula is correct: C(w', h') = w'*h' - 1.
 *
 *   - Inductive Step: We must show C(w, h) = w*h - 1. Let's analyze the cost of an
 *     arbitrary vertical cut at position k (where 1<=k<w) using our recurrence.
 *
 *     Cost_k = 1 + C(k, h) + C(w-k, h)
 *
 *     Since (k,h) and (w-k,h) represent smaller rectangles, we can apply the IH:
 *
 *     Cost_k = 1 + (k*h - 1) + ((w-k)*h - 1)
 *            = 1 + k*h - 1 + w*h - k*h - 1
 *            = w*h - 1
 *
 *   - Conclusion: The cost is w*h - 1 *regardless* of which cut `k` we choose. The
 *     same logic holds for horizontal cuts. Therefore, the `min` operation in the
 *     recurrence is redundant. The recurrence relation is definitively solved by
 *     the formula C(w, h) = w*h - 1.
 *
 *
 * FINAL ALGORITHM:
 * The problem that initially appeared to require a complex O(N^5) DP solution has
 * been proven to have a simple O(1) closed-form solution. The constraints of N<=300
 * were a strong hint that such a simplification must exist.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ii = std::pair<int, int>;


int do_min_cutting(const ii& tlp, const ii& brp, int col_size) {
  if(tlp >= brp) return 0;

  int best = INT32_MAX;

  // do vertical cuttings
  for(int c = tlp.second; c < brp.second; c++) {
    int left_cut = do_min_cutting(tlp, std::make_pair(brp.first, c), col_size);
    int right_cut = do_min_cutting(std::make_pair(tlp.first, c + 1), brp, col_size);
    best = std::min(best, 1 + left_cut + right_cut);
  }

  // do horizontal cuttings
  for(int r = tlp.first; r < brp.first; r++) {
    int top_cut = do_min_cutting(tlp, std::make_pair(r, brp.second), col_size);
    int bot_cut = do_min_cutting(std::make_pair(r + 1, tlp.second), brp, col_size);
    best = std::min(best, 1 + top_cut + bot_cut);
  }

  return best;
}


namespace algorithms::onlinejudge::maths::chocolate_bar
{
    /** https://onlinejudge.org/external/109/10970.pdf  */
    int n, m;
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
        
        while(scanf("%d %d", &n, &m) == 2) {
          printf("%d\n", n * m - 1);
        }
    }
}