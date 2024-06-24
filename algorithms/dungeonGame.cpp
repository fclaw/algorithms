#include <vector>

namespace leetcode::dp
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
        int m = dungeon.size();
        int n = dungeon[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        dp[0][0] = dungeon[0][0];
   
        return 1 - dp[m - 1][n - 1];
    }
}