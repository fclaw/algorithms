#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <optional>

using SubstringPalindromeMemo = std::vector<std::vector<std::string>>;
using SubstringPalindromeDp = std::vector<std::vector<std::string>>;
using SubstringPalindromeTupleDp = std::vector<std::vector<std::pair<int, int>>>;

void printSubstringPalindromeDp(SubstringPalindromeDp dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row ) 
          std::cout << std::setw(5) << s << ' ';
        std::cout << std::endl;
    }
}

namespace algorithms::leetcode::dp
{
     
    // https://leetcode.com/problems/longest-palindromic-substring
    // Given a string s, return the longest palindromic substring in s
    bool isPalindrome(std::string s, int f, int l) 
    {
        bool isSame = true;
        while(f < l)
        {
            if(s[f] != s[l])
            {
              isSame = false;
              break;
            }
            f++;
            l--;
        }
        return isSame;
    }
    
    std::string longestSubstringPalindromeRec(std::string s, int i, int j, SubstringPalindromeMemo& memo)
    {
        if(i == j) return s.substr(i, 1);

        if(memo[i][j] != std::string())
          return memo[i][j];

        if(isPalindrome(s, i, j))
          return s.substr(i, j - i + 1);

        auto r = longestSubstringPalindromeRec(s, i + 1, j, memo);
        auto l = longestSubstringPalindromeRec(s, i, j - 1, memo);

        memo[i][j] = r.size() > l.size() ? r : l;
        return memo[i][j];
    }

    std::string longestSubstringPalindromeDp(std::string s)
    {
        int n = s.size();
        SubstringPalindromeTupleDp dp(n, std::vector<std::pair<int, int>>(n, {-1, -1}));

        for (int i = 0; i < n; i++)
          dp[i][i] = {i, i};
        
        for(int i = n - 2; i >= 0; i--)
          for(int j = i + 1; j < n; j++)
          {
               if(s[i] == s[j] &&
                  isPalindrome(s, i + 1, j - 1))
                 dp[i][j] = {i, j};
               else
                 if(dp[i][j - 1].second - dp[i][j - 1].first > dp[i + 1][j].second - dp[i + 1][j].first)
                   dp[i][j] = dp[i][j - 1];
                 else dp[i][j] = dp[i + 1][j];
          }
        auto res = dp[0][n - 1];
        
        int f = res.first;
        int l = res.second;

        return s.substr(f, l - f + 1);
    }

    std::string longestSubstringPalindrome(std::string s) { return longestSubstringPalindromeDp(s); }
}