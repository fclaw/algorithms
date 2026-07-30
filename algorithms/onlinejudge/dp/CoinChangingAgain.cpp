/*
────────────────────────────────────────────────────────────────────────────────
🧳 UVa 11259 - Coin Changing Again
   URL: https://onlinejudge.org/external/112/11259.pdf
   Verdict: Accepted | Runtime: ~0.06 0s (using O(16) Query PIE)

   Algorithmic Summary:
   
   1. The Query Bottleneck:
      We have 4 coin values (C_1, C_2, C_3, C_4). For each query, we are given 
      different coin limits (D_1, D_2, D_3, D_4) and a target value V <= 10^5.
      With up to 10^5 queries, running a bounded coin-change DP per query would 
      take O(Q * V * limit) time, resulting in a guaranteed TLE.

   2. The Precomputation Step (Unbounded DP):
      Since the 4 coin values are fixed for the entire test, we precompute a 
      standard Unbounded Coin Change DP table (allowing infinite coin reuse) 
      up to V <= 10^5 exactly once. This takes O(4 * V) time (instantaneous).

   3. The Inclusion-Exclusion Principle (PIE) Query:
      Instead of counting valid combinations directly, we invert the problem:
         Valid Ways = Total Unbounded Ways - Invalid Ways
      
      A combination is invalid if at least one coin violates its limit.
      We define a "Violation" for Coin i as using it at least D_i + 1 times.
      
      Using the Inclusion-Exclusion Principle, the number of invalid ways is the 
      union of these violations: |A_1 U A_2 U A_3 U A_4|. We calculate this in 
      exactly 2^4 = 16 steps using a bitmask (from 0 to 15):
         - If we choose an ODD number of violating coins, we SUBTRACT.
         - If we choose an EVEN number of violating coins, we ADD back.

   4. The L+1 Sufficiency Proof (Why L+1 is enough):
      A common point of confusion is why we only pre-allocate exactly L_i + 1 
      coins to force a violation, and do not need to evaluate L_i + 2, L_i + 3, etc.
      
      Mathematically, the sets of violations are nested:
         V_all_violations = V_at_least_L+1
         V_at_least_L+3  ⊂  V_at_least_L+2  ⊂  V_at_least_L+1
      
      By pre-allocating exactly (D_i + 1) * C_i, the remaining target value 
      V - (D_i + 1)*C_i can be filled with ANY additional number of coins in our 
      unbounded DP table. This unbounded lookup naturally and automatically 
      spans all cases where the coin is used L+1, L+2, L+3... times. 
      
      The alternating signs of PIE then perfectly handle and cancel out the 
      overlapping violating combinations (e.g. combinations that violate both 
      Coin 1 and Coin 2 limits are subtracted twice, then added back once).
────────────────────────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ii = std::pair<int, int>;
using ll = long long;
using vi = std::vector<int>;
using vll = std::vector<ll>;


const int N = 4;
const int MAX_V = 100000;

ll query(int V, const vi& C, const vi& D, const vll& dp) {
  ll valid_ways = 0;

  // Iterate through all 16 subsets of violating coins
  for(int set = 0; set < (1 << N); ++set) {
    ll temp_v = V;
    int active_violations = 0;

    for(int i = 0; i < N; ++i) {
      if(set & (1 << i)) {
        active_violations++;
        // Force coin i to violate its limit by pre-allocating (D[i] + 1) coins
        temp_v -= (D[C[i]] + 1) * 1LL * C[i];
      }
    }

    if(temp_v >= 0) {
      // If the number of violating coins is odd, subtract. If even, add.
      if ((active_violations % 2)) {
        valid_ways -= dp[temp_v];
      } else {
        valid_ways += dp[temp_v];
      }
    }
  }

  return valid_ways;
}


namespace algorithms::onlinejudge::dp::coin_changing_again
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



        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int queries;
          int amount;
          vi coins(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> coins[i];
          }

          // pre calculate unbounded dp
          vll dp(MAX_V + 1, 0);
          dp[0] = 1;
          for(int c : coins) {
            for(int v = c; v <= MAX_V; ++v) {
              dp[v] += dp[v - c];
            }
          }

          std::cin >> queries;
          while(queries--) {
            int target;
            vi max_allowed(coins.back() + 1, 0);
            for(int i = 0; i < N; ++i) {
              std::cin >> amount;
              max_allowed[coins[i]] = amount;
            }
            std::cin >> target;
            std::cout << query(target, coins, max_allowed, dp) << std::endl;
          }
        }
    }
}