/*
───────────────────────────────────────────────────────────────
🧳 UVa 11341 TermStrategy, rt: 0.0s
───────────────────────────────────────────────────────────────
Objective:
-----------
Given a list of courses, each with marks obtainable for 1 to H hours of study,
and a total of M hours to distribute among all courses, select how many hours 
to spend on each course such that:
  - Each course is passed (i.e., score ≥ 5)
  - The total time used ≤ M
  - The total marks are maximised

Input:
------
- C (number of courses)
- M (maximum total hours available)
- For each course:
    H integers representing marks for studying 1..H hours

Example:
--------
Input:
2 4
1 5 6 10
2 9 9 9

Interpretation:
---------------
- Total hours = 4
- For Course 1: 
    - 2 hours gives 5 marks (pass), 4 hours gives 10 (best)
- For Course 2:
    - 2 hours gives 9 marks (pass), also best choice within limits

Valid choice: 2 hours on each → 5 + 9 = 14 marks

Let:
- f(i, h_learned) = maximum total marks attainable from course i onwards
  having spent h_learned hours in total.

Recurrence:
-----------
f(i, h_learned) = max(
    f(i + 1, h_learned), // skip this course (or cannot find valid hours)
    max over j = 1..H of:
        if mark[i][j - 1] >= 5 and h_learned + j <= M:
            mark[i][j - 1] + f(i + 1, h_learned + j)
)

Base cases:
-----------
- If i == C (all courses done):
    return 0 if h_learned ≤ M
    else return -INF (exceeded total hours)
    
Constraints:
------------
- Only hours j where mark[i][j - 1] ≥ 5 are considered (passing requirement)
- Cannot exceed total allowed hours M

Goal:
-----
- Start from f(0, 0)
- Return the maximum sum of marks achievable while passing all courses
  within the allowed M hours
*/


#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::dp::term_strategy
{
    /** https://onlinejudge.org/external/113/11341.pdf */
    int n, m, tc;
    // f(i, h_learned) = sum of j (1 ... m) (mark(i) + f(i + 1, h_learned + j + 1)))
    int knapsack(const vvi& courses, int i, int h_learned, vvi& memo)
    {
        if(i == n) return 0;

        if(~memo[i][h_learned]) return memo[i][h_learned];

        int best_score = INT32_MIN;
        for(int h = 0; h < m; ++h)
          if(h_learned + h + 1 <= m && 
             courses[i][h] >= 5)
            best_score = std::max(best_score, courses[i][h] + knapsack(courses, i + 1, h_learned + h + 1, memo));
        return memo[i][h_learned] = best_score;
    }
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

        while_read(tc);
        while(tc--)
        {
            while_read(n, m);
            vvi courses(n, vi(m));
            loop(n, [&courses](int i) {
                loop(m, [&courses, i](int j) {
                    while_read(courses[i][j]);
                });
            });
            
            vvi dp(n + 1, vi(m + 1, INT32_MIN));
            dp[0][0] = 0;

            for(int i = 0; i < n; ++i)
              for(int j = 0; j <= m; ++j)
                for(int h = 0; h < m; ++h)
                  if(j >= h + 1 && courses[i][h] >= 5)
                    dp[i + 1][j] = std::max(dp[i + 1][j], courses[i][h] + dp[i][j - h - 1]);

            double avg_score = (double)(*std::max_element(dp[n].begin(), dp[n].end())) / n;        
            if(avg_score < 5) printf("Peter, you shouldn't have played billiard that much.\n");
            else printf("Maximal possible average mark - %.2f.\n", avg_score + 1e-9);
        }
    }
}