/*
───────────────────────────────────────────────────────────────
🧳 UVa 10555 Dead Fraction, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * Algorithm: Converting a Repeating Decimal to a Rational Number (Fraction)
 *
 * --- The Core Principle ---
 *
 * The goal is to convert a number with a repeating decimal expansion (e.g., 0.1333...)
 * into its exact fractional form (p/q). The technique is purely algebraic and relies
 * on creating a system of two equations that can be used to eliminate the infinite
 * repeating tail of the decimal.
 *
 * Any repeating decimal can be split into an integer part, a non-repeating
 * fractional part, and a repeating fractional part. The integer part can be handled
 * separately, so we focus on the fractional part.
 *
 * Let the number be `x`.
 *
 *
 * ### Step 1: Isolate the Repeating Tail ###
 *
 * We need to create two equations where the digits after the decimal point are
 * identical. This is done by multiplying `x` by appropriate powers of 10.
 *
 *   a) Create Equation A: Multiply `x` by `10^k`, where `k` is the length of the
 *      non-repeating part of the decimal. This shifts the decimal point to sit
 *      just BEFORE the repeating block begins.
 *
 *   b) Create Equation B: Multiply `x` by `10^(k+L)`, where `L` is the length of the
 *      repeating block (the repetend). This shifts the decimal point to sit
 *      just AFTER the first full cycle of the repeating block.
 *
 *
 * ### Step 2: Eliminate the Repeating Tail by Subtraction ###
 *
 * By subtracting Equation A from Equation B, the identical infinite repeating tails
 * cancel each other out perfectly, leaving a simple integer on the right side.
 *
 *   (10^(k+L) * x) - (10^k * x) = (Integer from B) - (Integer from A)
 *
 * This simplifies to:
 *   x * (10^(k+L) - 10^k) = (An integer)
 *
 *
 * ### Step 3: Solve for x and Simplify ###
 *
 * We can now solve for `x` directly, which will give us the rational number.
 *
 *   x = (Integer result from subtraction) / (10^(k+L) - 10^k)
 *
 * The final step is to simplify this fraction by dividing the numerator and the
 * denominator by their greatest common divisor (GCD).
 *
 *
 * ### Example Walkthrough: x = 0.1333... ###
 *
 * - Non-repeating part "1" has length k=1.
 * - Repeating part "3" has length L=1.
 *
 * 1.  Let x = 0.1333...
 *
 * 2.  Equation A (multiply by 10^1 = 10):
 *     10x = 1.333...
 *
 * 3.  Equation B (multiply by 10^(1+1) = 100):
 *     100x = 13.333...
 *
 * 4.  Subtract A from B:
 *     100x - 10x = 13.333... - 1.333...
 *     90x = 12
 *
 * 5.  Solve and Simplify:
 *     x = 12 / 90
 *     x = (12/6) / (90/6) = 2 / 15
 *
 * This algebraic method is robust and works for any repeating decimal.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>




using ld = long double;
using ll = long long;
using ii = std::pair<int, int>;

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


int cnt_lz(const std::string& s) {
  int cnt = 0;
  int i = 0;
  while(i < (int)s.size() && 
        s[i] == '0') 
  { cnt++; i++; }
  return cnt;
}


ii make_rational(int j, int total_digits, ll num) {
  int k = total_digits - j; // For "09", j=2, k = 2-2=0. CORRECT.
  ll ten_kj = arithmetics::power(10, total_digits);
  ll ten_j = arithmetics::power(10, j);
  ll ten_k = arithmetics::power(10, k);
  ll denom = !j ? ten_kj : ten_kj - ten_k;
  ll nom = !j ? num : num - num / ten_j;
  ll gcd = arithmetics::__gcd(denom, nom);
  return {nom / gcd, denom / gcd};
}

namespace algorithms::onlinejudge::maths::dead_fraction
{
    /** https://onlinejudge.org/external/3/332.pdf */
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
        
        std::string decimal_s;
        while(std::cin >> decimal_s && 
              decimal_s.size() > 1) {
          size_t s = decimal_s.size();      
          decimal_s.erase(s - 3);
          size_t dot_pos = decimal_s.find('.');
          auto num_s = decimal_s.substr(dot_pos + 1, s);
          int lz = cnt_lz(num_s); // can it be used (how many leading zeros)
          ll num = std::stoll(num_s);
          int digits_in_num = (int)(log10(num)) + 1;
          int total_digits = lz + digits_in_num; // For "09", total_digits = 1 + 1 = 2. CORRECT.
          
          ii rational = {INT32_MAX, INT32_MAX};
          for(int repeat_from = 1; repeat_from <= total_digits; ++repeat_from) {
            ii curr_rational = make_rational(repeat_from, total_digits, num);
            if(curr_rational.second < 
               rational.second) {
              rational = curr_rational;
            }
          }
          if(rational.first == INT32_MAX && rational.second == INT32_MAX) rational = {0, 1};
          printf("%d/%d\n", rational.first, rational.second);
        }
    }
}