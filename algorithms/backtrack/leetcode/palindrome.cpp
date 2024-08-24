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
    void backtrack(const std::string& s, int idx, st& xs, palindromes& ans)
    {
        if(idx == s.size())
        {
            bool res = true;
            for(auto x : xs)
              res &= isPalindrome(x);
            if(res) ans.push_back(xs);
            return;
        }
        xs.push_back(s.substr(idx, 1));
        backtrack(s, idx + 1, xs, ans);
        if(!xs.empty())
        {
            xs.pop_back();
            if(xs.size() >= 1)
            {
                auto p = xs.back();
                xs[xs.size() - 1] = p + s.substr(idx, 1);
                backtrack(s, idx + 1, xs, ans);
            }
        }
    }
    palindromes partition(std::string s) 
    {
        palindromes ans;
        std::vector<std::string> tmp;
        backtrack(s, 0, tmp, ans);
        return ans;
    }    
}