#include <vector>
#include <iostream>
#include <iomanip>

using DP = std::vector<std::vector<int>>;

void printMaximalSquareDp(DP dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace leetcode::dp
{
    // https://leetcode.com/problems/maximal-square
    // Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area
    int maximalSquare(std::vector<std::vector<char>>& rect) 
    {
        int m = rect.size();
        int n = rect[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        dp[0][0] = rect[0][0] - '0';

        for (size_t i = 1; i < n; i++)
          dp[0][i] = std::max(dp[0][i], dp[0][i - 1]);

        for (size_t i = 1; i < m; i++)
          dp[i][0] = std::max(dp[i][0], dp[i - 1][0]);

        printMaximalSquareDp(dp);
 
        return dp[m - 1][n - 1];
    }
}