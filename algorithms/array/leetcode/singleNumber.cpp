#include <vector>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/single-number
    int singleNumber(std::vector<int>& nums) 
    {
        int ans = 0;
        for(auto n : nums)
          ans ^= n;
        return ans;  
    }
}