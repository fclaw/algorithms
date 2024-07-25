#include <vector>

using vvs = std::vector<std::vector<int>>;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/combinations
    void rec(std::vector<int> xs, int idx, int k, std::vector<int> ys, vvs& ans)
    {
        if(ys.size() == k)
        { 
            ans.push_back(ys);
            return;
        }
        if(idx >= xs.size())
          return;
        
        ys.push_back(xs[idx]);
        rec(xs, idx + 1, k, ys, ans);
        ys.pop_back();
        rec(xs, idx + 1, k, ys, ans);
    }

    std::vector<std::vector<int>> combine(int n, int k) 
    {
        std::vector<int> nums(n);
        for(int i = 1; i <= n; i++)
          nums[i - 1] = i;
        vvs ans = {};  
        rec(nums, 0, k, {}, ans);
        return ans;
    }
}