#include <vector>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/counting-bits
    // Given an integer n, return an array ans of length n + 1 
    // such that for each i (0 <= i <= n), ans[i] 
    // is the number of 1's in the binary representation of i.
    // T(n) = T(n - (n % 2))
    // dp[i] = dp[i >> 1] + (i & 1)
    std::vector<int> countBits(int n) 
    {
        std::vector<int> dp(n + 1, 0);
        for(int i = 1; i <= n; i++)
          dp[i] = dp[i >> 1] + /* even or odd */ (i & 1);
        return dp;
    }
}