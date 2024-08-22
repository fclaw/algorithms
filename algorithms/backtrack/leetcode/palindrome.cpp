#include <vector>
#include <string>
#include <stack>

namespace algorithms::backtrack::leetcode::palindrome
{

using palindromes = std::vector<std::vector<std::string>>;
using vc = std::vector<char>;

    // https://leetcode.com/problems/palindrome-partitioning
    /* 
       Given a string s, partition s such that 
       every substring of the partition is a palindrome
       Return all possible palindrome partitioning of s
    */
    const std::string empty_s = "";
    int S;
    palindromes ans;
    bool isPalindrome(std::string s)
    {
        bool res = true;
        int n = s.length();
        for (int i = 0; i < n / 2; i++)
          if (s[i] != s[n - i - 1])
          {
             res = false;
             break;
          }
        return res;
    }
    void dfs(const vc& xs, int idx, std::vector<std::string>& st)
    {
    }

    palindromes partition(std::string s) 
    {
        vc xs;
        for(auto c : s)
          xs.push_back(c);
        S = xs.size();  
        std::vector<std::string> st;
        st.push_back(empty_s);
        dfs(xs, 0, st);
        return ans;
    }    
}