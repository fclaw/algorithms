/*
───────────────────────────────────────────────────────────────
🧳 UVa 10304 Optimal Binary Search Tree, https://onlinejudge.org/external/103/10304.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * KNUTH'S OPTIMIZATION (KNUTH-YAO SPEEDUP)
 * ============================================================================
 * Applicable to: Interval Dynamic Programming
 * Standard Form: dp[l][r] = min_{l <= k <= r} { dp[l][k-1] + dp[k+1][r] } + C[l][r]
 *
 * ----------------------------------------------------------------------------
 * 1. THE BOTTLENECK OF NAIVE INTERVAL DP:
 * ----------------------------------------------------------------------------
 * - State Space: O(N^2) intervals [l, r].
 * - Transitions: Searching for the optimal split/root 'k' tests every element 
 *                between l and r (an O(N) linear search per state).
 * - Total Complexity: O(N^2) states * O(N) transitions = O(N^3).
 *   On UVa 10304 (N = 250), naive O(N^3) takes ~1.880s (borderline TLE).
 *
 * ----------------------------------------------------------------------------
 * 2. THE CORE THEOREM (MONOTONICITY OF OPTIMAL SPLITS):
 * ----------------------------------------------------------------------------
 * Let opt[l][r] be the index 'k' that minimizes the DP transition for range [l, r].
 * Donald Knuth (1971) proved that if the cost function C[l][r] satisfies the
 * Quadrangle Inequality and Monotonicity, the optimal decision is monotonic:
 *
 *              opt[l][r - 1]  <=  opt[l][r]  <=  opt[l + 1][r]
 *
 * Intuition ("Center of Gravity"):
 * - Shrinking the interval from the right [l, r-1] can only shift the optimal 
 *   root to the LEFT (or keep it the same).
 * - Shrinking the interval from the left [l+1, r] can only shift the optimal 
 *   root to the RIGHT (or keep it the same).
 * - Therefore, the optimal root for [l, r] is strictly TRAPPED between the 
 *   optimal roots of its two smaller sub-intervals!
 *
 * ----------------------------------------------------------------------------
 * 3. WHY RUNTIME COLLAPSES FROM O(N^3) DOWN TO O(N^2) (TELESCOPING SUM):
 * ----------------------------------------------------------------------------
 * Instead of searching k in [l, r], we restrict the loop to:
 *          k in [ opt[l][r - 1], opt[l + 1][r] ]
 *
 * For a fixed interval length L, the total work across all starting positions 'l' is:
 *   Sum_l (opt[l + 1][l + L - 1] - opt[l][l + L - 2])
 *
 * Notice this is a TELESCOPING series:
 *   (opt[2][L] - opt[1][L-1]) + (opt[3][L+1] - opt[2][L]) + ... <= N
 *
 * For every interval length L, the inner loop executes at most O(N) times TOTAL,
 * averaging O(1) checks per state rather than O(N)!
 *
 * Total Time: (N lengths) * O(N work per length) = O(N^2).
 *
 * ----------------------------------------------------------------------------
 * 4. EMPIRICAL BENCHMARK (UVa 10304):
 * ----------------------------------------------------------------------------
 * - Pure O(N^3) Interval DP:  1.880s  (Dangerously close to 2.0s TLE)
 * - With Knuth's Optimization: 0.160s  (~12x speedup!)
 *
 * ----------------------------------------------------------------------------
 * 5. PREREQUISITE CONDITIONS (When can you use it?):
 * ----------------------------------------------------------------------------
 * 1. Quadrangle Inequality:
 *    C[a][c] + C[b][d] <= C[a][d] + C[b][c]   for all a <= b <= c <= d
 * 2. Monotonicity:
 *    C[b][c] <= C[a][d]                      for all a <= b <= c <= d
 *
 * (In OBST, C[l][r] = sum(freq[l..r]) - freq[k], which satisfies both trivially).
 * ============================================================================
 * 
int find_cost_of_OBST_bottom_up(const vi& freq, const vi& pref, int S) {
    vvi dp(S + 2, vi(S + 2, 0));
    vvi opt(S + 2, vi(S + 2, 0));

    // Base cases: intervals of length 1
    for (int i = 1; i <= S; ++i) {
        dp[i][i] = 0;
        opt[i][i] = i; // The only possible root is i itself
    }

    // Solve intervals from length 2 up to S
    for (int len = 2; len <= S; ++len) {
        for (int l = 1; l <= S - len + 1; ++l) {
            int r = l + len - 1;
            int sum_range = pref[r] - pref[l - 1];

            dp[l][r] = INT32_MAX;

            // Pure Knuth-Yao: strictly bounded, no fallback needed!
            int start_k = opt[l][r - 1];
            int end_k   = opt[l + 1][r];

            for (int k = start_k; k <= end_k; ++k) {
                int cost = sum_range - freq[k] + dp[l][k - 1] + dp[k + 1][r];
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k; // Store optimal root
                }
            }
        }
    }

    return dp[1][S];
}
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;


int cache[251][251];

int dp(int l, int r, const vi& freq, const vi& pref, vvi& optimal) {
  
  if(l > r) {
    return 0;
  }


  if(~cache[l][r]) {
    return cache[l][r];
  }

  int cost_l_r = pref[r] - pref[l - 1];
  int best = INT32_MAX;
  int root = l;
  // Knuth-Yao: Search window is tiny!
  int start_r = l; 
  if(~optimal[l][r - 1]) {
    start_r = optimal[l][r - 1];
  }
  int end_r = r;
  if(~optimal[l + 1][r]) {
    end_r = optimal[l + 1][r]; 
  }
  for(int k = start_r; k <= end_r; ++k) {
    int left_cost = dp(l, k - 1, freq, pref, optimal);
    int right_cost = dp(k + 1, r, freq, pref, optimal);
    int local = cost_l_r - freq[k] + left_cost + right_cost;
    if(best > local) {
      best = local;
      root = k;
    }
  }

  optimal[l][r] = root;
  return (cache[l][r] = best);
}


int find_cost_of_OBST(const vi& freq, const vi& pref, int S) {
  std::memset(cache, -1, sizeof cache);
  vvi optimal(S + 2, vi(S + 2, -1));
  return dp(1, S, freq, pref, optimal);
}


namespace algorithms::onlinejudge::advanced_topics::OBST
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

        int S;
        while(std::cin >> S) {
          vi freq(S + 2, 0);
          for(int i = 1; i <= S; ++i) {
            std::cin >> freq[i];
          }
          vi pref(S + 1, 0);
          pref[1] = freq[0];
          for(int i = 1; i <= S; ++i) {
            pref[i] = pref[i - 1] + freq[i]; 
          }
          printf("%d\n", find_cost_of_OBST(freq, pref, S));
        }
    }
}