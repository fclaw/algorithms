

namespace algorithms::leetcode::dp
{
    // https://leetcode.com/problems/integer-break
    // Given an integer n, break it into the sum of k positive integers, 
    // where k >= 2, and maximize the product of those integers.
    // Return the maximum product you can get.
    int rec(int n)
    {
        if(n == 2)
          return 1;
        if(n == 3)
          return 2;
        if(n == 4)
          return 4;
        if(n == 5)
          return 6;
        if(n == 6)
          return 9;  

       return 3 * rec(n - 3);
    }
    int integerBreak(int n) { return rec(n); }
}