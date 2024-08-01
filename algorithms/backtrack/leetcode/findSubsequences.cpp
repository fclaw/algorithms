#include <vector>
#include <set>


using ss = std::vector<std::vector<int>>;
using st = std::vector<int>;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/non-decreasing-subsequences
    /*
       Given an integer array nums, return all the different 
       possible non-decreasing subsequences of the given array 
       with at least two elements. You may return the answer in any order.
       all possible 
    */
    void backtrack(const std::vector<int>& xs, int i, int last, ss& ans, st& tmp)
    {
        int n = xs.size();
        if(i >= n) 
        {
            if(tmp.size() > 1)
              ans.push_back(tmp);
            return;
        }

        if(!tmp.empty() &&
           tmp.back() > xs[i])
           backtrack(xs, i + 1, last, ans, tmp);
        else  
        { 
            tmp.push_back(xs[i]);
            backtrack(xs, i + 1, xs[i], ans, tmp);
            tmp.pop_back();
            // mask &= ~(1 << i);
            if(last != xs[i]) backtrack(xs, i + 1, last, ans, tmp);
        }
    }
    std::vector<std::vector<int>> findSubsequences(std::vector<int> nums) 
    {
        ss ans = {};
        st tmp = {};
        backtrack(nums, 0, INT32_MAX, ans, tmp);
        return ans;
    }
}