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
    int S;
    const std::string empty_s = "";
    palindromes ans;
    bool isPalindrome(std::string s) 
    {
        std::string r = s;
        std::reverse(r.begin(), r.end());
        return r == s;
    }
    void dfs(std::string s, int idx, st& storage)
    {
        if(idx == S)
        {
            auto tmp = storage;
            ans.push_back(tmp);
            return;
        }

        for(int i = idx; i < S; i++)
        {
            auto prev = storage.back();
            if(isPalindrome(prev + s[i]))
            {
                storage.pop_back();
                prev.push_back(s[i]);
                storage.push_back(prev);
            } else storage.push_back(s.substr(i, 1));
            dfs(s, i + 1, storage);
          
            if(!storage.empty())
            {
                auto tmp = storage.back();
                storage.pop_back();
                if(tmp.size() > 1)
                {
                    auto n = std::string(1, tmp.back());
                    tmp.pop_back();
                    storage.push_back(tmp);
                    storage.push_back(n);
                } else break;
            }
        }
    }

    palindromes partition(std::string s) 
    {
        S = s.size();
        st storage(1, empty_s);
        dfs(s, 0, storage);
        return ans;
    }    
}