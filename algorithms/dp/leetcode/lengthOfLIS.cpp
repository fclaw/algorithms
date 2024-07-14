
#include <vector>
#include <iostream>

namespace algorithms::leetcode::dp
{
    /* 
       https://leetcode.com/problems/longest-increasing-subsequence
       Given an integer array nums, return the length of the longest strictly increasing subsequence
       We can write the state of this problem with just one parameter: i. 
       Let LIS(i) be the LIS ending at index i. 
       We know that LIS(0) = 1 as the first number in A is itself a subsequence. 
       For i ≥ 1, LIS(i) is slightly more complex. 
       We need to find the index j such that j < i and A[j] < A[i] and LIS(j) is the largest. 
       Once we have found this index j, we know that LIS(i) = 1 + LIS(j). We can write this recurrence formally as:
       1. LIS(0) = 1 // the base case
       2. LIS(i) = max(LIS(j) + 1), ∀j ∈ [0..i-1] and A[j] < A[i] // the recursive case, 
       one more than the previous best solution ending at j for all j < i.
       The answer is the largest value of LIS(k) ∀k ∈ [0..n-1].
    */ 
    std::tuple<int, std::vector<int>> lengthOfLIS(std::vector<int> nums) 
    {
        std::vector<int> dp(nums.size(), 1);
        // dp[0] = 1;
        for (int i = 1; i < dp.size(); i++)
          for (int j = 0; j < i; j++)
            if(nums[i] > nums[j])
              dp[i] = std::max(dp[i], 1 + dp[j]);

        auto first = dp.begin();
        auto last = dp.end();

        auto max_iter = max_element(first, last);
        int pos = max_iter - first;
  
        std::vector<int> lis;
        lis.push_back(nums[pos]);
        int i = pos - 1;
        while(i >= 0)
        {
            if(dp[i] == dp[pos] - 1 && 
               nums[i] < nums[pos])
            { 
                lis.push_back(nums[i]);
                pos = i;
                i--;
            }
            else i--;
        }

        std::reverse(lis.begin(), lis.end());

        return {*max_iter, lis};
    }
}