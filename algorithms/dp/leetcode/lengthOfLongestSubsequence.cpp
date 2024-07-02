#include <vector>
#include <iostream>
#include <unordered_map>
#include <tuple>

void printLengthOfLongestSubsequenceDp(std::vector<std::vector<int>> dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target
    /*
      You are given a 0-indexed array of integers nums, and an integer target.
      Return the length of the longest subsequence of nums that sums up to target. If no such subsequence exists, return -1.
      A subsequence is an array that can be derived from another array 
      by deleting some or no elements without changing the order of the remaining elements.
      i = idx, t = target
    */
    int lengthOfLongestSubsequenceRec
        (std::vector<int> nums, 
         int target, 
         int idx, 
         std::unordered_map<int, std::unordered_map<int, int>>& memo)
    {
        if(target == 0)
          return 0;

        if(target < 0 || idx >= nums.size())
          return -1;

        // auto key = std::make_tuple(index, target);
        if (auto x = memo.find(idx); x != memo.end())
          if(x->second.find(target) != x->second.end())
            return memo[idx][target];

        int x = lengthOfLongestSubsequenceRec(nums, target - nums[idx], idx + 1, memo); // dp[i - 1][t - xs[i]]
        int y = lengthOfLongestSubsequenceRec(nums, target, idx + 1, memo); // dp[i - 1][t]
        if(x != -1)
          x++; 
        // Store the result in the memoization map
        memo[idx][target] = std::max(x, y);
        return memo[idx][target];
    }
    int lengthOfLongestSubsequence(std::vector<int> nums, int target) 
    {   
        int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(target + 1, -1));
 
        for (int i = 1; i <= n; i++)
          dp[i][0] = 0;

       dp[0][0] = 0;

       for (int idx = 1; idx <= n; idx++)
         for (int t = 1; t <= target; t++)
          {
              int x = 
                   t - nums[idx - 1] >= 0 && 
                   dp[idx - 1][t - nums[idx - 1]] != -1 ? 
                   dp[idx - 1][t - nums[idx - 1]] : -1;
              int y = dp[idx - 1][t];
              if(x != -1)
               x++;
              dp[idx][t] = std::max(x, y);
          }

        printLengthOfLongestSubsequenceDp(dp);

        return dp[n][target];
    }
}