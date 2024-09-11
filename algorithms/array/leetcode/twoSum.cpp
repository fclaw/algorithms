#include <vector>
#include <unordered_map>

namespace algorithms::array::leetcode::two_sum
{
    std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        std::unordered_map<int, int> map;
        std::vector<int> ans;
        for(int i = 0; i < nums.size(); i++)
        {
            if(auto it = map.find(nums[i]); 
               it != map.end())
              ans = {i, (*it).second};
            else map[target - nums[i]] = i;
        }
        return ans;
    }
}