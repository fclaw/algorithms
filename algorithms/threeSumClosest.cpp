#include <vector>
#include <iostream>

namespace leetcode::array 
{
    // https://leetcode.com/problems/3sum-closest
    int threeSumClosest(std::vector<int>& nums, int target) 
    {
        std::sort(nums.begin(), nums.end()); // O(n*log(n))
        int i = 0;
        int sum;
        std::vector<std::vector<int>> xs(nums.size());
        while(i < nums.size())
        {
            auto left = i + 1;
            auto right = nums.size() - 1;
            auto curr_sum = 0;
            while(left < right)
            {
                curr_sum = nums[i] + nums[left] + nums[right];
                if(target == curr_sum)
                {
                    sum = curr_sum;
                    break;
                }

                if(std::abs(sum - target) > 
                   std::abs(curr_sum - target))
                  sum = curr_sum;

                else if (target > curr_sum)
                  left++;
                else right--;
            }
            
            if(++i < nums.size() && nums[i] == nums[i - 1])
              continue;
        }
        return sum;
    }

}