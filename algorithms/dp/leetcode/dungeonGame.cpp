#include <vector>
#include <iostream>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/dungeon-game
    /*
      The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. 
      The dungeon consists of m x n rooms laid out in a 2D grid. 
      Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.
      The knight has an initial health point represented by a positive integer. 
      If at any point his health point drops to 0 or below, he dies immediately.
      Some of the rooms are guarded by demons (represented by negative integers), 
      so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).
      To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
      Return the knight's minimum initial health so that he can rescue the princess.
      Note that any room can contain threats or power-ups, 
      even the first room the knight enters and the bottom-right room where the princess is imprisoned.
    */
    int calculateMinimumHP(std::vector<std::vector<int>> dungeon)
    {
        int M = dungeon.size();
        int N = dungeon[0].size();
        std::vector<std::vector<int>> dp(M + 1, std::vector<int>(N + 1, 5 * 1e+05));
        dp[M - 1][N] = 1;
        dp[M][N - 1] = 1;

        for (int r = M - 1; r >= 0; r--)
          for(int c = N - 1; c >= 0; c--)
           {
               int below;
               // 
               if(dungeon[r][c] < 0)
                  below = std::abs(dungeon[r][c]) + dp[r + 1][c];
               if(dungeon[r][c] > 0 && dungeon[r][c] >= dp[r + 1][c])
                  below = 1;
               if(dungeon[r][c] > 0 && dungeon[r][c] < dp[r + 1][c])
                  below = dp[r + 1][c] - dungeon[r][c];
               if(dungeon[r][c] == 0)
                  below = dp[r + 1][c];   
               int right;
               if(dungeon[r][c] < 0)
                 right = std::abs(dungeon[r][c]) + dp[r][c + 1];
               if(dungeon[r][c] > 0 && dungeon[r][c] >= dp[r][c + 1])
                 right = 1;
               if(dungeon[r][c] > 0 && dungeon[r][c] < dp[r][c + 1])
                 right = dp[r][c + 1] - dungeon[r][c];
               if(dungeon[r][c] == 0)
                 right = dp[r][c + 1];

               dp[r][c] = std::min(below, right);
           }

        return dp[0][0];
    }
}