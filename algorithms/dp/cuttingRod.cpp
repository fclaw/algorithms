#include <vector>
#include <iostream>

namespace algorithms::dp
{
    // Given an iron rod of a certain length and price of selling rods of different lengths on the market, 
    // how should we cut the rod so that the profit si maximized.
    // To solve this problem using dynamic programming, follow these steps:
    // Define the State:
    // Let dp[i] represent the maximum value obtainable for a rod of length i
    // Base Case:
    // dp[0] is 0 because a rod of length 0 has no value.
    // Recurrence Relation:
    // For each length 𝑖, consider all possible cuts. If you cut the rod into two parts of lengths 𝑗 and i - j  
    // the total value is the sum of the prices of these two parts.
    // Thus, for each 𝑖 dp[i] is the maximum of price[j-1] + dp[i-j] for all 𝑗 from 1 to 𝑖
    int maxProfitFromCuttingRodDp(int rod, std::vector<int> prices)
    {
        std::vector<int> dp(rod + 1, 0);
        
        for (size_t r = 1; r <= rod; r++)
            for (size_t p = 0; p < r; p++)
              dp[r] = std::max(dp[r], prices[p] + dp[r - p - 1]);
        return dp[rod];
    }
    int maxProfitFromCuttingRod(int rod, std::vector<std::pair<int, int>> prices)
    {
        if(rod == 0)
          return 0;

        int maxProfit = INT32_MIN;
        for (size_t i = 0; i < prices.size(); i++)
        {
            if(rod - prices[i].first < 0)
              continue;
          maxProfit = std::max(maxProfit, prices[i].second + maxProfitFromCuttingRod(rod - prices[i].first, prices));
        }
        return maxProfit;
    }
}