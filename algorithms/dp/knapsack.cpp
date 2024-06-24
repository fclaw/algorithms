#include <vector>

namespace algorithms::dp
{
    /*
      Given a list of items with values and weights, as well as a max weight, 
      find the maximum value you can generate from items, 
      where the sum of the weights is less than or equal to the max
    */
   int maxValueInKnapsackRecursive(std::vector<std::pair<int, int>> xs, int weight, int idx)
   {
       if(idx >= xs.size())
         return 0;

       if(weight - xs[idx].first < 0)
         return maxValueInKnapsackRecursive(xs, weight, idx + 1);

       int includeVal = xs[idx].second + maxValueInKnapsackRecursive(xs, weight - xs[idx].first, idx + 1);
       int excludeVal = maxValueInKnapsackRecursive(xs, weight, idx + 1);

       return std::max(includeVal, excludeVal);
   }
   
   int maxValueInKnapsackDp(std::vector<std::pair<int, int>> xs, int weight)
   {
      int n = xs.size();
      std::vector<std::vector<int>> dp(n + 1, std::vector<int>(weight + 1, 0));
      
      for (size_t i = 1; i <= weight; i++)
        dp[0][i] = 0;

      for (size_t i = 1; i <= n; i++)
        dp[i][0] = 0;  

      for (size_t i = 1; i <= n; i++)
        for (size_t w = 0; w <= weight; w++)
          if(xs[i - 1].first > w)
            dp[i][w] = dp[i - 1][w];
          else
            dp[i][w] = std::max(dp[i - 1][w], xs[i - 1].second + dp[i - 1][w - xs[i - 1].first]);
        
      return dp[n][weight];
   }

   int maxValueInKnapsack(std::vector<std::pair<int, int>> xs, int weight) { return maxValueInKnapsackDp(xs, weight); }
}