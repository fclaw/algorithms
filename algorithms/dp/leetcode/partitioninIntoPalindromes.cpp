#include <vector>
#include <string>

using vvp = std::vector<std::vector<std::string>>;

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/palindrome-partitioning
    /* 
       Given a string s, partition s such that 
       every substring of the partition is a palindrome
       Return all possible palindrome partitioning of s
    */
    std::vector<std::string> rec(std::string s, int idx, vvp& ans)
    {
        return {};
    }

    vvp partition(std::string s) 
    {
        xxs ans = {};
        rec(s, 0, ans);
        return ans;
    }
    
}