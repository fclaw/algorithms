#include <vector>
#include <iostream>
#include <algorithm>

namespace leetcode::dp
{

    // https://leetcode.com/problems/min-cost-climbing-stairs
    /*
     You are given an integer array cost where cost[i] is the cost of ith step on a staircase. 
     Once you pay the cost, you can either climb one or two steps.
     You can either start from the step with index 0, or the step with index 1.
     Return the minimum cost to reach the top of the floor
     Input: cost = [1,100,1,1,1,100,1,1,100,1]
     Output: 6
     Explanation: You will start at index 0.
     - Pay 1 and climb two steps to reach index 2.
     - Pay 1 and climb two steps to reach index 4.
     - Pay 1 and climb two steps to reach index 6.
     - Pay 1 and climb one step to reach index 7.
     - Pay 1 and climb two steps to reach index 9.
     - Pay 1 and climb one step to reach the top.
     The total cost is 6.
    */
    int minCostClimbingStairs(std::vector<int>& cost) 
    {
          int n = cost.size(); 
          std::vector<int> dp(n + 1, 0);
          dp[0] = cost[0];
          dp[1] = cost[1];

          for (size_t i = 2; i <= n; i++)
            dp[i] = (i == n ? 0 : cost[i]) + std::min(dp[i - 1], dp[i - 2]);

         return dp[n];
    }

    // C() = C(i - 1) + C(i - 2) + .. + C(i - k) 
    // i > k
    int climbingStairsInKSteps(int n, int k)
    {
        std::vector<int> dp(n + 1, 0);
        
        dp[0] = 1;
        dp[1] = 1;
        
        for (size_t stairs = 2; stairs <= n; stairs++)
          for (size_t step = 1; step <= k; step++)
            if (stairs >= step)
              dp[stairs] += dp[stairs - step];

        return dp[n];
    }

    int climbingStairsInKStepsMissingSome(int n, int k, std::vector<int> xs)
    {
        std::vector<int> dp(n + 1, 0);
        
        dp[0] = 1;
        dp[1] = 1;
        
        for (size_t stairs = 2; stairs <= n; stairs++)
          for (size_t step = 1; step <= k; step++)
          {
            if (stairs < step)
              continue;
            if(std::find(xs.begin(), xs.end(), stairs) != xs.end())
               dp[stairs] = 0;
            else dp[stairs] += dp[stairs - step];
          }

        return dp[n];
    }

    int cheapestWayToReachNthStairs(int n, std::vector<int> costs)
    { 
        std::vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = costs[1];
        dp[2] = costs[2];
        
        // C(n) = costs[n - 1] + min(C(n - 1), C(n - 2))
         for (size_t stairs = 2; stairs <= n; stairs++)
            dp[stairs] += costs[stairs - 1] + std::min(dp[stairs - 1], dp[stairs - 2]);

        return dp[n];
        
    }

 }