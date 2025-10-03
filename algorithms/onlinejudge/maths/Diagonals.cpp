/*
───────────────────────────────────────────────────────────────
🧳 UVa 10784 Diagonal, https://onlinejudge.org/external/107/10784.pdf, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem-Solving Strategy for UVa 10784 - Diagonal ---
 *
 * The problem asks for the minimum number of vertices 'n' a polygon must have
 * such that the number of its diagonals is at least 'N'.
 *
 * This is not a search problem, but rather a mathematical one that requires
 * us to "invert" the formula for the number of diagonals.
 *
 * PHASE 1: DERIVING THE FORMULA for Diagonals of an n-gon
 *
 * Our goal is to find a formula D(n) for the number of diagonals in a polygon
 * with 'n' vertices. Your derivation is the standard, elegant way to find this:
 *
 * 1.  Consider a single vertex:
 *     - An n-gon has 'n' vertices in total.
 *     - From any single vertex, you can draw a line to every other vertex.
 *     - Lines to the vertex itself are not possible.
 *     - Lines to its two adjacent vertices form the sides of the polygon, not diagonals.
 *     - Therefore, from one vertex, we can draw lines to n - 1 (itself) - 2 (neighbors)
 *       = (n - 3) other vertices. These are all diagonals.
 *
 * 2.  Consider all 'n' vertices:
 *     - Since each of the 'n' vertices can start (n - 3) diagonals, a naive
 *       first guess would be n * (n - 3).
 *
 * 3.  Correct for Double-Counting:
 *     - The process above counts each diagonal twice. The diagonal from vertex A
 *       to vertex B is the same as the diagonal from vertex B to vertex A.
 *     - To correct for this, we must divide the total by 2.
 *
 * 4.  The Closed-Form Formula:
 *     - This gives us the final, correct formula:
 *       D(n) = n * (n - 3) / 2
 *
 *
 * PHASE 2: SOLVING THE INEQUALITY for 'n'
 *
 * The problem gives us a large number 'N' and asks for the smallest integer 'n'
 * such that D(n) >= N.
 *
 *   n * (n - 3) / 2 >= N
 *
 * Rearranging this gives a quadratic inequality:
 *
 *   n^2 - 3n >= 2N
 *   n^2 - 3n - 2N >= 0
 *
 *
 * PHASE 3: FINDING 'n' EFFICIENTLY
 *
 * We need to find the smallest integer 'n' that satisfies this inequality.
 *
 * 1.  Using the Quadratic Formula:
 *     - We can find the positive root of the corresponding equation n^2 - 3n - 2N = 0.
 *     - The formula is: n = (-b + sqrt(b^2 - 4ac)) / 2a
 *     - Plugging in our values (a=1, b=-3, c=-2N):
 *       n = (3 + sqrt(9 - 4*1*(-2N))) / 2
 *       n = (3 + sqrt(9 + 8N)) / 2
 *     - This 'n' is the exact real number where the number of diagonals is 'N'. Since
 *       we need D(n) >= N, and D(n) is an increasing function, the smallest integer
 *       solution will be ceil() of this value.
 *
 * 2.  Binary Search (Alternative):
 *     - Since D(n) is a monotonically increasing function of 'n', we can also use
 *       binary search to find the smallest 'n' that satisfies D(n) >= N.
 *     - Search space for 'n' would be from 3 to a sufficiently large upper bound
 *       (e.g., 2*10^9 or derived from the max N).
 *     - For each 'mid' value in the binary search, calculate D(mid) and check if
 *       it's >= N.
 *
 * The quadratic formula approach is an O(1) solution and is the most direct method.
 * Care must be taken with floating-point precision when calculating the square root.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::diagonals
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


       ull diagonals; 
       int t_case = 1;
       while(scanf("%llu", &diagonals) == 1 && diagonals != 0) {
         printf("Case %d: %llu\n", t_case++, static_cast<ull>(std::ceil((3 + std::sqrt(9ULL + 8ULL * diagonals)) / 2)));
       }
    }
}