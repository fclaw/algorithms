#include <vector>


namespace algorithms::dp
{
    /*
    There is a fence with n posts, each post can be painted with one of the k colors.
    You have to paint all the posts such that no more than two adjacent fence posts have the same color.
    Return the total number of ways you can paint the fence.
    Note: n and k are non-negative integers.
    */
   long long countWaysToPaintFence(int n, int k)
   {
       // let assume that c = 2
       // f(i, j) = f(i - 1, j - 1) + f(i - 2, j - 1)
       // f(1, 0) = 1
       // f(1, 1) = 1;
       // f(2, 0) = 2
       // f(2, 1) = 2
       std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k, 0));

       for (int i = 0; i < k; i++)
         dp[1][i] = i;
       
       dp[2][0] = 1;

       for (int i = 2; i < k; i++)
         dp[2][i] = 2 * i;

       for (int plank = 3; plank <= n; plank++)
         for (int colour = 0; colour < k; colour++)
           dp[plank][colour] += dp[plank - 1][(k - 1) - colour] + dp[plank - 2][(k - 1) - colour]; 

       auto ways = 0;  
       for (int i = 0; i < k; i++)
         ways += dp[n][i];

       return ways;
   }
}