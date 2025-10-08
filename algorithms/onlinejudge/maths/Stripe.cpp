/*
───────────────────────────────────────────────────────────────
🧳 UVa 10541 Stripe, https://onlinejudge.org/external/105/10541.pdf, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 10541 - Stripe ---
 *
 * This is a classic combinatorial problem that can be solved elegantly using the
 * "Stars and Bars" method. The problem asks for the number of ways to form a 1xN
 * stripe that matches a given "code" (a sequence of K blocks of black squares).
 *
 * --- PHASE 1: Deconstructing the Stripe's Structure ---
 *
 * A valid stripe consists of three types of components arranged in a line:
 * 1.  Black Blocks: There are 'K' blocks of black squares. Their sizes are given in the
 *     input. Let 'B' be the total number of black squares (sum of the code numbers).
 *
 * 2.  Mandatory Separators: Between each of the 'K' black blocks, there must be at
 *     least one white square. For 'K' blocks, this requires 'K-1' white squares to
 *     act as fixed separators. (This is not needed if K <= 1).
 *
 * 3.  "Free" White Squares: These are the remaining white squares that can be
 *     distributed anywhere to fill the rest of the stripe's length 'N'.
 *
 * The key insight is to count the number of "free" white squares.
 *   - Total black squares = B
 *   - Total mandatory separators = K - 1
 *   - "Free" white squares = N - B - (K - 1)
 *
 * --- PHASE 2: Transforming the Problem with "Stars and Bars" ---
 *
 * The problem now becomes: "In how many ways can we distribute the 'Free' white
 * squares into the available empty spaces in the stripe?"
 *
 * This is a perfect application of the Stars and Bars theorem.
 *
 * 1.  The "Stars": The items we need to distribute are the "Free" white squares. They
 *     are identical (indistinguishable).
 *     - Number of stars (n') = N - B - (K - 1)
 *
 * 2.  The "Bins": The distinct containers where we can place the stars are the
 *     potential locations for white squares. These are:
 *     - The space before the first black block.
 *     - The spaces between each of the K-1 pairs of black blocks.
 *     - The space after the last black block.
 *
 *     Visualized with K blocks (Bk):  _ B1 _ B2 _ ... _ BK _
 *     Counting these locations gives us (K-1) "inner" bins + 2 "outer" bins.
 *     - Number of bins (k') = K + 1
 *
 * --- PHASE 3: Applying the Formula ---
 *
 * The Stars and Bars formula for distributing 'n' identical items into 'k' distinct
 * bins is: C(n + k - 1, k - 1) or equivalently C(n + k - 1, n).
 *
 * Substituting our values for n' and k':
 *   - Ways = C( (N - B - (K - 1)) + (K + 1) - 1, (K + 1) - 1 )
 *
 * Let's simplify the 'n' part of C(n,r):
 *   - n = (N - B - K + 1) + (K + 1) - 1
 *   - n = N - B - K + 1 + K
 *   - n = N - B + 1
 *
 * And simplify the 'r' part:
 *   - r = (K + 1) - 1
 *   - r = K
 *
 * The Final Closed-Form Formula:
 *   - Ways = C(N - B + 1, K)
 *
 * This single formula provides the answer. Since the result can have up to 50 digits,
 * the calculation C(n,k) must be performed using a Big Integer library. The
 * constraints on N (up to 200) are small enough that a direct O(k) calculation
 * of C(n,k) = (n/1)*(n-1/2)*... is feasible.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;
namespace bg = algorithms::onlinejudge::maths::utility::big_integer;



namespace algorithms::onlinejudge::maths::stripe
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

        int t_cases, N, n_digits;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d", &N, &n_digits);
          int sum_code = 0, code;
          for(int i = 0; i < n_digits; ++i) {
            scanf("%d", &code);
            sum_code += code;
          }
          int FREE = N - sum_code - (n_digits - 1); // stars
          int BINS = n_digits + 1; // bars
          bg::bigint ways = arith::combinations_bigint(FREE + BINS - 1, BINS - 1);
          printf("%s\n", ways.getRawRep().c_str());
        }
    }
}