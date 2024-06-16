#include <vector>


namespace leetcode::dp
{
    // https://leetcode.com/problems/pascals-triangle
    // Given an integer numRows, return the first numRows of Pascal's triangle.
    // In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
    std::vector<std::vector<int>> generate(int numRows) 
    {
        std::vector<std::vector<int>> dp(numRows, std::vector(numRows, 0));
        for (size_t i = 0; i < numRows; i++)
          dp[i][0] = 1;

        for (size_t i = 1; i < numRows; i++)
          for (size_t j = 1; j < numRows; j++)
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

        for (auto& v : dp)
          v.erase(std::remove(v.begin(), v.end(), 0), v.end());

        return dp;
    }
}