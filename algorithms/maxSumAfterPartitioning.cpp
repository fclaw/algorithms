#include <vector>
#include <iostream>

namespace leetcode::dp
{
    // https://leetcode.com/problems/partition-array-for-maximum-sum
    /*
      Given an integer array arr, partition the array into (contiguous) subArrays of length at most k. 
      After partitioning, each subArray has their values changed to become the maximum value of that subArray.
      Return the largest sum of the given array after partitioning.
    */
    int maxSumAfterPartitioningRecursive(std::vector<int> xs, int idx, int k, std::vector<int>& memo)
    {
        if(idx > xs.size())
          return 0;

        if(memo[idx] != -1)
          return memo[idx];

        int res = 0;
        int maxVal = 0;
        for (int i = 0; i < std::min((int)xs.size() - idx, k); i++)
        {
            maxVal = std::max(maxVal, xs[idx + i]);
            int localMax = maxSumAfterPartitioningRecursive(xs, idx + i + 1, k, memo);
            memo[idx + i + 1] = localMax;
            res = std::max(res, maxVal * (i + 1) + localMax);
        }
        
        return res;
    }

    int maxSumAfterPartitioningDp(std::vector<int> xs, int k)
    {
        return 0;
    }

    int maxSumAfterPartitioning(std::vector<int> xs, int k)
    {
        std::vector<int> memo(xs.size() + 1, -1); 
        return maxSumAfterPartitioningRecursive(xs, 0, k, memo); 
    }
}