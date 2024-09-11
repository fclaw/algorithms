#include <vector>
#include <string>

namespace algorithms::backtrack::leetcode::letter_combinations
{
    /**  
     * https://leetcode.com/problems/letter-combinations-of-a-phone-number
     * Given a string containing digits from 2-9 inclusive, return all possible letter combinations 
     * that the number could represent. Return the answer in any order.
     * A mapping of digits to letters (just like on the telephone buttons) is given below. 
     * Note that 1 does not map to any letters. */
    std::string acc;
    std::vector<std::string> ans;
    std::vector<std::pair<std::string, std::string>> keyboard = 
      {{"2", "abc"}, 
       {"3", "def"}, 
       {"4", "ghi"}, 
       {"5", "jkl"}, 
       {"6", "mno"}, 
       {"7", "pqrs"}, 
       {"8", "tuv"}, 
       {"9", "wxyz"}};
    void backtrack(const std::vector<std::string>& xs, int s)
    {

        if(acc.length() == xs.size())
        {
            ans.push_back(acc);
            return;
        }

        for(int i = s; i < xs.size(); i++)
          for(int j = 0; j < xs[i].length(); j++)
          {
              acc.push_back(xs[i][j]);
              backtrack(xs, i + 1);
              acc.pop_back();
          }
    }
    std::vector<std::string> letterCombinations(std::string digits) 
    {
        std::vector<std::string> xs;
        for(auto c : digits)
          for(auto p : keyboard)
            if(p.first == std::string(1, c))
               xs.push_back(p.second);
        backtrack(xs, 0);
        return ans;
    }
}