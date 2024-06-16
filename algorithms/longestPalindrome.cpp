#include <string>
#include <unordered_map>
#include <iostream>

namespace leetcode::string
{
    // https://leetcode.com/problems/longest-palindrome
    // Given a string s which consists of lowercase or uppercase letters, 
    // return the length of the longest palindrome
    // that can be built with those letters.
    // Letters are case sensitive, for example, "Aa" is not considered a palindrome
    int longestPalindrome(std::string s) 
    {
        std::unordered_map<char, int> map;
        for (auto c : s)
          map[c]++;
        int maxlength = 0;
        int oddFrequencyFound = 0;
        std::for_each(
          map.begin(), 
          map.end(), 
          [&maxlength, &oddFrequencyFound](std::pair<char, int> p) 
          {
             int count = p.second;
             // Add the largest even part of count to palindromeLength
             maxlength += (count / 2) * 2;
             // Check if there's any odd frequency
             if (count % 2 == 1)
                oddFrequencyFound = true;
          });
          return oddFrequencyFound ? ++maxlength : maxlength;
    }
}