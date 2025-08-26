/*
───────────────────────────────────────────────────────────────
🧳 UVa  UVa 913 - Joana and the Odd Numbers, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Mathematical Analysis: From Pattern to Formula ---
 *
 * The problem asks for the sum of the last three numbers on a line in a specific
 * triangular arrangement of odd numbers. The line is identified by N, the number
 * of elements it contains. A direct simulation is unnecessary; the solution lies
 * in finding a mathematical formula.
 *
 * Let the last number on the line with N elements be X. The numbers are consecutive
 * odd numbers, so the last three are (X-4), (X-2), and X.
 * Their sum is (X-4) + (X-2) + X = 3X - 6.
 *
 * The entire problem reduces to finding a formula for X.
 *
 *
 * ### Step 1: Find the Position of X ###
 *
 * To find the value of X, we first need to find its position in the global sequence
 * of all odd numbers (1, 3, 5, 7, ...). This position is equal to the total
 * count of numbers written up to and including the line with N elements.
 *
 *   - The lines are numbered k = 1, 2, 3, ...
 *   - The number of elements on line k is 1, 3, 5, ..., which is given by the
 *     formula `2k - 1`.
 *   - The total count of numbers up to line k is the sum of the first k odd numbers:
 *     1 + 3 + 5 + ... + (2k-1).
 *   - This is a well-known arithmetic series whose sum is simply k^2.
 *
 * So, the position of the last number on line k is k^2.
 *
 *
 * ### Step 2: Relate N (Input) to k (Line Number) ###
 *
 * The input N is the number of elements on the target line. We know the number
 * of elements on line k is `2k - 1`. Therefore:
 *   N = 2k - 1
 *
 * Solving for k gives us the line number for our target line:
 *   k = (N + 1) / 2
 *
 *
 * ### Step 3: Combine to Find X's Position in terms of N ###
 *
 * Now we can find the position of X using only the input N.
 *   Position = k^2 = ( (N + 1) / 2 )^2
 *
 *
 * ### Step 4: Find the Value of X ###
 *
 * The value of the p-th odd number in the sequence (1, 3, 5, ...) is given by
 * the formula `2p - 1`.
 *
 * We can find the value of X by plugging its position into this formula:
 *   X = 2 * Position - 1
 *   X = 2 * ( ( (N + 1) / 2 )^2 ) - 1
 *
 *
 * ### Step 5: Calculate the Final Sum ###
 *
 * The required sum is 3X - 6.
 *   Sum = 3 * [ 2 * ( ( (N + 1) / 2 )^2 ) - 1 ] - 6
 *   Sum = 6 * ( ( (N + 1) / 2 )^2 ) - 3 - 6
 *   Sum = 6 * ( ( (N + 1) / 2 )^2 ) - 9
 *
 * For implementation, to avoid floating point issues, let `k_val = (N + 1) / 2`.
 * The final formula is `6 * k_val * k_val - 9`.
 * Since N can be large, 64-bit integers (long long) must be used.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ll = long long;


namespace algorithms::onlinejudge::maths::Joana_and_the_Odd_Numbers
{
    /** https://onlinejudge.org/external/9/913.pdf */
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

        ll n;
        while(scanf("%lld", &n) == 1) {
          ll last_number = (n + 1) / 2;
          ll sum = 6 * last_number * last_number - 9;
          printf("%lld\n", sum);
        }          
    }
}