#include <vector>

using vvs = std::vector<std::vector<int>>;
using ll = long long;
const int N = 7;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/permutations
    // Given an array nums of distinct integers, return all the possible permutations. 
    // You can return the answer in any order.
    vvs rec(std::vector<int>& nums, ll mask)
    {
        if(__builtin_popcount(mask) == nums.size())
          return {{}};

        vvs tmp;
        for(int i = 0; i < nums.size(); i++)
        {
            if(!(mask & (1LL << i)))
            {
                auto xxs = rec(nums, mask | (1LL << i));
                for(auto& xs : xxs)
                  xs.push_back(nums[i]);
                tmp.insert(tmp.end(), xxs.begin(), xxs.end());  
            }
        }
        return tmp;
    }

    void backtrack(std::vector<int>& nums, int idx, vvs& ans)
    {
        int n = nums.size();
        if(idx == n)
          ans.push_back(nums);
         

        for(int i = idx; i < n; i++)
        {
            std::swap(nums[idx], nums[i]);
            backtrack(nums, idx + 1, ans);
            std::swap(nums[idx], nums[i]);
        }
    }

    std::vector<std::vector<int>> permute(std::vector<int> nums) 
    {
        vvs ans = {};
        // return rec(nums, 0);
        backtrack(nums, 0, ans);
        return ans;

    }
}