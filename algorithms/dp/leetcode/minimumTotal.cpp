#include <vector>
#include <iostream>
#include <iomanip>

using Triangle = std::vector<std::vector<int>>;

void printMinimumTotalDp(std::vector<std::vector<int>> dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/triangle
    /*
      Given a triangle array, return the minimum path sum from top to bottom.
      For each step, you may move to an adjacent number of the row below. 
      More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
    */
    int minimumTotal(Triangle triangle) 
    {
        int row = triangle.size();
        int n = triangle[row - 1].size();
        std::vector<std::vector<int>> dp(row, std::vector<int>(n, INT32_MAX));

        for (int i = 0; i < n; i++)
          dp[0][i] = triangle[row - 1][i];

        for (int r = 1; r < row; r++)
          for (int c = 0; c < n - r; c++)
             dp[r][c] = 
               std::min(
                triangle[row - (r + 1)][c] + dp[r - 1][c], 
                triangle[row - (r + 1)][c] + dp[r - 1][c + 1]
               );

        printMinimumTotalDp(dp);

        return dp[row - 1][0];
    }
}