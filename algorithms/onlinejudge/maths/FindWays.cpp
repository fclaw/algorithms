/*
───────────────────────────────────────────────────────────────
🧳 UVa 10219 Find the ways!, https://onlinejudge.org/external/102/10219.pdf, only O(1) is accepted, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 10219 - Find the ways! ---
 *
 * This problem is a masterclass in recognizing the correct mathematical tool when all
 * standard algorithmic approaches are designed to fail. The core task is to find the
 * number of decimal digits in the binomial coefficient C(n, k).
 *
 * --- PHASE 1: INITIAL ANALYSIS & ELIMINATING PATHS ---
 *
 * 1.  THE OBVIOUS GOAL: Calculate `floor(log10(C(n, k))) + 1`.
 *     The standard way to find the number of digits of a huge number X is via `log10(X)`.
 *     Using logarithm properties, this becomes:
 *     `log10(C(n,k)) = log10(n!) - log10(k!) - log10((n-k)!)`
 *
 * 2.  PATH A: Direct Computation (BigInt).
 *     - Fails because the problem hints the final answer is small, making a BigInt
 *       library unnecessary overhead and likely not the intended solution.
 *
 * 3.  PATH B: Iterative Summation of Logs (Pre-computation or On-the-fly).
 *     - The formula `log10(n!) = Σ log10(i)` for i=1 to n suggests a simple loop.
 *     - This was implemented, but resulted in a RUNTIME ERROR on the judge.
 *     - CONCLUSION: The runtime error proves that the input 'n' can be too large
 *       for any algorithm with O(n) complexity, whether for pre-computation or
 *       for calculation within a test case. The solution MUST be faster than linear time.
 *
 * --- PHASE 2: THE FORCED CONCLUSION (THE "AHA!" MOMENT) ---
 *
 * After eliminating all standard iterative and pre-computation strategies, we are
 * forced to conclude that a direct, O(1) mathematical formula is required to
 * calculate `log10(n!)` for a very large 'n'.
 *
 * This is the classic scenario for using STIRLING'S APPROXIMATION.
 *
 * --- PHASE 3: THE FINAL ALGORITHM (STIRLING'S FORMULA) ---
 *
 * 1.  STIRLING'S APPROXIMATION for ln(n!):
 *     The formula provides an excellent O(1) approximation for the natural log of a factorial:
 *     `ln(n!) ≈ n*ln(n) - n + 0.5*ln(2*π*n)`
 *
 * 2.  CONVERSION TO LOG10:
 *     We convert from natural log (ln) to base-10 log (log10) using the change of base rule:
 *     `log10(X) = ln(X) / ln(10)`.
 *     This gives: `log10(n!) ≈ (n*ln(n) - n + 0.5*ln(2*π*n)) / ln(10)`.
 *     A more direct (but equivalent) formula using log10 is:
 *     `log10(n!) ≈ n*log10(n) - n*log10(e) + 0.5*log10(2*π*n)`.
 *     where log10(e) is 1/ln(10).
 *
 * This knowledge-based approach is the only one that satisfies all constraints: it's
 * O(1) per test case, uses constant memory, and avoids all large number overflows.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

using ull = unsigned long long;

constexpr int MAX = 1000000;


namespace algorithms::onlinejudge::maths::find_ways
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

        // --- PRE-COMPUTATION is much faster ---
        // Pre-compute the log factorials (sum of logs) up to n.
        // actual constraint on the upper bound > 1m renders this approach useless
        std::vector<double> log_factorials(MAX + 1, 0.0);
        for (int i = 1; i <= MAX; ++i) {
            log_factorials[i] = log_factorials[i - 1] + std::log10((double)i);
        }

        int n, k;
        while(scanf("%d %d", &n, &k) == 2) {

          // 1. Get the log of each factorial component from the pre-computed table.
          double log_n_fact = arith::stirling(n);
          double log_k_fact = arith::stirling(k);
          double log_nk_fact = arith::stirling(n - k);

          // 2. Combine the logs to get the log of the final C(n,k) value.
          // log10(C(n,k)) = log10(n!) - log10(k!) - log10((n-k)!)
          double log_C_nk = log_n_fact - log_k_fact - log_nk_fact;
        
          // 3. Convert the final log value to the number of digits.
          // Digits = floor(log10(X)) + 1
          ull num_digits = std::floor(log_C_nk) + 1;

          printf("%llu\n", num_digits);
        }
    }
}