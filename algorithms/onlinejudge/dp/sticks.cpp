/*
  Interval DP Strategy – Why We Expand from Small to Large Segments

  In dynamic programming problems that involve continuous segments (like cutting sticks,
  matrix multiplication, or palindromic substrings), the optimal cost or value for a 
  larger interval [l, r] usually depends on the values of smaller subintervals such as:
      - dp[l][k] and dp[k][r] for some l < k < r

  To ensure all required subresults are already computed before they are used,
  we must evaluate the DP table in increasing order of segment length.

  This is typically done by looping over segment lengths first, then computing 
  all intervals of that length:
  
      for (int len = 2; len <= n; ++len)
        for (int l = 0; l + len <= n; ++l) {
          int r = l + len - 1;
          // Compute dp[l][r] based on smaller intervals
        }

  This ensures that by the time we compute dp[l][r], all required values like
  dp[l][k] and dp[k][r] (for l < k < r) are already available and correct.

  Final result is typically found in dp[0][n - 1] or dp[1][n] depending on indexing.
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



namespace algorithms::onlinejudge::dp::sticks
{
    /** https://onlinejudge.org/external/100/10003.pdf */
    int length, n;
    // f(l, i, j) = sum of k from i to j l + min(f(cut[k], i, k), f(l - cut[k], k + 1, j))
    int min_cut(const vi& cuts, int l, int r, vvi& memo)
    {
        if(r - l <= 1) return 0;
        
        int& best = memo[l][r];
        if(~best) return best;

        int cost = cuts[r] - cuts[l];
        best = INT32_MAX;
        for(int k = l + 1; k < r; ++k)
          best = std::min(best, cost + min_cut(cuts, l, k, memo) + min_cut(cuts, k, r, memo));
        return best;
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
        
        while(while_read(length) && length)
        {
            while_read(n);
            vi cuts(n);
            loop(n, [&cuts](int i) { while_read(cuts[i]); });
            cuts.emplace(cuts.begin(), 0);
            cuts.push_back(length);
            int s = (int)cuts.size();

            vvi dp(s, vi(s, INT32_MAX));

           for(int i = 0; i < s; ++i)
             for(int j = 0; j < s; ++j)
               if(std::abs(i - j) <= 1)
                 dp[i][j] = 0;

            for(int len = 1; len < s; ++len)
              for(int l = 0; l + len < s; ++l) {
                int r = l + len;
                int cost = cuts[r] - cuts[l];
                for(int k = l + 1; k < r; ++k)
                  dp[l][r] = std::min(dp[l][r], cost + dp[l][k] + dp[k][r]);
              }
            printf("The minimum cutting is %d.\n", dp[0][s - 1]);  
        }
    }
}