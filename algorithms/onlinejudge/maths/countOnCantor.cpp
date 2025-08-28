/*
───────────────────────────────────────────────────────────────
🧳 UVa 264 Count on Cantor, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: An O(1) Mathematical Solution ---
 *
 * The problem asks for the N-th rational number in a sequence that traverses a 2D
 * grid of fractions in a diagonal, zig-zag pattern. A direct simulation that iterates
 * term by term is too slow (O(N)), given N can be up to 10^7.
 *
 * The elegant solution is to find a direct mathematical formula by analyzing the
 * properties of the diagonals.
 *
 *
 * ### Step 1: Identify the Role of Triangular Numbers ###
 *
 * The path is structured in diagonals. Let's number them starting from k=1.
 * - Diagonal k=1: (1/1). Contains 1 term. Total terms up to here: 1.
 * - Diagonal k=2: (1/2, 2/1). Contains 2 terms. Total terms up to here: 1+2 = 3.
 * - Diagonal k=3: (3/1, 2/2, 1/3). Contains 3 terms. Total terms up to here: 1+2+3 = 6.
 *
 * The total number of terms up to the end of the k-th diagonal is the k-th
 * triangular number, T_k = k * (k + 1) / 2.
 *
 * Our first task is to find which diagonal `k` the N-th term falls on.
 *
 *
 * ### Step 2: Find the Diagonal Number `k` ###
 *
 * We are looking for the smallest integer `k` such that the N-th term is included
 * within the first `k` diagonals. Mathematically, this is the smallest `k` for which:
 *   N <= T_k
 *   N <= k * (k + 1) / 2
 *
 * Rearranging this gives a standard quadratic inequality:
 *   2N <= k^2 + k
 *   k^2 + k - 2N >= 0
 *
 * We can find the positive root of the corresponding equation k^2 + k - 2N = 0 using
 * the quadratic formula: k = (-b ± sqrt(b^2 - 4ac)) / 2a.
 *   k_float = (-1 + sqrt(1 - 4*1*(-2N))) / 2
 *   k_float = (-1 + sqrt(1 + 8N)) / 2
 *
 * Since `k` must be the smallest integer satisfying the inequality, our answer for the
 * diagonal number is the ceiling of this floating-point result:
 *   k = ceil(k_float)
 *
 *
 * ### Step 3: Find the Term's Position Within the Diagonal ###
 *
 * Once we know the diagonal number `k`, we need to find out how many steps `pos` we
 * are into that diagonal.
 *
 * - The total number of terms BEFORE our diagonal `k` began is T_{k-1}.
 *   Terms_before = (k - 1) * k / 2
 *
 * - The position of our term N along the diagonal is therefore:
 *   pos = N - Terms_before
 *
 *
 * ### Step 4: Determine Numerator and Denominator from Parity ###
 *
 * The direction of traversal along a diagonal depends on whether `k` is even or odd.
 *
 * - If `k` is EVEN: The path moves from bottom-left to top-right.
 *   The sequence of terms is (k/1), (k-1/2), (k-2/3), ... , (1/k).
 *   The numerator starts at `k` and decreases, while the denominator starts at `1` and increases.
 *     - Numerator = k - pos + 1
 *     - Denominator = pos
 *
 * - If `k` is ODD: The path moves from top-right to bottom-left.
 *   The sequence of terms is (1/k), (2/k-1), (3/k-2), ... , (k/1).
 *   The numerator starts at `1` and increases, while the denominator starts at `k` and decreases.
 *     - Numerator = pos
 *     - Denominator = k - pos + 1
 *
 * By implementing these four steps, we can directly calculate the N-th term in O(1)
 * time per test case, avoiding any slow loops.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ii = std::pair<int, int>;

namespace algorithms::onlinejudge::maths::count_on_cantor
{
    /** https://onlinejudge.org/external/2/264.pdf */
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
         
        int term;
        while(scanf("%d", &term) == 1) {
         
           ii start = {1, 1};
           int diagonal_length = 1;
           int curr_term = 1;
           while(curr_term < term) {
            // move right
            start.second += 1;
            curr_term++;
            if(curr_term == term) goto finish;

            // move down along the diagonal
            for(int i = 1; i <= diagonal_length; ++i) {
              if(curr_term == term) goto finish;
              start.first += 1;
              start.second -= 1;
              curr_term++;
            }

            diagonal_length++;
            if(curr_term == term) goto finish;

            // move down
            start.first += 1;
            curr_term++;
            if(curr_term == term) goto finish;

            // move up along the diagonal
            for(int i = 1; i <= diagonal_length; ++i) {
              if(curr_term == term) goto finish;
              start.first -= 1;
              start.second += 1;
              curr_term++;
            }

            diagonal_length++;
            if(curr_term == term) goto finish;
           }

           finish:
           printf("TERM %d IS %d/%d\n", term, start.first, start.second);
        }
    }
}