/*
───────────────────────────────────────────────────────────────
🧳 UVa 12712 Pattern Locker, https://onlinejudge.org/external/127/12712.pdf,   rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 12712 - Pattern Locker ---
 *
 * The problem requires calculating the sum of permutations, Σ P(n, k) for k=m..n,
 * under a large composite modulus (MOD = 10^13 + 7).
 *
 * --- CHALLENGES & FAILED APPROACHES ---
 *
 * 1.  Modular Inverse: A standard approach is to use P(n,k) = n! / (n-k)!, which
 *     in modular arithmetic is `(fact[n] * invFact[n-k]) % MOD`.
 *     - FLAW: This approach FAILS because the modulus is not prime and shares factors
 *       (like 131) with the factorials (e.g., 144!). This means the modular
 *       multiplicative inverse does not exist for many of the required terms.
 *
 * 2.  Direct Calculation (per query): An alternative is to calculate each P(n,k) term
 *     in a loop for every test case.
 *     - FLAW: This is too slow. With N up to ~10000, this O(N^2) approach per test
 *       case results in a Time Limit Exceeded (TLE).
 *
 * --- THE ACCEPTED SOLUTION: DP Pre-computation of Permutations ---
 *
 * This solution avoids both pitfalls by pre-calculating all required permutation
 * values in a 2D DP table, which is an unconventional but brilliant approach.
 *
 * 1.  THE DP STATE:
 *     - `fact[i][j]` is defined to store the value of the product of all integers
 *       from 'i' to 'j', inclusive, under the modulus.
 *       `fact[i][j] = (j * (j-1) * ... * i) % MOD`.
 *
 * 2.  THE RECURRENCE:
 *     - The table is filled using the simple recurrence:
 *       `fact[i][j] = (j * fact[i][j-1]) % MOD`, with the base case `fact[i][i] = i`.
 *     - This pre-computation takes O(N^2) time, where N is MAX_DOTS, but it is only
 *       performed ONCE.
 *
 * 3.  ANSWERING QUERIES (O(1) per term):
 *     - The number of permutations P(n, k) is the product `n * (n-1) * ... * (n-k+1)`.
 *     - This corresponds exactly to our pre-computed value `fact[n-k+1][n]`.
 *
 * 4.  THE FINAL SUMMATION:
 *     - For each query (l, m, n), we loop k from m to n.
 *     - Inside the loop, we perform an O(1) lookup: `ways_for_k = fact[l*l - k + 1][l*l]`.
 *     - We add this to a running total, taking the modulus at each step.
 *     - Total time per query is O(n-m).
 *
 * This O(MAX^2) pre-computation + O(N) query time approach is fast enough and
 * cleverly bypasses all the mathematical traps involving modular inverses and overflows.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;
using vull = std::vector<ull>;
using vvull = std::vector<vull>;



constexpr ull MOD = 10000000000007ULL;
constexpr int MAX_DOTS = 100 * 100;


namespace algorithms::onlinejudge::maths::pattern_locker
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

        vvull fact(MAX_DOTS + 1, vull(MAX_DOTS + 1));
        for(int i = 1; i <= MAX_DOTS; i++) {
          fact[i][i] = i;
          for(int j = i + 1; j <= MAX_DOTS; j++) {
            fact[i][j] = (j * fact[i][j - 1]) % MOD;
          }
        }

        int t_cases, l, m, n, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d %d", &l, &m, &n);

          ull total_ways = 0;
          int total_dots = l * l;
          // The loop to sum up P(total_dots, k) for k from m to n.
          for(int i = m; i <= n; i++)
            total_ways = (total_ways + fact[total_dots - i + 1][total_dots]) % MOD;
          printf("Case %d: %llu\n", t_case++, total_ways);
        }
    }
}