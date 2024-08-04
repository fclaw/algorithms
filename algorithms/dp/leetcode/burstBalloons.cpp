#pragma once
#include <vector>
#include <iostream>
#include <iomanip>  // for std::setw

using DP = std::vector<std::vector<int>>;

namespace algorithms::dp::leetcode
{
    // https://leetcode.com/problems/burst-balloons
    /*
      The optimal strategy can be found using dynamic programming by considering all possible ways 
      to burst balloons in different orders and storing the results of subproblems to avoid redundant calculations.

      Drawing a dynamic programming (DP) table is an effective way to visualize and understand the process of solving a problem using the DP approach. Here’s a step-by-step guide on how to draw and fill a DP table, using the "Burst Balloons" problem as an example.

      Steps to Draw a DP Table:
      - Identify the Dimensions:
        Determine the size of the DP table based on the problem. For the "Burst Balloons" problem, the table size is 
        (𝑛 + 2) × (𝑛 + 2) where n is the number of balloons in the original array. This accounts for the virtual balloons at the start and end.
        Label the Rows and Columns: Label the rows and columns with indices representing the subproblems. For the "Burst Balloons" problem, 
        the indices represent positions in the modified balloon array including the virtual balloons.
      - Initialize the Table:
         Fill the base cases of the table. For example, dp[i][i+1] is initialized to 0 because no coins are collected if there are no balloons between 
         𝑖 and 𝑖 + 1.
      - Fill the Table:
        Use the defined recurrence relation to fill the table iteratively. Calculate the values based on previously computed subproblems.
      - Extract the Result:
        The final result for the problem is typically found in one of the cells of the table, often related to the full range of the problem space.

        let left, right denote a range of balloons
        B(left, right) = n, max coins we can collect in the range from left to right

        supposing we pick up a k-th balloon to burst 
        recursive step:  B(l, r) = nums[k - 1] * nums[k] * nums[k + 1] + B(l, r - k) + B(k + 1, r)
        B(l, r - k) denotes maxCoins from the range (l, r - k)
        B(k + 1, r)  denotes maxCoins from the range (k +1, r)
        base case: B(0, 0) = 0
        [1, 3, 5] -> extended to [1, 3, 1, 5, 1],
        therefore the indices are shifted: the leftmost and rightmost indices are reserved for boundary balloons
        dp[0][i] and dp[n][i]  ought to be filled with 1
        loop starts from 1
    */
    int burstBalloonsDp(std::vector<int>& nums)
    {
        int n = nums.size();
        // insert at the beginning and the end
        // [1, x1, x2, ... xn, 1] where [x1 .. xn] the original array
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        // dp table
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));
        
        for (size_t l = 1; l <= n; l++) // length
          for(size_t left = 1; left <= n - l + 1; left++) // left
          {
            int right = l + left - 1;
            for (size_t k = left; k <= right; k++)
              dp[left][right] = std::max(dp[left][right], nums[left - 1] * nums[k] * nums[right + 1] + dp[left][k - 1] + dp[k + 1][right]);
          }
       
        return dp[1][n];
    }
}