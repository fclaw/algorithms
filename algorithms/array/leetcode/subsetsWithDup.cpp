#include <vector>
#include <iostream>


const int C = 11;

namespace algorithms::array::leetcode
{
    // https://leetcode.com/problems/subsets-ii
    void rec(std::vector<int> xs, int i, int mask, std::vector<int> tmp, std::vector<std::vector<int>>& xxs)
    {
        int n = xs.size();
        if(i == n)
        {
           xxs.push_back(tmp);
           return;
        }
        
        auto ys = tmp;
        ys.push_back(xs[i]);
        int v = xs[i] > 0 ? xs[i] : ~xs[i] + C;
        rec(xs, i + 1, mask | (1 << v), ys, xxs);

        if(mask & (1 << v))
          return;

        if(!ys.empty())
          ys.pop_back();
        rec(xs, i + 1, mask, ys, xxs); 
    }
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) 
    {
        std::vector<std::vector<int>> ans;
        rec(nums, 0, 0, {}, ans);
        return ans;
    }
}