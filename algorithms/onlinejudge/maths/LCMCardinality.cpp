/*
───────────────────────────────────────────────────────────────
🧳 UVa 10892 LCM Cardinality, https://onlinejudge.org/external/108/10892.pdf, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 *
 * --- Analysis: From Brute Force to a Prime Factorization Insight ---
 *
 * The problem asks us to count the number of integer pairs (a, b) such that
 * lcm(a, b) = N.
 *
 *
 * ### Path 1: The Brute-Force (Divisor Pairing) Approach ###
 *
 * A direct interpretation leads to a straightforward but slow algorithm:
 * 1. A key property is that if lcm(a, b) = N, then both 'a' and 'b' must be
 *    divisors of N.
 * 2. Generate all divisors of N. This can be done in O(sqrt(N)).
 * 3. Form every possible pair of divisors (a, b).
 * 4. For each pair, calculate their LCM using lcm(a,b) = (a*b)/gcd(a,b).
 * 5. If the result is N, increment a counter.
 *
 * While correct, this approach is too slow. The number of divisors, d(N), can be
 * large, making the O(d(N)^2) step of checking all pairs exceed the time limit.
 * This suggests a more profound insight from number theory is required.
 *
 *
 * ### Path 2: The Profound Insight (Prime Factorization) ###
 *
 * The key to a faster solution is to stop thinking about `a`, `b`, and `N` as
 * single numbers and instead consider their building blocks: their prime factors.
 *
 * Step A: The LCM Rule for Prime Factors
 * The definition of LCM via prime factorization is the core of the insight. Let:
 *   N = p₁^e₁ * p₂^e₂ * ...
 *   a = p₁^a₁ * p₂^a₂ * ...
 *   b = p₁^b₁ * p₂^b₂ * ...
 *
 * The condition `lcm(a, b) = N` is true IF AND ONLY IF for every prime `pᵢ`:
 *   max(aᵢ, bᵢ) = eᵢ
 *
 * Step B: The Independence Principle
 * The choice of exponents (a₁, b₁) for prime p₁ is completely independent of the
 * choice of exponents (a₂, b₂) for prime p₂. This allows us to solve the problem
 * for each prime separately and multiply the results.
 *
 * Step C: Counting the Exponent Pairs
 * For a single prime `p` with exponent `e` in N, we need to count the number of
 * pairs of non-negative integers (x, y) such that `max(x, y) = e` and `0<=x,y<=e`.
 *
 *   - Total possible pairs (x,y) in the range [0,e] x [0,e] is (e+1)*(e+1).
 *   - The condition `max(x,y) = e` is violated ONLY IF both x < e AND y < e.
 *   - The number of these "invalid" pairs is e * e.
 *   - Therefore, the number of valid pairs is (Total) - (Invalid)
 *     = (e+1)² - e²
 *     = (e² + 2e + 1) - e²
 *     = 2e + 1
 *
 * Step D: The Final Formula
 * The total number of *ordered* pairs (a, b) is the product of the counts for each prime:
 *   Total Ordered Pairs = (2e₁ + 1) * (2e₂ + 1) * ...
 *
 * Since the problem doesn't distinguish between (a, b) and (b, a), we adjust for
 * unordered pairs. The product above counts the single symmetric pair (N, N) once.
 * The remaining non-symmetric pairs are counted twice. The total is:
 *   (Product + 1) / 2
 *
 *
 * ### Final Algorithm & Complexity  ###
 *
 * Path 1 (Divisor Pairing) has a complexity of roughly O(d(N)^2), where d(N) is
 * the number of divisors of N. For the given constraints, the number of divisors
 * is small enough that this approach passes efficiently, with runtimes around 0.05s.
 *
 * Path 2 (Prime Factorization) is asymptotically faster with a complexity of
 * O(sqrt(N)). This is the theoretically optimal method and would be necessary if
 * the test cases included numbers with a very large number of divisors.
 *
 * The final algorithm implemented here uses the O(sqrt(N)) prime factorization
 * method, as it is more robust.
 *
 * 1. Prime factorize N to get the exponents {e₁, e₂, ...}.
 * 2. Calculate the product P = (2e₁ + 1) * (2e₂ + 1) * ...
 * 3. The answer is (P + 1) / 2.
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


using ull = unsigned long long;
using v_ull = std::vector<ull>;
using v_pull = std::vector<std::pair<ull, ull>>;
auto ___lcm = algorithms::onlinejudge::maths::utility::arithmetics::__lcm<ull>;



namespace algorithms::onlinejudge::maths::lcm_cardinality
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
        while(scanf("%llu", &num) == 1 && num) {
          v_ull divisors;
          ull bound = std::floor(std::sqrt(num));
          for(ull d = 1; d <= bound; ++d) {
            if(!(num % d)) { 
              divisors.push_back(d);
              if(num / d != d)
                divisors.push_back(num / d);
            }
          }

          size_t s = divisors.size();
          v_pull pairs;
          for(size_t i = 0; i < s; ++i)
            for(size_t j = i + 1; j < s; ++j)
              pairs.push_back({divisors[i], divisors[j]});
          
          ull num_pairs = 1;    
          for(auto& p : pairs)
            if(___lcm(p.first, p.second) == num)
             num_pairs++;
          printf("%llu %llu\n", num, num_pairs);
        }
    }
}