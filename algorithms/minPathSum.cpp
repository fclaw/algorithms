#include <vector>

// https://leetcode.com/problems/minimum-path-sum
int minPathSum(std::vector<std::vector<int>>& grid)
{
     int n = grid.size(); // y
     int m = grid[0].size(); // x
     std::vector<std::vector<int>> dp = std::vector<std::vector<int>>(n, std::vector<int>(m, -1));

    // base case 0, 0
    dp[0][0] = grid[0][0];

    // y is zero
    for (size_t i = 1; i < m; i++)
      dp[0][i] = dp[0][i - 1] + grid[0][i];

    // x is zero
    for (size_t j = 1; j < n; j++)
      dp[j][0] = dp[j - 1][0] + grid[j][0];

    for (size_t i = 1; i < n; i++)
      for (size_t j = 1; j < m; j++)
        dp[i][j] = std::min(grid[i][j] + dp[i - 1][j], grid[i][j] + dp[i][j - 1]);

    return dp[n - 1][m - 1];
}