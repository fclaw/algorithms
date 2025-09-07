/*
───────────────────────────────────────────────────────────────
🧳 UVa 12036 Stable Grid, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: The Pigeonhole Principle ---
 *
 * The problem asks if we can rearrange the numbers in each row of an N x N grid
 * such that no column has repeated values. This appears to be a complex permutation
 * or matching problem. However, the constraints and the nature of the condition allow
 * for a much simpler solution.
 *
 *
 * ### The Key Insight: Necessary vs. Sufficient Conditions ###
 *
 * Instead of trying to construct a stable arrangement (which would be very difficult),
 * let's find a simple "necessary" condition. If this necessary condition is not met,
 * then a solution is impossible.
 *
 * Consider a single number, let's say the number 7. Let's count its total occurrences
 * across the entire N x N grid. Let this count be `count(7)`.
 *
 * In any valid "stable" arrangement, these `count(7)` instances of the number 7 must
 * be placed in the grid. Since we can only permute numbers within their own rows,
 * each 7 will remain in its original row.
 *
 * The crucial constraint is that after rearrangement, each column can have at most ONE
 * instance of the number 7. Since there are N columns, this means that in total, we
 * can place at most N sevens in the final grid without any column conflicts.
 *
 *
 * ### The Pigeonhole Principle ###
 *
 * This leads directly to a Pigeonhole Principle argument:
 *
 *   - The numbers (e.g., all the 7s) are the "pigeons".
 *   - The N columns are the "pigeonholes".
 *   - The rule is that no two pigeons (of the same value) can be in the same pigeonhole.
 *
 * If the number of pigeons (`count(7)`) is greater than the number of pigeonholes (`N`),
 * then by the Pigeonhole Principle, at least one pigeonhole (column) must contain
 * more than one pigeon. This would violate the stability condition.
 *
 * Therefore, a NECESSARY condition for the grid to be stable is that for ANY number `v`
 * present in the grid, its total frequency must not exceed N.
 *   `count(v) <= N` for all `v`.
 *
 *
 * ### Is the Condition Sufficient? ###
 *
 * The problem now is: is this condition also sufficient? If `count(v) <= N` for all
 * numbers `v`, are we guaranteed to find a stable arrangement? The answer comes
 * from a famous theorem in combinatorics related to systems of distinct
 * representatives, Hall's Marriage Theorem. It can be shown that this condition
 * is indeed sufficient.
 *
 * Therefore, the problem simplifies from a complex arrangement task to a simple
 * frequency counting task.
 *
 *
 * ### The Algorithm ###
 *
 * 1. Read N and the N x N grid.
 * 2. Use a hash map (or an array, since numbers are <= 100) to store the frequency
 *    of every number in the entire grid.
 * 3. Iterate through the frequencies. If any number's frequency is greater than N,
 *    the grid is not stable.
 * 4. If all numbers have a frequency less than or equal to N, the grid is stable.
 *
 * This transforms the problem into a simple O(N^2) pass to count frequencies.
 * Your provided code has a logical flaw in its counting loop, but the idea is right.
 * A single pass to build the frequency map is all that's needed.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;
using map = std::unordered_map<int, int>;




namespace algorithms::onlinejudge::maths::stable_grid
{
    /** https://onlinejudge.org/external/120/12036.pdf */
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
         
        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n;
          scanf("%d", &n);
          vvi grid(n, vi(n));
          map counter;
          for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
              scanf("%d", &grid[i][j]);
              counter[grid[i][j]] = 0;
            }
          }
          
          bool is_stable = true;
          for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
              int cnt = counter.at(grid[i][j]);
              if(cnt >= n) {
               is_stable = false;
               goto finished;
              }
              counter[grid[i][j]]++;
            }
          }

          finished: printf("Case %d: %s\n", t_case++, is_stable ? "yes" : "no");
        }  
    }
}