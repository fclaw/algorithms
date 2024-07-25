#include <vector>
#include <numeric>

using vvs = std::vector<std::vector<int>>;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/combination-sum-iii
    /*
      Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
      Only numbers 1 through 9 are used
      Each number is used at most once
      Return a list of all possible valid combinations. 
      The list must not contain the same combination twice, 
      and the combinations may be returned in any order.
    */
    void backtrack(std::vector<int> nums, int idx, int k, int target, vvs& ans, std::vector<int>& tmp) 
    {
        int n = nums.size();
        if(k > 0 && idx >= n || k < 0)
          return;

        auto s = std::reduce(tmp.begin(), tmp.end());
        if(k == 0 && target == s)
        {
            ans.push_back(tmp);
            return;
        }

        for(int i = idx; i < n; i++)
        {
            tmp.push_back(nums[i]);
            backtrack(nums, i + 1, k - 1, target, ans, tmp);
            tmp.pop_back();
        }
    }

    std::vector<std::vector<int>> combinationSum3(int k, int n) 
    {
        std::vector<int> nums(9);
        for(int i = 1; i <= 9; i++)
          nums[i - 1] = i;

        vvs ans = {};
        std::vector<int> tmp = {};
        backtrack(nums, 0, k, n, ans, tmp);
        return ans; 
    }
}