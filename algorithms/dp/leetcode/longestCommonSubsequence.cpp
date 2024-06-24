#include <string>
#include <vector>


namespace algorithms::leetcode::dp
{
    /*
    https://leetcode.com/problems/longest-common-subsequence
    Given two strings text1 and text2, return the length of their longest common subsequence. 
    If there is no common subsequence, return 0.
    A subsequence of a string is a new string generated 
    from the original string with some characters (can be none) deleted 
    without changing the relative order of the remaining characters.
    For example, "ace" is a subsequence of "abcde".
    A common subsequence of two strings is a subsequence that is common to both strings.
    */
    int longestCommonSubsequenceRec(std::string text1, int first, std::string text2, int second, std::vector<std::vector<int>>& memo)
    {
        if(first >= text1.size() || second >= text2.size())
          return 0;

        if(memo[first][second] != -1)
          return memo[first][second];

        int excludeChFromFirst = longestCommonSubsequenceRec(text1, first + 1, text2, second, memo);
        int excludeChFromSecond = longestCommonSubsequenceRec(text1, first, text2, second + 1, memo);

        memo[first + 1][second] = excludeChFromFirst;
        memo[first][second + 1] = excludeChFromSecond;

        if(text1[first] == text2[second])
        {
          int res =  1 + longestCommonSubsequenceRec(text1, first + 1, text2, second + 1, memo);
          memo[first + 1][second + 1] = res;
          return res;
        }
        else return std::max(excludeChFromFirst, excludeChFromSecond);
    }

    int longestCommonSubsequenceDp(std::string text1, std::string text2)
    {
        int n = text1.size();
        int m = text2.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

        for (size_t f = 1; f <= n; f++)
          for (size_t s = 1; s <= m; s++)
            if(text1[f - 1] == text2[s - 1])
              dp[f][s] = 1 + dp[f - 1][s - 1];
            else dp[f][s] = std::max(dp[f - 1][s], dp[f][s - 1]);   

        return dp[n][m];
    }


    int longestCommonSubsequence(std::string text1, std::string text2) { return longestCommonSubsequenceDp(text1, text2); }
}