/*
───────────────────────────────────────────────────────────────
🧳 UVa 12918 Lucky Thief, rt: s
───────────────────────────────────────────────────────────────
 * --- Analysis: Worst-Case Scenario Summation ---
 *
 * The problem asks for the minimum number of tries a thief must perform to *guarantee*
 * that they open 'm' unlocked houses from a total of 'n' houses.
 *
 * The keyword "ensure" or "guarantee" forces a worst-case analysis. We are not
 * interested in the average or best-case scenarios. The "minimum number of guaranteed
 * tries" is equivalent to the maximum number of tries required in the unluckiest
 * possible arrangement of locked and unlocked doors.
 *
 * Let's use the problem's variable names:
 *   n = total number of houses
 *   m = number of unlocked houses (keys)
 *
 *
 * ### Step 1: Deconstructing the Worst-Case Cost Model ###
 *
 * The specific cost model that solves this problem is a sum based on finding each
 * unlocked door one by one, under worst-case assumptions at each step.
 *
 * Let's analyze the process of finding the 'm' unlocked doors sequentially.
 * The cost (number of tries) to find each subsequent door is modeled as an
 * increasing value.
 *
 *   - The cost associated with finding the 1st unlocked door is `n - m`.
 *   - The cost associated with finding the 2nd is `n - m + 1`.
 *   - ...
 *   - The cost associated with finding the m-th (last) unlocked door is `n - 1`.
 *
 * While the real-world story for this specific cost progression is subtle, it is
 * the model that correctly solves the problem. It implies that with each success,
 * the search space for the next success becomes paradoxically harder or more expansive.
 *
 * The total number of tries is the sum of these costs.
 *
 *
 * ### Step 2: Formulating the Sum ###
 *
 * Total Tries = (n - m) + (n - m + 1) + (n - m + 2) + ... + (n - 1)
 *
 * This is an arithmetic series. We can calculate this sum efficiently without a loop.
 *
 *
 * ### Step 3: Calculating the Sum with the Arithmetic Series Formula ###
 *
 * A sum of an arithmetic series is given by:
 * Sum = (Number of Terms / 2) * (First Term + Last Term)
 *
 *   - First Term (a_1): `n - m`
 *   - Last Term (a_k): `n - 1`
 *   - Number of Terms (k): `(Last Term) - (First Term) + 1`
 *                       `k = (n - 1) - (n - m) + 1`
 *                       `k = n - 1 - n + m + 1`
 *                       `k = m`
 *
 * Plugging these into the formula:
 * Total Tries = (m / 2.0) * ( (n - m) + (n - 1) )
 * Total Tries = (m / 2.0) * ( 2n - m - 1 )
 *
 *
 * ### Step 4: Alternative Calculation using Summation Formulas ###
 *
 * The sum can also be viewed as the difference between two triangular number sums.
 * Let T(x) = x * (x + 1) / 2 be the sum of integers from 1 to x.
 *
 * Sum = (1 + 2 + ... + (n-1)) - (1 + 2 + ... + (n-m-1))
 * Sum = T(n - 1) - T(n - m - 1)
 *
 * Both calculation methods yield the same result and provide an O(1) solution for
 * each test case, which is necessary given the problem constraints.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





using ll = long long;


namespace algorithms::onlinejudge::maths::lucky_thief
{
    /** https://onlinejudge.org/external/129/12918.pdf */
    int t_cases;
    ll keys, houses;
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
         
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%lld %lld", &keys, &houses);
          // arithmetic series
          ll min_tries = (keys * (2 * houses - keys - 1)) / 2;
          printf("%lld\n", min_tries);
        }
    }
}