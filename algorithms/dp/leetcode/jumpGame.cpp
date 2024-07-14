#include <vector>
#include <algorithm>
#include <iostream>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/jump-game
    /*
       You are given an integer array nums. You are initially positioned at the array's first index, 
       and each element in the array represents your maximum jump length at that position.
       Return true if you can reach the last index, or false otherwise.
    */
   // dp approach is abjectly slow on large inputs due to time complexity of O(n^2)
    bool canJumpDp(std::vector<int> nums)
    {
          int n = nums.size();
        std::vector<bool> dp(n, false);
        dp[0] = true;
        for (int i = 0; i < n - 1; i++)
          if(dp[i])
          {
              auto b = i + nums[i];
              for(int j = 1; j <= std::min(b, n - 1); j++)
                 dp[j] = true;
          }
        return dp[n - 1];
    }
    bool canJumpGreedy(std::vector<int> nums)
    {
       int n = nums.size();
    if (n == 0) return false;

    int farthest = 0;  // The farthest index we can reach

    // Iterate through each index
    for (int i = 0; i < n; ++i) {
        if (i > farthest) return false;  // If current index is unreachable, return false

        // Update the farthest index we can reach
        farthest = std::max(farthest, i + nums[i]);

        // Check if we can reach or pass the last index
        if (farthest >= n - 1) return true;
    }

    return false;
    }
    bool canJump(std::vector<int>& nums) { return canJumpGreedy(nums); }
}