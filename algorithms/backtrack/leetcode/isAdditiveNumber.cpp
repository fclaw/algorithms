#include <string>
#include <vector>

using ull = unsigned long long;

namespace algorithms::backtrack::leetcode
{
    // https://leetcode.com/problems/additive-number
    /*
       An additive number is a string whose digits can form an additive sequence.
       A valid additive sequence should contain at least three numbers. 
       Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
       Given a string containing only digits, return true if it is an additive number or false otherwise.
    */
     int numDigits(int number)
    {
        int digits = 0;
        if (number < 0) digits = 1; // remove this line if '-' counts as a digit
        while (number) {
            number /= 10;
            digits++;
        }
        return digits;
    }  
    int SIZE;
    void backtrack(const std::string& s, int pos, std::vector<ull>& xs, bool& ans)
    {
        if(pos == SIZE)
        {
            if(xs.size() > 2)
              ans = true;
            return;
        }

        for(int offset = 1; offset <= SIZE - pos; offset++)
        {
            if(ans) break;
            if(offset > 1 && s[pos] == '0')
              break;
            if(!xs.empty() && 
               numDigits(xs.back()) > SIZE - pos)
              break;

            ull val = std::stoull(s.substr(pos, offset));
            if(xs.size() >= 2 &&
               val > *(xs.end() - 1) + *(xs.end() - 2))
              break;
            if(xs.size() >= 2 &&
               val < *(xs.end() - 1) + *(xs.end() - 2))
              continue;
            xs.push_back(val);
            backtrack(s, pos + offset, xs, ans);
            xs.pop_back();
        }
    }
    bool isAdditiveNumber(std::string s)
    {
        SIZE = s.size();
        std::vector<ull> xs;
        bool ans = false;
        backtrack(s, 0, xs, ans);
        return ans;
    }
}