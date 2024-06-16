#include <string>
#include <vector>

using DP = std::vector<std::vector<int>>;

namespace leetcode::dp
{
     
    // https://leetcode.com/problems/longest-palindromic-substring
    // Given a string s, return the longest palindromic substring in s
    // Objective fuction: P(i, j) = n, 
    // where i an j are the right and left boundaries, n - max palindrome within i, j
    std::string longestPalindromeDp(std::string str)
    {
        int n = str.size();
        DP dp(n, std::vector<int>(n, 0));
        return std::string();
    }

    std::string longestSubstringPalindrome(std::string s) { return longestPalindromeDp(s); }
}