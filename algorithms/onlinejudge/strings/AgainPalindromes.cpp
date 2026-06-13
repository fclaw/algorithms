/*
───────────────────────────────────────────────────────────────
🧳 UVa 10617 AgainPalindromes, https://onlinejudge.org/external/106/10617.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * DP TRANSITION: MISMATCH BRANCH ( S[L] != S[R] )
 * ============================================================================
 * Scenario: The characters at the outer boundaries of the current range do 
 * not match. They cannot form a new palindrome together.
 * 
 * Goal: Count all palindromic subsequences that exist within the range [L, R].
 * 
 * Naive Approach: 
 * We might try to just add the palindromes found by ignoring the left char 
 * to the palindromes found by ignoring the right char:
 *      f(L, R) = f(L+1, R) + f(L, R-1)
 * 
 * The "Double Counting" Bug:
 * As shown via tracing (e.g., string "ABB"), the subproblem f(L+1, R) evaluates
 * the inner string AND the right boundary. The subproblem f(L, R-1) evaluates
 * the inner string AND the left boundary.
 * 
 * Because BOTH recursive branches evaluate the overlapping inner substring 
 * S[L+1 ... R-1], the palindromes that exist strictly in that middle section 
 * are counted twice!
 * 
 * The Fix (Inclusion-Exclusion Principle):
 * To correct the sum, we must subtract the overlapping area exactly once. The 
 * overlapping area is precisely the subproblem that excludes both outer 
 * characters.
 * 
 * Final Formula:
 * f(L, R) = f(L+1, R) + f(L, R-1) - f(L+1, R-1)
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ui = u_int64_t;
using vi = std::vector<ui>;
using vvi = std::vector<vi>;



ui count_all_palindromes(const std::string& str) {
  int s = (int)str.size();
  vvi dp(s, vi(s, 0));
  // init 
  for(int i = 0; i < s; ++i) {
    dp[i][i] = 1;
  }
  
  for(int l = 2; l <= s; ++l) {
    for(int i = 0; i < s - l + 1; ++i) {
      int j = i + l - 1;
      if(str[i] == str[j]) {
        dp[i][j] = 1 + dp[i + 1][j] + dp[i][j - 1];
      } else{
        dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
      }
    }
  }
  return dp[0][s - 1];
}


namespace algorithms::onlinejudge::strings::again_palindromes
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
          std::string seq;
          std::cin >> seq;
          printf("%lld\n", count_all_palindromes(seq));
        }
    }
}