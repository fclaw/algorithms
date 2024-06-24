#include <vector>

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
    int findTargetSumWaysRec(std::vector<int> nums, int target, int idx)
    {
        if(idx == nums.size())
          return target == 0 ? 1 : 0;

        return findTargetSumWaysRec(nums, target - nums[idx], idx + 1) + 
               findTargetSumWaysRec(nums, target + nums[idx], idx + 1);
    }
    
    int findTargetSumWaysDp(int nums, int target) { return 0; } 

    int findTargetSumWays(std::vector<int> nums, int target) { return findTargetSumWaysRec(nums, target, 0); }
}