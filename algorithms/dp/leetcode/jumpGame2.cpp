#include <vector>
#include <iostream>

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/jump-game-ii
    /*
      You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].
      Each element nums[i] represents the maximum length of a forward jump from index i. 
      In other words, if you are at nums[i], you can jump to any nums[i + j] where:
        0 <= j <= nums[i]
        i + j < n
      Return the minimum number of jumps to reach nums[n - 1]. 
      The test cases are generated such that you can reach nums[n - 1]
    */
    int minJumps(std::vector<int> nums) 
    {
        int n = nums.size();
        int i = 0;
        int end = n - 1;
        int jumps = 0;
  
        while(i != end)
        {
            int k = 0;
            int maxJump = 0;
            int j = i + nums[i];
            if(j >= end)
            {
                jumps++;
                break;
            }
            while(j > i)
            {
              if(j + nums[j] > maxJump)
              {
                k = j;
                maxJump = j + nums[j];
              }
              j--;
            }
            i = k;
            jumps++;
        };

        return jumps;
    }
}