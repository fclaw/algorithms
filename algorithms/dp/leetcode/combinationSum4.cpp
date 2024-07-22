#include <vector>
#include <iostream>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/combination-sum-iv
    int combinationSum4(std::vector<int> nums, int target, std::vector<int>& memo) 
    {
        if(target == 0)
          return 1;

        int &sum = memo[target];
        if(~sum) return memo[target];

        sum = 0;
        for(auto n : nums)
          if(target - n >= 0)
            sum += combinationSum4(nums, target - n, memo);
        return memo[target] = sum;
    }

    int combinationSum4Dp(std::vector<int> nums, int target)
    {
        std::vector<int> dp(target + 1, 0);

        dp[0] = 1;

        for(int i = 1; i <= target; i++)
          for(auto n : nums)
            if(i - n >= 0)
              dp[i] += dp[i - n];
           
        return dp[target];
    }
}