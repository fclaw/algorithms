/*
───────────────────────────────────────────────────────────────
🧳 UVa 10680 LCM, https://onlinejudge.org/external/106/10680.pdf, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * Algorithm: Prime Factorization of LCM(1, 2, ..., N)
 *
 * --- The Core Mathematical Insight ---
 *
 * The problem requires finding the last non-zero digit of LCM(1, 2, ..., N).
 * The value of the LCM grows astronomically large, so we cannot compute it directly.
 * The solution is to work with the LCM's prime factorization and use modular arithmetic.
 *
 * The key is to find the exponent of each prime `p` in the factorization of the LCM.
 *
 *
 * ### Step 1: The Prime Factorization Definition of LCM ###
 *
 * The prime factorization of the Least Common Multiple (LCM) of a set of numbers is
 * constructed by taking every prime factor present in any of the numbers and raising
 * it to the HIGHEST power found among them.
 *
 * Let `L = LCM(1, 2, ..., N)`.
 * Let `E_p(k)` be the exponent of a prime `p` in the factorization of an integer `k`.
 *
 * The exponent of `p` in the factorization of `L` is given by:
 *   E_p(L) = max( E_p(1), E_p(2), ..., E_p(N) )
 *
 *
 * ### Step 2: The "Highest Prime Power" Shortcut ###
 *
 * A direct implementation of the above would require factoring every number from 1 to N,
 * which is too slow. A more profound insight simplifies the problem dramatically.
 *
 * The maximum power of a prime `p` that appears in the factorization of any number
 * `k <= N` must come from a number that is itself a power of `p`.
 *
 * Let `p^x` be the largest integer power of `p` such that `p^x <= N`.
 *   - The number `p^x` is in the set `{1, 2, ..., N}`.
 *   - The exponent of `p` in the factorization of `p^x` is `x`.
 *   - No other number `k <= N` can have a power of `p` in its factorization that is
 *     greater than `x`, because if it did (e.g., `k = m * p^(x+1)`), then `k` would
 *     be larger than `N`.
 *
 * Therefore, the maximum exponent of `p` we need for the LCM is simply the largest
 * integer `x` such that `p^x <= N`.
 *
 *
 * ### Example: Finding the power of 2 in LCM(1...20) ###
 *
 * We need to find the largest exponent `x` such that `2^x <= 20`.
 *   - 2^1 = 2  (<= 20)
 *   - 2^2 = 4  (<= 20)
 *   - 2^3 = 8  (<= 20)
 *   - 2^4 = 16 (<= 20)
 *   - 2^5 = 32 (> 20) -> Stop.
 *
 * The largest power is 4. So, the prime factorization of LCM(1...20) contains the
 * term 2^4.
 *
 *
 * ### The Final Algorithm ###
 *
 * 1. Pre-compute all prime numbers up to N using a sieve.
 * 2. To find the prime factorization of LCM(1...N):
 *    a. Create an empty map or frequency array to store the exponents.
 *    b. For each prime `p` in your list up to N:
 *       i. Find the largest integer `x` such that `p^x <= N`.
 *       ii. Store this `x` as the exponent for the prime `p`.
 *
 * This O(π(N) * log(N)) approach (where π(N) is the number of primes up to N) is
 * extremely efficient and avoids factoring every number individually.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

constexpr ll MAX = 1000000;
constexpr ll MOD = 10;
using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::lcm
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);

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
 
        ll num;
        while(scanf("%lld", &num) == 1 && num) {

          std::vector<int> lcm_factors(num + 1, 0);
           // Loop through pre-computed primes p <= num
          for (ll p : primes::p) {
            if(p > num) { break; }

            ll cp = p;
            int exp = 0;

            // Keep multiplying by p until we exceed num.
            // This avoids repeated power calculations.
            while(cp <= num) {
              exp++;
                  
              // Check for potential overflow before multiplying.
              // This is crucial for large p and num.
              if(cp > num / p) {
                break; 
               }
               cp *= p;
            }
              
            if(exp > 0) {
              lcm_factors[p] = exp;
            }
          }

          if(lcm_factors.size() >= 5) {
            ll count2 = lcm_factors[2];
            ll count5 = lcm_factors[5];
            lcm_factors[5] = 0;
            lcm_factors[2] = count2 - count5;
          }

          ll last_digit = 1;
          for(ll base = 2; base <= num; ++base) {
            ll exp = lcm_factors[base];
            ll term = arithmetics::power_mod(base, exp, MOD);
            last_digit = (last_digit * term) % MOD;
          }
 
          printf("%lld\n", last_digit);
        }
    }
}