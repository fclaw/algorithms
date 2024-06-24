#include <string>
#include <vector>
#include <iostream>

using DP = std::vector<std::vector<int>>;

namespace leetcode::dp
{
     
    // https://leetcode.com/problems/longest-palindromic-substring
    // Given a string s, return the longest palindromic substring in s
    // Objective fuction: P(i, j) = n ?? (p[i1, j2], bool) - p-is the max palindrome in i,j, bool whether i-j is a palindrome , 
    // where i an j are the right and left boundaries, n - max palindrome within i, j
    int longestPalindromeDp(std::string str)
    {
        int n = str.size();
        DP dp(n + 1, std::vector<int>(n + 1, 0));
 
        // .... ???

        return dp[0][n];
    }

    int longestSubstringPalindrome(std::string s) { return longestPalindromeDp(s); }
}