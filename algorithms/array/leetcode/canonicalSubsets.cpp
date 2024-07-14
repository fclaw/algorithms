#include <vector>
#include <iostream>


namespace algorithms::array::leetcode
{
    /* 
       https://leetcode.com/problems/subsets
       Given an integer array nums of unique elements, return all possible subsets (the power set).
       The solution set must not contain duplicate subsets. Return the solution in any order.
    */
    void rec(std::vector<int> xs, int i, std::vector<int> tmp, std::vector<std::vector<int>>& xxs)
    {
        int n = xs.size();
        if(i == n)
        {
           xxs.push_back(tmp);
           return;
        }

        auto ys = tmp;
        ys.push_back(xs[i]);
        rec(xs, i + 1, ys, xxs);
        if(!ys.empty())
          ys.pop_back();
        rec(xs, i + 1, ys, xxs); 
    }

    std::vector<std::vector<int>> bitset(std::vector<int> xs) 
    { 
        std::vector<std::vector<int>> ans = {};
        int n = xs.size();
        int s = 1;
        int p = (1 << n);
        while (s <= p)
        {
            std::vector<int> tmp;
            for (int j = 0; j < xs.size(); j++)
              if(s & (1 << j))
                tmp.push_back(xs[j]);
            ans.push_back(tmp);
            s++;
        }
        return ans;
    }

    std::vector<std::vector<int>> canonicalSubsets(std::vector<int> xs) { return bitset(xs); }
}