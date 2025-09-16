
/*
───────────────────────────────────────────────────────────────
🧳 UVa 106 Fermat vs. Pythagoras, https://onlinejudge.org/external/1/106.pdf,  rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 *
 * --- Algorithmic Insight: The Epitome of Boundary Handling ---
 *
 * This solution generates Pythagorean triples using Euclid's formula. While the formula
 * itself is straightforward, the main challenge lies in iterating through the
 * generators `m` and `n` efficiently. A naive search would be too slow. The loop
 * structure here is the epitome of how to handle the boundaries of the search space
 * to eliminate redundant or invalid checks.
 *
 * Let the problem be finding triples (a,b,c) where a,b,c <= N.
 * The generators are `m > k > 0`. The hypotenuse is `c = m^2 + k^2`.
 *
 *
 * ### Insight 1: Bounding the Outer Loop (`m`) ###
 *
 * The largest component of a primitive triple is the hypotenuse `c = m^2 + k^2`.
 * Since we require `c <= N`, it must be that `m^2 < N`.
 * This gives us a tight upper bound for the outer loop: `m <= sqrt(N)`.
 * By iterating `m` only up to `sqrt(N)`, we drastically reduce the search space from
 * a naive O(N^2) to a much more manageable O(N).
 *
 *
 * ### Insight 2: Bounding the Inner Loop (`n` or `k`) ###
 *
 * For a fixed `m`, the largest component `c = m^2 + n^2` grows with `n`.
 * We can stop iterating `n` as soon as `m^2 + n^2 > N`.
 * The implementation `if(c > num) break;` achieves this, pruning the search for
 * each `m` as early as possible.
 *
 * A further optimization used in some versions is to note that the leg `b = 2*m*n`
 * must also be `<= N`. Since `n > m`, we know `2*m*m < 2*m*n <= N`, which gives a
 * rough lower bound on `m`. The code `if (2 * m * n > num) break;` is another
 * effective pruning step.
 *
 *
 * ### Insight 3: Efficiently Enforcing Generator Properties (`n += 2`) ###
 *
 * Euclid's formula for *primitive* triples requires that the generators `m` and `n`:
 *   1. Are coprime (`gcd(m, n) == 1`).
 *   2. Have opposite parity (one is even, one is odd).
 *
 * The `gcd` check is done explicitly. The opposite parity check is handled with
 * exceptional elegance by the loop structure: `for(ull n = m + 1; ; n += 2)`.
 *
 *   - If `m` is odd, `n` starts at `m+1` (which is even) and increments by 2,
 *     ensuring `n` always remains even.
 *   - If `m` is even, `n` starts at `m+1` (which is odd) and increments by 2,
 *     ensuring `n` always remains odd.
 *
 * This structure bakes the opposite-parity constraint directly into the loop,
 * avoiding a separate `if` check inside and halving the number of `n` values
 * that need to be tested.
 *
 * This careful, multi-layered approach to bounding the search is what makes the
 * algorithm both correct and highly efficient.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>




namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using ll = long long;
using ull = unsigned long long;

auto ___gcd = arithmetics::__gcd<ull>;

constexpr int MAX_NUM = 1000001;


namespace algorithms::onlinejudge::maths::Fermat_vs_Pythagoras
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
        

        ull num;
        while(scanf("%llu", &num) == 1) {
          // 'used' array to track which numbers (1..num) are part of any triple.
          // The second part of the problem asks for the count of numbers NOT used.
          std::vector<ull> used(MAX_NUM, false);
          // 'prime_triples' will count the number of PRIMITIVE triples found.
          ull prime_triples = 0;
          // 'taken' will count the unique numbers that are part of any triple.
          ull taken = 0;
          // --- Euclid's Formula for Primitive Pythagorean Triples ---
          // The formula generates a triple (a,b,c) from two integers m and n.
          // We iterate through possible generators m and n to find all primitive triples
          // where all components (a,b,c) are less than or equal to 'num'.
          // Let's analyze the loop bounds for the generators 'm' and 'n'.
          // Let's assume the text meant m<n as is standard. Your code uses m<n as well.
          // The hypotenuse c = m*m + n*n. Since c <= num, we know m*m < num and n*n < num.
          // This means the upper bound for both m and n is roughly sqrt(num).
          ull bound = std::ceil(std::sqrt(num));
          for(ull m = 1; m <= bound; ++m) {
            // Iterate through the second generator 'n'.
            // Your loop condition 2*m*n <= num is an optimization for one of the legs, 'b'.
            // Your n += 2 step is a clever way to ensure that m and n have different parity.
            // If m is odd, n starts at m+1 (even) and increments by 2 (stays even).
            // If m is even, n starts at m+1 (odd) and increments by 2 (stays odd).
            for(ull n = m + 1; 2 * m * n <= num; n += 2) {
              // Per the definition, for a triple to be PRIMITIVE, its generators
              // 'm' and 'n' must be coprime.
              if(__gcd(m, n) == 1) {
                ull a = n * n - m * m;
                ull b = 2 * m * n;
                ull c = m * m + n * n;
                if(c <= (ull)num) {
                  prime_triples++;
                  if(!used[a]) { taken++; used[a] = true; }
                  if(!used[b]) { taken++; used[b] = true; }
                  if(!used[c]) { taken++; used[c] = true; }

                  // As the definition states, "If (a,b,c) is a Pythagorean triple, all
                  // triples of the form (ka,kb,kc) are also Pythagorean triples where k > 1."
                  // We must now find and mark all multiples of our primitive triple
                  // that are within the bound 'num'.
                  for(ull j = 2; c * j <= num; j++) {
                    if(!used[a * j]) { taken++; used[a * j] = true; }
                    if(!used[b * j]) { taken++; used[b * j] = true; }
                    if(!used[c * j]) { taken++; used[c * j] = true; }
                  }
                }
              }
            }
          }
          printf("%llu %llu\n", prime_triples, num - taken);
        }
    }
}