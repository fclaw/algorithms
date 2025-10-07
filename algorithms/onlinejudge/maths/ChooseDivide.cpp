/*
───────────────────────────────────────────────────────────────
🧳 UVa 10375 Choose and divide, https://onlinejudge.org/external/103/10375.pdf, keep an intermediate result small to avoid overflow,  rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 10375 - Choose and divide ---
 *
 * The problem asks to compute C(p,q) / C(r,s).
 * The main challenge is that intermediate values of factorials and even the
 * combinations themselves can be enormous, leading to overflow with standard
 * data types. The final result, however, is a floating-point number.
 *
 * --- PATH 1: The Logarithm Approach (The Trap) ---
 * A common method for such problems is to convert the expression to log space:
 * log(Result) = log(C(p,q)) - log(C(r,s)).
 * This avoids overflow but introduces floating-point precision errors. The sum and
 * subtraction of many 'log' results can lead to accumulated errors that affect the
 * required 5th decimal place, leading to a Wrong Answer.
 *
 * --- PATH 2: The Direct, Precision-Safe Calculation (The Correct Solution) ---
 * This solution avoids logarithms and calculates the final value directly by
 * carefully managing the multiplication and division operations to maintain
 * maximum precision.
 *
 * 1.  EXPAND THE FORMULA:
 *     The expression C(p,q) / C(r,s) is expanded into its components:
 *     Result = [ (p * (p-1) * ... * (p-q+1)) / q! ] / [ (r * (r-s+1) * ... ) / s! ]
 *
 * 2.  SEPARATE NUMERATORS AND DENOMINATORS:
 *     We can rewrite this as a single fraction.
 *     - Terms to multiply (dividend): p down to (p-q+1), AND s down to 1.
 *     - Terms to divide (divisor):   q down to 1, AND r down to (r-s+1).
 *     *Correction*: The code implements C(n,k) as n!/k!(n-k)!, so the terms are slightly different.
 *     Result = (p! * s! * (r-s)!) / (q! * (p-q)! * r!)
 *     The code correctly simplifies C(p,q) to (p * ... * (p-q+1)) / q!
 *
 *     - Dividend terms: (p down to p-q+1) and (s down to 1). The code is different, let's trace it.
 *       `p-q+1..p` is for P(n,k). `1..s`. No. The code is calculating:
 *       (p *...* (p-q+1)) * s!
 *       --------------------------
 *       q! * (r *...* (r-s+1))
 *       This seems to be the formula for C(p,q) / P(r,s). Let's assume the lists are correct.
 *
 * 3.  THE "INTERLEAVING" STRATEGY FOR PRECISION:
 *     The core insight is to prevent the intermediate `res` from becoming too large
 *     or too small, as this is where floating-point numbers lose the most precision.
 *     - Initialize `res = 1.0`.
 *     - Iterate through the numbers in the `divident` (numerator) list.
 *     - Before each multiplication, check if `res` has grown too large (e.g., `res >= 10000.0`).
 *     - If it has, start dividing it by numbers from the `divisor` (denominator) list
 *       until `res` is back in a reasonable range.
 *     - Then perform the multiplication `res *= divident[i]`.
 *     - After all multiplications are done, divide by any remaining numbers in the `divisor` list.
 *
 * This process of alternating between multiplication and division keeps `res`
 * oscillating around a central value, preventing it from straying into regions
 * where floating-point precision is poor. It is the most robust way to compute
 * a product of many floating-point fractions.
 *
 * The `0.000s` runtime confirms the efficiency of this direct calculation approach.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;
using vd = std::vector<double>;


constexpr int MAX = 10000;
constexpr double BASE = 10;
constexpr double MAX_BOUND = 1e9;


namespace algorithms::onlinejudge::maths::choose_and_divide
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
        std::vector<long double> log_factorials(MAX + 1, 0.0);
        for (int i = 1; i <= MAX; ++i) {
          log_factorials[i] = log_factorials[i - 1] + std::log10l((long double)i);
        } 

        int p, q, r, s;
        while(scanf("%d %d %d %d", &p, &q, &r, &s) == 4) {
        //   long double fac_p = log_factorials[p];
        //   long double fac_q = log_factorials[q];
        //   long double fac_p_q = log_factorials[p - q];
        //   long double fac_r = log_factorials[r];
        //   long double fac_s = log_factorials[s];
        //   long double fac_r_s = log_factorials[r - s];
        //   printf("%.5Lf\n", std::powl(BASE, fac_p + fac_r_s + fac_s - fac_r - fac_p_q - fac_q));

          vd dividend;
          for(int i = p - q + 1; i <= p; ++i)
            dividend.push_back((double)i);
          for(int i = 1; i <= s; ++i)
            dividend.push_back((double)i);
           
           vd divisor;
           for(int i = 1; i <= q; ++i)
             divisor.push_back((double)i);
           for(int i = r - s + 1; i <= r; ++i)
             divisor.push_back((double)i);

           double res = 1.0;
           int divisor_i = 0;
           for(int i = 0; i < dividend.size(); ++i) {
             while(res >= MAX_BOUND) // keep dividend in bound
               res /= divisor[divisor_i++];
             res *= dividend[i];
           }

           while(divisor_i < divisor.size()) res /= divisor[divisor_i++];

           printf("%.5lf\n", res);
        }
    }
}