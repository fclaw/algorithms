/*
───────────────────────────────────────────────────────────────
🧳 UVa 11296 Counting Solutions of an Integer Equation, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Mathematical Analysis: A Combinatorial Approach ---
 *
 * The problem asks for the number of non-negative integer solutions to the equation:
 *   x + 2y + 2z = n
 *
 * A direct brute-force check of all (x, y, z) is too slow. We must find an O(1)
 * mathematical formula by reducing the problem.
 *
 *
 * ### Step 1: Isolate a Variable and Analyze Constraints ###
 *
 * We can rearrange the equation to solve for x:
 *   x = n - 2y - 2z
 *   x = n - 2(y + z)
 *
 * Since x, y, and z must be non-negative, we have two key constraints:
 *   1. x >= 0  =>  n - 2(y + z) >= 0  =>  2(y + z) <= n  =>  (y + z) <= n/2
 *   2. The parity of x depends on the parity of n.
 *      - If n is even, x = (even - even), so x is even. This is always possible.
 *      - If n is odd, x = (odd - even), so x is odd. This is also always possible.
 *
 * The problem is now reduced to a simpler one: For a given n, how many pairs of
 * non-negative integers (y, z) satisfy the inequality (y + z) <= n/2 ?
 *
 *
 * ### Step 2: Define the Upper Bound ###
 *
 * Let k = floor(n/2). In integer arithmetic, this is simply k = n / 2.
 * The problem is now: Count the number of non-negative integer pairs (y, z) such that:
 *   y + z <= k
 *
 *
 * ### Step 3: Enumerate the Subproblems ###
 *
 * To count the solutions to the inequality y + z <= k, we can sum the number of
 * solutions for each possible value of the sum S = y + z.
 * The sum S can range from 0 up to k.
 *
 * Total Solutions = (Solutions for y+z=0) + (Solutions for y+z=1) + ... + (Solutions for y+z=k)
 *
 *
 * ### Step 4: The Crucial Combinatorial Insight (Counting the Solutions) ###
 *
 * This is the heart of the solution. We need to find a formula for the number of
 * non-negative integer solutions to the equation `y + z = S` for a fixed sum S.
 *
 * This is a classic combinatorial problem often called "Stars and Bars".
 *   - Imagine we have S "stars" (units) to distribute between y and z.
 *   - We need 1 "bar" (a separator) to divide the stars into two groups.
 *
 * For example, if S = 4:
 *   y=0, z=4  is represented as: |****
 *   y=1, z=3  is represented as: *|***
 *   y=2, z=2  is represented as: **|**
 *   y=3, z=1  is represented as: ***|*
 *   y=4, z=0  is represented as: ****|
 *
 * The number of solutions is the number of places we can put the single bar. We have
 * S stars and 1 bar, for a total of S+1 items/positions. We need to choose 1 of these
 * positions for the bar. The number of ways is C(S+1, 1) = S+1.
 *
 * Therefore, the equation `y + z = S` has exactly `S + 1` non-negative integer solutions.
 *
 *
 * ### Step 5: The Final Summation and Formula ###
 *
 * Now we can substitute our finding from Step 4 back into the summation from Step 3:
 *
 * Total Solutions = ∑_{S=0}^{k} (S + 1)
 *
 * This is the sum of the first (k+1) positive integers: 1 + 2 + 3 + ... + (k+1).
 * The formula for the sum of the first m integers is m*(m+1)/2. Here, m = k+1.
 *
 * Total Solutions = (k + 1) * ( (k + 1) + 1 ) / 2
 *                 = (k + 1) * (k + 2) / 2
 *
 *
 * ### Final Algorithm ###
 *
 * 1. Given n, calculate the upper bound for the sum (y+z): k = n / 2 (integer division).
 * 2. Apply the summation formula: result = (k + 1) * (k + 2) / 2.
 *
 * This single O(1) formula works for both even and odd n, providing an elegant and
 * efficient solution.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;



namespace algorithms::onlinejudge::maths::counting_solutions
{
    /** https://onlinejudge.org/external/112/11296.pdf */
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
        
        int n;
        while(scanf("%d", &n) == 1) {
          int k = n / 2;
          ll result = (ll)(k + 1) * (k + 2) / 2;
          printf("%lld\n", result);
        }
    }
}