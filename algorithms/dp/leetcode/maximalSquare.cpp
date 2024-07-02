#include <vector>
#include <iostream>
#include <iomanip>

void printMaximalSquareDp(std::vector<std::vector<int>> dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::leetcode::dp
{

    // https://leetcode.com/problems/maximal-square
    // Given an m x n binary matrix filled with 0's and 1's, 
    // find the largest square containing only 1's and return its area
    int maximalSquare(std::vector<std::vector<char>> rect) 
    {
        int m = rect.size();
        int n = rect[0].size();
        int maxSquareSide = 0;

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        for (size_t row = 1; row <= m; row++)
          for (size_t col = 1; col <= n; col++)
                if(rect[row - 1][col - 1] - '0' == 1)
                {
                  int l = 
                    std::min(dp[row - 1][col], 
                      std::min(dp[row][col - 1],
                        dp[row - 1][col - 1]));
                  dp[row][col] = 1 + l;
                  maxSquareSide = std::max(maxSquareSide, dp[row][col]);
                }

        printMaximalSquareDp(dp);

        return maxSquareSide * maxSquareSide;
    }
}