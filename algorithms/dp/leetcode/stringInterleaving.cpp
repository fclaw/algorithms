#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/interleaving-string
    // Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
    // An interleaving of two strings s and t is a configuration where s and t are divided into n and m 
    // substrings respectively, such that:
    // s = s1 + s2 + ... + sn
    // t = t1 + t2 + ... + tm
    // |n - m| <= 1
    // The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
    // Note: a + b is the concatenation of strings a and b
    bool isInterleaveRecursive(std::string s1, int n, std::string s2, int m,  std::string s3, int k)
    {
        if(n == s1.size() && 
           m == s2.size() && 
           k == s3.size())
          return true;

        if(k == s3.size())
          return false;
      
        if(n == s1.size() && 
           m == s2.size())
          return false;

        bool first = false;
        bool second = false;
 
        if(n < s1.size() && *(s1.begin() + n) == *(s3.begin() + k))
          first = isInterleaveRecursive(s1, n + 1, s2, m, s3, k + 1);

        if(m < s2.size() && *(s2.begin() + m) == *(s3.begin() + k))
          second = isInterleaveRecursive(s1, n, s2, m + 1, s3, k + 1);

        return first || second;
    }

    using IsInterleaveDp = std::vector<std::vector<bool>>;

    void printIsInterleaveDp(IsInterleaveDp dp)
    {
        for ( const auto &row : dp )
        {
            for ( const auto &s : row ) 
            std::cout << std::setw(5) << s << ' ';
            std::cout << std::endl;
        }
    }

    bool isInterleaveDp(std::string s1, std::string s2, std::string s3)
    {
        int m = s1.size();
        int n = s2.size();
        IsInterleaveDp dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;

        // s1 is empty
        for (int i = 1; i <= n; i++)
          dp[0][i] = dp[0][i - 1] && s2[i - 1] == s3[i - 1];

        // s2 is empty
        for (int i = 1; i <= m; i++)
          dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];


        for (size_t i = 1; i <= m; i++)
          for (size_t j = 1; j <= n; j++)
          {
              if(s1[i - 1] == s3[i + j - 1] && 
                 s2[j - 1] != s3[i + j - 1])
                dp[i][j] = dp[i - 1][j];

              if(s1[i - 1] != s3[i + j - 1] && 
                 s2[j - 1] == s3[i + j - 1])
                dp[i][j] = dp[i][j - 1];

              if(s1[i - 1] == s3[i + j - 1] && 
                 s2[j - 1] == s3[i + j - 1])
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];     
          }

        printIsInterleaveDp(dp);

        return dp[m][n];
    }

    bool isInterleave(std::string s1, std::string s2, std::string s3) { return isInterleaveDp(s1, s2, s3); }
} // namespace name
