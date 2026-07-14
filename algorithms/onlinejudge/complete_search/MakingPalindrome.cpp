/*
───────────────────────────────────────────────────────────────
🧳 UVa 11753 Creating Palindrome, https://onlinejudge.org/external/117/11753.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM: CREATING PALINDROME (Constraint-Flipping Backtracking)
 *            (UVa 11753 - Creating Palindrome)
 * ============================================================================
 * THE DP TRAP (Why O(N^2) Dynamic Programming fails):
 * 1. Let N be the length of the integer sequence (N <= 10,000).
 * 2. A standard Edit-Distance/Palindrome DP would require a 2D table of size 
 *    N x N. This requires 10,000 x 10,000 = 100,000,000 integers (~400 MB).
 *    This will instantly trigger a Memory Limit Exceeded (MLE) on the judge.
 * 3. Furthermore, processing 10^8 states across T=100 test cases requires 
 *    10 billion operations, resulting in a severe Time Limit Exceeded (TLE).
 * 
 * THE BACKTRACKING SAVIOR (The K-Boundary Pruning):
 * -------------------------------------------------
 * The problem states that the maximum allowed difficulty (insertions) is K <= 20. 
 * If the minimum insertions exceed K, we can abort immediately.
 * 
 * We design a recursive backtracking function: `backtrack(l, r, k)` 
 * where `k` is the number of insertions made so far.
 * 
 * 1. THE NO-BRANCH MATCH:
 *    If `seq[l] == seq[r]`, the outer elements match. We do NOT branch! 
 *    We just move inward: `backtrack(l+1, r-1, k)`. This is a O(1) step that 
 *    does not grow our search tree.
 * 
 * 2. THE BRANCH ON MISMATCH:
 *    If `seq[l] != seq[r]`, we must branch. We try two paths (cost 1 each):
 *    - Insert on the left: `backtrack(l, r-1, k+1)`
 *    - Insert on the right: `backtrack(l+1, r, k+1)`
 * 
 * THE MATHEMATICAL COMPLEXITY PROOF (O(2^K)):
 * Since we only branch on mismatches, and we abort the search immediately if 
 * `k > K` (Heuristic Depth Pruning), the maximum depth of branching is strictly 
 * bounded by K.
 * 
 * With 2 choices per branch and a maximum depth of K, the total number of 
 * states visited in the worst-case is:
 *      Total Operations = O(2^K) = 2^20 ≈ 1,048,576 operations.
 * 
 * One million operations takes less than 0.002 seconds in C++, making this 
 * algorithm mathematically superior to the 400MB DP approach!
 * 
 * OVERFLOW SAFETY:
 * Because we use `INT32_MAX` as our infinity representation, doing `1 + left` 
 * would cause a signed integer overflow. We prevent this by writing an explicit 
 * branch-swapping guard to safely return `INT32_MAX` without doing the addition.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


int K;

int backtrack(const vi& seq, int l, int r, int k) {

 
  if(k > K) {
    return INT32_MAX;
  }

  if(l >= r) {
    return 0;
  }

  if(seq[l] == seq[r]) {
    return backtrack(seq, l + 1, r - 1, k);
  } else {

    int right = backtrack(seq, l + 1, r, k + 1);
    int left = backtrack(seq, l, r - 1, k + 1);
    if(left == INT32_MAX && right == INT32_MAX) {
      return INT32_MAX;
    } else if(left == INT32_MAX) {
      return 1 + right;
    } else if (right == INT32_MAX) {
      return 1 + left;
    } else return 1 + std::min(right, left);
  }
}



namespace algorithms::onlinejudge::complete_search::making_palindrome
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

        int t_cases, N, t_case = 1;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> N >> K;
          vi seq(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> seq[i];
          }
          int steps = backtrack(seq, 0, N - 1, 0);
          std::string verdict;
          if(steps == 0) {
            verdict = "Too easy";
          } else if (steps == INT32_MAX) {
            verdict = "Too difficult";
          } else {
            verdict = std::to_string(steps);
          }
          printf("Case %d: %s\n", t_case++, verdict.c_str());
        }
    }
}