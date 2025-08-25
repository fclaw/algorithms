/*
───────────────────────────────────────────────────────────────
🧳 UVa 11718 Fantasy of a Summation, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Mathematical Analysis: Deriving the Closed-Form Formula ---
 *
 * The problem asks for the result of a K-nested loop, which is computationally
 * infeasible to simulate directly due to large K. We must derive a mathematical
 * formula to calculate the result in O(N log K) time.
 *
 * The code calculates: S = Sum_{i1..iK} (A[i1] + ... + A[iK]) mod MOD.
 *
 *
 * STEP 1: Deconstruct the Sum using Linearity
 *
 * The summation can be split into the sum of contributions from each term in the
 * inner parenthesis:
 * S = Sum_{i1..iK}(A[i1]) + Sum_{i1..iK}(A[i2]) + ... + Sum_{i1..iK}(A[iK])
 *
 * By symmetry, the total sum for each term is identical. Therefore:
 * S = K * [ Sum_{i1..iK}(A[i1]) ]
 *
 * Our task reduces to calculating the total contribution of just the first term, A[i1].
 *
 *
 * STEP 2: Isolate the Contribution of a Single Term (The Sketch's Logic)
 *
 * Let's analyze the multi-summation for A[i1]:
 * Total_A_i1 = Sum_{i1=0..n-1} Sum_{i2=0..n-1} ... Sum_{iK=0..n-1} (A[i1])
 *
 * As the sketch correctly identifies, the value of A[i1] depends ONLY on the
 * outermost loop variable, i1. For the K-1 inner loops (from i2 to iK), A[i1] is
 * a constant. By the distributive law, we can factor it out of the inner summations.
 *
 * Total_A_i1 = Sum_{i1=0..n-1} [ A[i1] * (Sum_{i2=0..n-1} ... Sum_{iK=0..n-1} (1)) ]
 *                                       \___________________________________/
 *                                                      ^
 *                                        This is K-1 nested summations of 1.
 *
 *
 * STEP 3: Evaluate the Constant Term
 *
 * Each of the K-1 inner summations `Sum_{ix=0..n-1} (1)` evaluates to `n`.
 * The product of these K-1 summations is n * n * ... * n (K-1 times), which is `n^(K-1)`.
 *
 * So the expression becomes:
 * Total_A_i1 = Sum_{i1=0..n-1} [ A[i1] * n^(K-1) ]
 *
 * The term `n^(K-1)` is a constant with respect to the i1 loop, so it can also be
 * factored out:
 * Total_A_i1 = n^(K-1) * Sum_{i1=0..n-1} A[i1]
 *
 *
 * STEP 4: Assemble the Final Formula
 *
 * Let `Sum_A = A[0] + A[1] + ... + A[n-1]`.
 * The total contribution from the A[i1] terms is `n^(K-1) * Sum_A`.
 *
 * Since there are K identical contributions (from A[i1], A[i2], ..., A[iK]), the
 * grand total sum S is:
 *
 * S = K * n^(K-1) * Sum_A
 *
 *
 * STEP 5: Apply Modular Arithmetic
 *
 * To prevent overflow, all calculations must be performed modulo MOD. This requires
 * modular exponentiation (for n^(K-1)) and modular multiplication.
 *
 * Final Result = ( (K % MOD) * (power(n, K-1, MOD)) * (Sum_A % MOD) ) % MOD
 *
 * This O(N + log K) approach is efficient enough for the given constraints.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ll = long long;


 ll derive_closed_form(ll n, ll k, ll mod, ll sum) {
  return ((k % mod) * (modpow(n, k - 1, mod) * (sum % mod)) % mod) % mod;
}


namespace algorithms::onlinejudge::maths::fantasy_of_summation
{
    /** https://onlinejudge.org/external/117/11718.pdf */
    int t_cases, t_case = 1;
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

        int n, k, mod;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d %d", &n, &k, &mod);
          ll sum = 0, v;
          for(int i = 1; i <= n; i++) { scanf("%lld", &v); sum += v; }
          printf("Case %d: %lld\n", t_case++, derive_closed_form((ll)n, (ll)k, (ll)mod, sum));
        }  
    }
}