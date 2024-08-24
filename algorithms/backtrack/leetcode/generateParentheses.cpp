#include <vector>
#include <string>
#include <stack>

namespace algorithms::backtrack::leetcode::gp
{

using parenthesis = std::vector<std::string>;

    /** 
     * https://leetcode.com/problems/generate-parentheses
     * Given n pairs of parentheses, write a function 
     * to generate all combinations of well-formed parentheses
     * Given N pairs of parentheses, find all solutions.
     * There are 2N characters we have to fill. For each character, we have two choices "(" or ")".
     * The total number of nodes = 2^(2N) = 4^N Copy operation = O(2N) = O(N) => O(N * 4^N)
     * Again, we don't technically copy all combinations, just the valid ones, but we are certain it will never be worse than this 
     * */
    int N;
    const char l_unit = '(';
    const char r_unit = ')';
    bool isValid(const std::string& s)
    {
        std::stack<char> st;
        bool res = true;
        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] == l_unit)
                st.push(s[i]);
            else if(s[i] == r_unit)
            {
                if(st.empty() || 
                   st.top() != l_unit || 
                   s[i] != r_unit)
                   {
                      res = false;
                      break;
                   }
                else st.pop();
            }
        }
        return st.empty() && res;
    }    
    void backtrack(int n, std::string s, parenthesis& ans) 
    {
        if(n == N)
        {
            if(isValid(s))
              ans.push_back(s);
            return;
        }

        auto ls = s;
        ls.push_back(l_unit);
        backtrack(n + 1, ls, ans);
        ls.pop_back();
        ls.push_back(r_unit);
        backtrack(n + 1, ls, ans);
    }
    parenthesis generateParentheses(int n) 
    {
        N = 2 * n;
        parenthesis ans;
        backtrack(0, {}, ans);
        return ans;
    }
}