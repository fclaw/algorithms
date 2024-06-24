#include <string>
#include "longestCommonSubsequence.cpp"

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/delete-operation-for-two-strings
    // Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
    // In one step, you can delete exactly one character in either string.
    int minDistance(std::string word1, std::string word2) 
    {
        int l = algorithms::leetcode::dp::longestCommonSubsequence(word1, word2);
        return word1.size() + word2.size() - 2* l; 
    }
}