#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cctype>
#include <unordered_set>

namespace algorithms::graph::leetcode::invalid_parentheses
{

using state = std::tuple<std::string, int>;

    /**
     * https://leetcode.com/problems/remove-invalid-parentheses
     * Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses 
     * to make the input string valid.
     * Return a list of unique strings that are valid with the minimum number of removals. 
     * You may return the answer in any order. 
     * hints: Since we do not know which brackets can be removed, we try all the options! We can use recursion
     * In the recursion, for each bracket, we can either use it or remove it.
     * Recursion will generate all the valid parentheses strings but we want the ones with the least number of parentheses deleted.
     * We can count the number of invalid brackets to be deleted and only generate the valid strings in the recursion. */
    std::unordered_set<std::string> visited;
    std::vector<std::string> ans;
    bool finished = false;
    bool isValid(const std::string& s) 
    {
        std::stack<int> st;
        for (auto i : s)
        {
            if(std::isalpha(i))
              continue;
            if(i=='(') st.push(i);
            else 
            {
                if(st.empty() || 
                   (st.top()=='(' && i!=')'))
                  return false;
                else st.pop();
            }
        }
        return st.empty();
    }
    void bfs(std::queue<state> q)
    {
        while(!q.empty())
        {
            state st = q.front();
            q.pop();
            std::string s;
            int size, l;
            std::tie(s, size) = st;

            if(isValid(s))
            {
               ans.push_back(s);
               finished = true;
            }
            
            if(finished) continue;

            for(int i = 0; i < size; i++)
            {
                if((bool)std::isalpha(s[i]))
                  continue;
                std::string tmp = s;
                tmp.erase(tmp.begin() + i);
                if(auto it = visited.find(tmp); 
                   it != visited.end())
                  continue;
                visited.insert(tmp);
                q.push({tmp, tmp.length()});
            }
        }
    }
    std::vector<std::string> removeInvalidParentheses(std::string s)
    {
        std::queue<state> q;
        q.push({s, s.length()});
        visited.insert(s);
        bfs(q);
        return ans;
    }
}