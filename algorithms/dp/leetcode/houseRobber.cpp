#include <vector>
#include <algorithm>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/house-robber
    int robHelper(std::vector<int>& xs, int i, std::vector<int>& memo)
    {
        if(i >= xs.size())
        return 0;
        if(memo[i] != -1)
        return memo[i]; 
        int maxBooty = 0;
        for (size_t j = i + 2; j < xs.size(); j++) {
        int local = robHelper(xs, j, memo);
        memo[j] = local;
        maxBooty = std::max(maxBooty, local);
        }
        return xs[i] + maxBooty;
    }

    int solveHouseRobber(std::vector<int>& nums) 
    {
        std::vector<int> memo = std::vector<int>(nums.size() + 1, -1);
        int maxBooty = 0;
        for (size_t i = 0; i < nums.size(); i++)
        maxBooty = std::max(maxBooty, robHelper(nums, i, memo));
        return maxBooty;
    }

    // https://leetcode.com/problems/house-robber-ii
    // Since House[1] and House[n] are adjacent, they cannot be robbed together. 
    // Therefore, the problem becomes to rob either House[1]-House[n-1] or House[2]-House[n], 
    // depending on which choice offers more money.
    int solveHouseRobber2(std::vector<int>& nums) 
    {
        if(nums.size() == 1)
            return nums[0];

        auto last_house = *(nums.end() - 1);
        nums.pop_back();
        int maxBootyNoLast = solveHouseRobber(nums);
        nums.erase(nums.begin());
        nums.push_back(last_house);
        int maxBootyNoFirst = solveHouseRobber(nums);
        return std::max(maxBootyNoLast, maxBootyNoFirst);
    }
}