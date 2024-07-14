#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <optional>

using SubstringPalindromeMemo = std::vector<std::vector<std::string>>;
using SubstringPalindromeDp = std::vector<std::vector<std::string>>;
using SubstringPalindromeTupleDp = std::vector<std::vector<std::tuple<int, int, std::optional<bool>>>>;
  

void printSubstringPalindromeDp(SubstringPalindromeTupleDp dp)
{
    for ( const auto &row : dp )
    {
        for ( const auto &s : row )
        {
            int f, l;
            std::optional<bool> isPal;
            std::tie(f, l, isPal) = s;
            std::cout << std::setw(7) << "{ i: " << f << ", j: " <<  l << " }" << ' ';
        }
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
        SubstringPalindromeTupleDp dp(n, std::vector<std::tuple<int, int, std::optional<bool>>>(n, {-1, -1, std::nullopt}));

        for (int i = 0; i < n; i++)
          dp[i][i] = {i, i, true};

        for(int i = n - 2; i >= 0; i--)
          for(int j = i + 1; j < n; j++)
          {
               int f, l;
               std::optional<bool> isP;
               std::tie(f, l, isP) = dp[i + 1][j - 1];
               
               if(!isP.has_value())
               {
                  auto r = l - f == (j - 1) - (i + 1) + 1;
                  dp[i + 1][j - 1] = {f, l, r};
                  isP = r;
               }

               if(s[i] == s[j] && isP.value())
                 dp[i][j] = {i, j, true};
               else
               {
                   int li, lj, di, dj;
                   std::optional<bool> left_is_p, down_is_p;
                   std::tie(li, lj, left_is_p) = dp[i][j - 1];
                   std::tie(di, dj, down_is_p) = dp[i + 1][j]; 
                   if(lj - li > dj - di)
                      dp[i][j] = {li, lj, false};
                   else dp[i][j] = {di, dj, false};
                }
          }

        auto res = dp[0][n - 1];
        
        int f, l;
        std::optional<bool> isP;
        std::tie(f, l, isP) = res;
        return s.substr(f, l - f + 1);
    }

    std::string longestSubstringPalindrome(std::string s) { return longestSubstringPalindromeDp(s); }
}