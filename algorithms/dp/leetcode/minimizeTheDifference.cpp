#include <vector>
#include <iostream>
#include <unordered_map>


const int ROW = 70;
const int COL = 70;

namespace algorithms::dp::leetcode
{
    /*
      https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements
      You are given an m x n integer matrix mat and an integer target.
      Choose one integer from each row in the matrix such that the absolute difference between target
      and the sum of the chosen elements is minimized.
      Return the minimum absolute difference.
       The absolute difference between two numbers a and b is the absolute value of a - b
      
      hint: 
        Instead of keeping track of all possible sums, 
        since in each row, we are adding positive numbers, 
        only keep those that can be a candidate, 
        not exceeding the target by too much.
    */
     int memo[ROW][COL];
     int n;
     int m;
     int t;
     int rec(std::vector<std::vector<int>>& matrix, int r, int sum)
     {
        if(r == n)
          return std::abs(t - sum);

        int &ans = memo[r][sum];
        if(~ans) return ans;

        ans = INT32_MAX;
        for (int c = 0; c < m; c++)
          ans = std::min(ans, rec(matrix, r + 1, sum + matrix[r][c]));
        return ans;
     }

    int minimizeTheDifference(std::vector<std::vector<int>> matrix, int target) 
    {
        for(auto &x:memo)
          for(auto &y:x)
            y = -1;

        n = matrix.size();
        m = matrix[0].size();
        t = target;
        return rec(matrix, 0, 0);
    }
}