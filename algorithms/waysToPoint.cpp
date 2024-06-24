#include <vector>
#include <iostream>

namespace algorithms::dp
{
    int countWaysToReachPoint(int n, std::vector<int> xs)
    {
        if(n < 0)
          return 0;
        if(n == 0)
          return 1;
        
        int ways = 0;
        for (int i = 0; i < xs.size(); i++)
          ways += countWaysToReachPoint(n - xs[i], xs); 
        return ways;  
    }

    int countWaysToReachPointDp(int n, std::vector<int> xs)
    {
         std::vector<int> dp(n + 1, 0);
         dp[0] = 1;

         for (int i = 1; i <= n; i++)
           for (int j = 0; j < xs.size(); j++)
             if(i - xs[j] >= 0)
               dp[i] += dp[i - xs[j]];
 
        return dp[n];
    }
}