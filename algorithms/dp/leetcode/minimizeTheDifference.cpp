#include <vector>
#include <iostream>
#include <iomanip>


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
    //  std::vector<int> rec(std::vector<std::vector<int>> rect, int r, int c)
    //  {
    //      // ???
    //  }

    // F(i, j, prev) = n
    int minimizeTheDifference(std::vector<std::vector<int>> xxs, int target) 
    {
        return 0;
    }
}