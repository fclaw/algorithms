#include <vector>
#include <unordered_set>

// https://leetcode.com/problems/longest-consecutive-sequence
int longestConsecutive(std::vector<int>& nums) 
{
    std::unordered_set<int> hash(nums.begin(), nums.end());
    int longest_streak = 0;
    
    for(auto x : hash)
    {
         // Check if 'num' is the start of a sequence
        if (hash.find(x - 1) == hash.end()) {
            int current_num = x;
            int current_streak = 1;

            // Incrementally find the length of the sequence
            while (hash.find(current_num + 1) != hash.end()) {
                current_num += 1;
                current_streak += 1;
            }

            // Update the longest streak found
            longest_streak = std::max(longest_streak, current_streak);
        }
    }
    return longest_streak;
}