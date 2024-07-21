#include <vector>

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/missing-number
    int missingNumber(std::vector<int> nums)
    {
        int n = nums.size();
        int ans = 0;
        for(auto x : nums)
          ans ^= x;

        int i = 0;
        while(i <= n)
          ans ^= i++;

        return ans;
    }
}