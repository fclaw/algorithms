inc

// https://leetcode.com/problems/unique-paths-ii
// dp[y][x] = grid[y - 1][x] == 1 ? 0 : dp[y - 1][x] + grid[y][x - 1] == 1 ? 0 : dp[y][x - 1]

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
     int n = obstacleGrid.size(); // y
     int m = obstacleGrid[0].size(); // x
     vector<vector<int>> dp = vector<vector<int>>(n, vector<int>(m, 0));

    if(obstacleGrid[0][0] == 1)
      return 0;

    // base case 0, 0
    dp[0][0] = 1;

    // y is zero
    int xObstacle = -1;
    for (size_t i = 0; i < m; i++)
    {
      if(obstacleGrid[0][i] == 1)
        xObstacle = i;
      dp[0][i] = xObstacle != -1 ? 0 : 1;
    }

    // x is zero
    int yObstacle = -1;
    for (size_t j = 0; j < n; j++)
    {
       if(obstacleGrid[j][0] == 1)
         yObstacle = j;
      dp[j][0] = yObstacle != -1 ? 0 : 1;
    }

    for (size_t i = 1; i < n; i++)
      for (size_t j = 1; j < m; j++)
      {  
        if(obstacleGrid[i][j] == 1)
          dp[i][j] = 0;
        else
        {
            int fromAbove = obstacleGrid[i - 1][j] == 1 ? 0 : dp[i - 1][j];
            int fromLeft = obstacleGrid[i][j - 1] == 1 ? 0 : dp[i][j - 1];
            dp[i][j] = fromAbove + fromLeft;
        }
      }
    return dp[n - 1][m - 1];
}