/*
───────────────────────────────────────────────────────────────
🧳 UVa 10943 How do you add? , rt: s
───────────────────────────────────────────────────────────────
  Combination Formula - Pascal's Triangle Recurrence
  --------------------------------------------------

  The number of ways to choose k elements from a set of n elements is denoted as:
      C(n, k) or "n choose k"

  Standard recurrence relation:
      C(n, k) = C(n - 1, k - 1) + C(n - 1, k)

  Explanation:
    - Consider one particular element in the set:
        • If we include it, we need to choose (k - 1) from the remaining (n - 1)
        • If we exclude it, we choose all k from the remaining (n - 1)
    - Hence, the total is the sum of both cases.

  Base Cases:
    C(n, 0) = 1      // Only one way to choose nothing
    C(n, n) = 1      // Only one way to choose all elements
    C(n, k) = 0 when k > n

  This recurrence forms Pascal's Triangle:
      C(0, 0)
      C(1, 0) C(1, 1)
      C(2, 0) C(2, 1) C(2, 2)
      ...
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

const int mod = (int)1e6;


namespace algorithms::onlinejudge::dp::castaways
{
    /** https://onlinejudge.org/external/109/10943.pdf */
    int N, K;
    int get_ways(int n, int k)
    {
        if(n == 0) return 1;

        int ways = 0;
        for(int i = 0; i <= n; ++i)
          if(k >= 1) ways += get_ways(n - i, k - 1);
        return ways;  
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
        
        while(while_read(N, K) && N && K) {
          vvi dp(N + 1, vi(K + 1, 0));
          dp[0][0] = 1;
          for(int n = 0; n <= N; ++n)
            for(int k = 0; k <= K; ++k)
              for(int i = 0; i <= n; ++i) {
                if(k >= 1) dp[n][k] += dp[n - i][k - 1];
                dp[n][k] %= mod;
              }
          printf("%d\n", dp[N][K]);
        }          
    }
}