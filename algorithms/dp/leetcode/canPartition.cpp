#include <vector>
#include <iostream>

namespace algorithms::dp::leetcode
{    
    int fetchTarget(std::vector<int> nums, long long subset)
    {
        int n = nums.size();
        int sum = 0;
        for (int i = 0; i < n; i++)
          if(subset & (1LL << i))
            sum += nums[i];
        return sum;
    }

    /*
       Given an integer array nums, return true if you can partition the array into two subsets 
       such that the sum of the elements in both subsets is equal or false otherwise.
    */
    bool solveViaSubset(std::vector<int> xs, int idx, long long subset)
    {
        int n = xs.size();
        if(idx == n)
          return false;

        bool ans = false;
        for (int i = 0; i < n; i++)
        {
            if(subset & (1LL << i))
              continue;
            int prefixSum = fetchTarget(xs, subset);
            int postfixSum = fetchTarget(xs, ~subset);
            long long new_set = 0 | (1LL << i);
            new_set |= subset;
            ans |= 
              ((prefixSum + xs[i] == postfixSum - xs[i]) || 
              solveViaSubset(xs, idx + 1, new_set)); 
        }

        return ans;
    }

    bool solve(std::vector<int> xs, int idx, int target, std::vector<std::vector<int>>& memo) 
    {
        int n = xs.size();
        if(idx == n)
          return false;

        if(target < 0)
          return false;

        if(target == 0) 
          return true;  

        if(memo[target][idx] != -1)
          return (bool)memo[target][idx];

        memo[target][idx] =
          solve(xs, idx + 1, target - xs[idx], memo) || 
          solve(xs, idx + 1, target, memo);
        return memo[target][idx];
    }

    bool solveDp(std::vector<int> xs, int target) 
    {
        std::vector<bool> dp(target + 1);

        dp[0] = true;

        for(auto x : xs)
          for(int i = target; i >= x; i--)
              dp[i] = dp[i] || dp[i - x];

        return dp[target]; 
    }

    bool canPartition(std::vector<int> nums)
    {
        int sum = 0;
        for(auto n : nums)
          sum += n;

        if(sum % 2 == 1)
          return false;

        return solveDp(nums, sum / 2);
    }
}