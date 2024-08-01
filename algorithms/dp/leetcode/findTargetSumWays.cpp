#include <vector>
#include <unordered_map>

using Memo = std::unordered_map<int, std::unordered_map<int, int>>;


namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/target-sum
    /*
      You are given an integer array nums and an integer target.
      You want to build an expression out of nums by adding one of the symbols '+' and '-' 
      before each integer in nums and then concatenate all the integers.
      For example, if nums = [2, 1], you can add a '+' before 2 and a '-' 
      before 1 and concatenate them to build the expression "+2-1".
      Return the number of different expressions that you can build, which evaluates to target.
    */
    int findTargetSumWaysRec(std::vector<int> nums, int target, int idx, Memo memo)
    {
        if(idx == nums.size())
          return target == 0 ? 1 : 0;

        if(auto x = memo.find(idx); x != memo.end())
            return (*x).second.find(target)->second;

        int res = findTargetSumWaysRec(nums, target - nums[idx], idx + 1, memo) +
                  findTargetSumWaysRec(nums, target + nums[idx], idx + 1, memo);

        memo[idx][target] = res;

        return res;
    }
    
    int findTargetSumWaysDp(std::vector<int> nums, int target) 
    {
        int sum = 0;
        for (auto n : nums)
          sum += n;

        if(sum < std::abs(target))
          return 0;

        std::vector<std::vector<int>> dp(nums.size() + 1, std::vector<int>(2 * sum + 1));

        dp[0][sum] = 1;

        for (int i = 1; i <= nums.size(); i++)
          for (int t = 0; t < 2 * sum + 1; t++)
          {
            int prev = dp[i - 1][t];
            if (prev != 0) 
            {
              dp[i][t - nums[i - 1]] += prev;
              dp[i][t + nums[i - 1]] += prev;
            }
          }

        return dp[nums.size()][sum + target];
    }

    int findTargetSumWays(std::vector<int> nums, int target) { return findTargetSumWaysDp(nums, target); }
}