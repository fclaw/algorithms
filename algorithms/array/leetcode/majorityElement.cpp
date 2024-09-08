#include <vector>

namespace algorithms::array::leetcode
{
    /**
     * https://leetcode.com/problems/majority-element
     */
     int majorityElement(std::vector<int>& nums) 
     {
        int majority_el = nums[0];
        int counter = 1;
        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] == majority_el)
              ++counter;
            else
            {
                --counter;
                if(counter == 0)
                {
                    majority_el = nums[i];
                    counter = 1;
                }
            }
        }

        int k = 0;
        for(auto n : nums)
          if(n == majority_el) ++k;

        return majority_el;
     }
}