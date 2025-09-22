/*
───────────────────────────────────────────────────────────────
🧳 UVa 10176 Ocean Deep!- Make it shallow!!, convert binary
   to decimal digit by digit; do modulo 131071 to the intermediate result, rt: s
───────────────────────────────────────────────────────────────
 * -----------------------------
 * --- PROBLEM DECONSTRUCTION ---
 * -----------------------------
 * The core task is to determine if a very large binary number, N, is divisible
 * by a given prime modulus, M = 131071. The number N can have up to 10,000 digits,
 * making it impossible to store in standard data types like `long long`.
 * This immediately signals that the solution must use modular arithmetic to keep
 * the intermediate values small.
 *
 * ---------------------------
 * --- MATHEMATICAL FOUNDATION ---
 * ---------------------------
 * Any number can be represented as a polynomial of its base. For a binary
 * number with digits b_n, b_{n-1}, ..., b_0 (from left to right), the value is:
 * N = b_n * 2^n + b_{n-1} * 2^(n-1) + ... + b_0 * 2^0
 *
 * Our goal is to compute N % M. Using the properties of modular arithmetic:
 * N % M = ( (b_n*2^n % M) + (b_{n-1}*2^(n-1) % M) + ... ) % M
 *
 * -----------------------------------------
 * --- ALGORITHMIC APPROACH: FROM NAIVE TO EFFICIENT ---
 * -----------------------------------------
 *
 * 1. The Naive O(L*log L) Approach:
 *    One could loop through the digits of the binary string (length L) and for each
 *    digit b_i, calculate its value (b_i * 2^power % M) using a modular
 *    exponentiation function (O(log L)). This would give a total time complexity of
 *    O(L * log L), which is too slow for L=10000.
 *
 * 2. The Efficient O(L) Approach (The Key Insight):
 *    Instead of calculating each term independently, we can build the result
 *    incrementally. This is an application of Horner's method for polynomial
 *    evaluation.
 *
 *    Let `rem` be the value of the binary prefix processed so far, all under modulo M.
 *    When we encounter the next bit `b`, the new value of the number is effectively
 *    (old_value * 2) + b.
 *
 *    Applying the modulus at every step, we get the update rule:
 *    `new_rem = ((current_rem * 2) + b) % M;`
 *
 *    By initializing `rem = 0` and applying this rule for each bit from left to
 *    right, we maintain the running remainder. The final value of `rem` after
 *    processing the last bit is the answer, N % M. This requires only one
 *    multiplication and one addition per digit, leading to a linear O(L) time
 *    complexity.
 *
 * --------------------------
 * --- IMPLEMENTATION DETAILS ---
 * --------------------------
 * - Input Handling: The input number can span multiple lines and is terminated
 *   by a '#' character. The most efficient way to handle this is to read the
 *   input character-by-character, updating the `remainder` on-the-fly. This
 *   "streaming" approach avoids storing the potentially huge string in memory.
 *
 * - State Variable: Only one variable, `long long remainder`, is needed to keep
 *   track of the state during the calculation for a single number. `long long` is
 *   used to prevent overflow during the `remainder * 2` step before the
 *   modulus is applied.
 *
 * - Termination: When '#' is read, the calculation for the current number is
 *   complete. We check if `remainder == 0` to print "YES" or "NO", and then
 *   reset `remainder = 0` for the next number.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
constexpr ll MOD = 131071;
constexpr char zero = '0';
constexpr char one = '1';
constexpr char terminus = '#';


namespace algorithms::onlinejudge::maths::ocean_deep
{
    /** https://onlinejudge.org/external/101/10176.pdf */
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
       
        char c;
        std::string binary;
        // This is the main loop. It reads one character at a time until the end of the file.
       while (std::cin.get(c)) {
         if(c == zero || c == one) {
           // If it's a bit, append it to our "fully loaded string"
           binary += c;
          } else if (c == terminus) {
            ll rem = 0;
            ll len = binary.size();
            for(ll exp = 0; exp < len; ++exp) {
              ll bit = binary[exp] - '0';
              ll power_of_2 = len - 1 - exp; // Correct exponent
              rem = (bit * arith::mod_power((ll)2, power_of_2, MOD) + rem % MOD) % MOD;
            }
            printf("%s\n", rem == 0 ? "YES" : "NO");
            binary.clear();
          }
       }
    }
}