#include <vector>
#include <string>
#include <stack>

namespace algorithms::backtrack::leetcode::palindrome
{

using palindromes = std::vector<std::vector<std::string>>;
using st = std::vector<std::string>;


    // https://leetcode.com/problems/palindrome-partitioning
    /* 
       Given a string s, partition s such that 
       every substring of the partition is a palindrome
       Return all possible palindrome partitioning of s
    */
    palindromes ans;
    bool isPalindrome(const std::string& s) 
    {
        int l = 0;
        int r = s.size() - 1;
        while (l < r)
          if (s[l++] != s[r--])
            return false;
        return true;
    }
    void backtrack(const std::string& s, int idx, st xs, palindromes& ans)
    {
        if(idx == s.size())
        {
            bool res = true;
            for(auto x : xs)
              res &= isPalindrome(x);
            if(res) ans.push_back(xs);
            return;
        }

        auto ys = xs;
        ys.push_back(s.substr(idx, 1));
        backtrack(s, idx + 1, ys, ans);
        if(!ys.empty())
        {
            ys.pop_back();
            if(ys.size() >= 1)
            {
                auto p = ys.back();
                ys[ys.size() - 1] = p + s.substr(idx, 1);
                backtrack(s, idx + 1, ys, ans);
            }
        }
    }
    palindromes partition(std::string s) 
    {
        palindromes ans;
        backtrack(s, 0, {}, ans);
        return ans;
    }    
}