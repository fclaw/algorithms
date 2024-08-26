#include <vector>
#include <string>
#include <set>


namespace algorithms::backtrack::leetcode::letter_case_permutation
{
    /**
     *  https://leetcode.com/problems/letter-case-permutation
     * Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string
     * Return a list of all possible strings we could create. Return the output in any order
     * on time complexity:
     * Assume a string of size L.
     * We have two choices per character (uppercase, lowercase).
     * In the worst case, we may be changing all characters and therefore copy all combinations of those. => O(2 ^ L * L)
    */
    int N;
    std::vector<std::string> ans;
    int choice = 0;
    void flip(std::string& s, int idx)
    {
        if((choice & (1 << idx))) { 
          s[idx] = std::tolower(s[idx]);
          choice &= ~(1 << idx);
        }
        else {
          s[idx] = std::toupper(s[idx]);
          choice |= (1 << idx);
        }
    }
    void backtrack(std::string& s, int idx, std::string& t)
    {
        if(idx == N)
        {
            ans.push_back(t);
            return;
        }

        t.push_back(s[idx]);   
        backtrack(s, idx + 1, t);
        t.pop_back();
        if(std::isalpha((int)s[idx]))
        {
            flip(s, idx);
            t.push_back(s[idx]);
            backtrack(s, idx + 1, t);
            t.pop_back();
        }
    }
    std::vector<std::string> letterCasePermutation(std::string& s) 
    {
        N = s.size();
        std::string t;
        for(int i = 0; i < N; i++)
          if(std::isalpha((int)s[i]) && 
             std::isupper(s[i])) 
             choice |= (1 << i);    
        backtrack(s, 0, t);
        return ans;
    }
}