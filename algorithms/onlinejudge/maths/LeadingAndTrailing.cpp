/*
───────────────────────────────────────────────────────────────
🧳 UVa 11029 Leading and Trailing, combination of logarithmic trick to get
   the first three digits and ‘big mod’ trick to get the last three digits rt: s
───────────────────────────────────────────────────────────────
 * ======================================================================================
 * THE LOGARITHMIC TRICK: Finding the First K Digits of a Huge Number
 * ======================================================================================
 *
 * THE PROBLEM:
 * How do we find the first few digits of a number X (e.g., n^exp or N!)
 * that is far too large to store in any primitive data type like `unsigned long long`?
 * For example, 2^100 is a 31-digit number. We can't compute it directly.
 *
 * THE CORE IDEA:
 * The solution lies in scientific notation and the properties of logarithms.
 * Any positive number X can be expressed as:
 *   X = m * 10^k
 * where 'm' is the mantissa (1 <= m < 10) and 'k' is an integer exponent.
 *
 * Crucially, the first digits of X are IDENTICAL to the first digits of the mantissa 'm'.
 * If we can find 'm', we have our answer.
 *
 * THE MATH EXPLAINED:
 * We use base-10 logarithms (log10) to isolate the mantissa.
 *
 * 1. Start with the equation:
 *    X = m * 10^k
 *
 * 2. Take log10 of both sides:
 *    log10(X) = log10(m * 10^k)
 *
 * 3. Apply the logarithm product rule, log(a*b) = log(a) + log(b):
 *    log10(X) = log10(m) + log10(10^k)
 *
 * 4. Apply the logarithm power rule, log(a^b) = b*log(a):
 *    log10(X) = log10(m) + k
 *
 * 5. The "Aha!" Moment:
 *    - 'k' is an integer (it's the integer part of log10(X)).
 *    - Since 1 <= m < 10, it follows that log10(1) <= log10(m) < log10(10),
 *      which means 0 <= log10(m) < 1.
 *    - Therefore, log10(m) is the FRACTIONAL part of log10(X).
 *
 * THE ALGORITHM:
 *
 * 1. Calculate L = log10(X).
 *    - For X = n^exp, use the power rule: L = exp * log10(n).
 *    - For X = N!, use the product rule: L = log10(1) + log10(2) + ... + log10(N).
 *
 * 2. Isolate the fractional part of L.
 *    frac = L - floor(L);
 *
 * 3. We now know that frac = log10(m). To find 'm', we do the inverse of log10:
 *    m = pow(10, frac);
 *    // 'm' will be a double between 1.0 and 10.0 that holds our digits.
 *
 * 4. To get the first 'k' digits as an integer, scale 'm' up and truncate.
 *    first_k_digits = floor(m * pow(10, k - 1));
 *
 * EXAMPLE: First 3 digits of 2^100
 *
 * 1. L = log10(2^100) = 100 * log10(2) ≈ 100 * 0.30103 = 30.103
 * 2. frac = 30.103 - floor(30.103) = 0.103
 * 3. m = pow(10, 0.103) ≈ 1.26765...
 * 4. To get 3 digits: floor(1.26765 * pow(10, 3-1)) = floor(126.765) = 126.
 *
 * The first 3 digits are 126.
 *
 * IMPLEMENTATION NOTE:
 * This method relies on the precision of floating-point numbers (`double` is usually
 * sufficient). For extreme precision, `long double` might be necessary.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
using ld = long double;

constexpr ll MOD = 1000;

ll get_last_3_digits(ll num, ll pow) 
{ return arith::mod_power(num, pow, MOD); }
ll get_first_3_digits(ll num, ll pow) {
  ld log_num  = static_cast<ld>(pow) * std::log10l(num);
  ld int_part = std::floor(log_num);
  ld frac_part = log_num - int_part;
  ld mantissa = std::powl(10, frac_part);
  return static_cast<ll>(mantissa * 100);
}

namespace algorithms::onlinejudge::maths::leading_and_trailing
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
       scanf("%d", &t_cases);
       while(t_cases--) {
        ll num, pow;
        scanf("%lld %lld", &num, &pow);
        ll first_3_digits = get_first_3_digits(num, pow);
        ll last_3_digits = get_last_3_digits(num, pow);
        std::string last_3_digits_s;
        if(last_3_digits > 0) {
          int d = std::floor(std::log10l((ld)last_3_digits) + 1);
          int diff = 3 - d;
          for(int i = 0; i < diff; ++i) {
            last_3_digits_s += "0";
          }
          last_3_digits_s += std::to_string(last_3_digits);
        }
        printf("%lld...%s\n", first_3_digits, last_3_digits == 0 ? "000" : last_3_digits_s.c_str());
       }
    }
}