
#include <string>
#include <vector>
#include <iostream>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/decode-ways
    /*
      You have intercepted a secret message encoded as a string of numbers. 
      The message is decoded via the following mapping:
       "1" -> 'A'
       "2" -> 'B'
       ...
       "26" -> 'Z'
       However, while decoding the message, you realize that there are many different ways 
       you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").
       For example, "11106" can be decoded into
       "AAJF" with the grouping (1, 1, 10, 6)
       "KJF" with the grouping (11, 10, 6)
       The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid)
       Given a string s containing only digits, return the number of ways to decode it. 
       If the entire string cannot be decoded in any valid way, return 0.
    */
    int rec(std::string s, int i, std::vector<int>& memo)
    {
        if(i == 0 && s[0] != '0')
          return 1;
        if(i == 0 && s[0] == '0')
          return 0;

        if(i == 1 && s[1] == '0' && s[0] <= '2')
          return 1;

        if(i == 1 && s[1] == '0' && s[0] > '2')
          return 0;

        if(i == 1 && s[0] > '2')
          return 1;

        // if(i == 1)
        //   return 2;

        int &ways = memo[i];
        if(~ways) return memo[i];

        if(s[i] >= '1' && s[i] <= '6' && (s[i - 1] == '1' ||  s[i - 1] == '2'))
          return rec(s, i - 1, memo) + rec(s, i - 2, memo);
        else if(s[i] >= '1' && s[i] <= '9' && s[i - 2] > '2')
          return rec(s, i - 2, memo);
        else if(s[i] == '0' && (s[i - 1] == '1' ||  s[i - 1] == '2'))
          return rec(s, i - 1, memo);
        else return 0;
    }

    int viaDp(std::string s)
    {
        int n = s.size();
        std::vector<int> dp(n + 1, 0);
        
        dp[0] = 1;
        dp[1] = s[0] - '0' == 0 ? 0 : 1;
        for(int i = 2; i <= n; i++)
        {
            if (s[i - 1] != '0')
              dp[i] = dp[i - 1];
            if(s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '6')
              dp[i] += dp[i - 2];
        }

        return dp[n];
    }


    int numDecodings(std::string s) { return viaDp(s); }
}