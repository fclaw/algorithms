#include <functional>

namespace algorithms::math::leetcode::reverse_number
{
    /** https://leetcode.com/problems/reverse-integer */
    void doReverse(int n, int& reversed_n)
    {
        if(n == 0) return;
        int d = n % 10;
        // Check for overflow conditions before appending the digit. 
        // first condition stands for multiplication by 10, second for addition
        // Overflow if the number is about to go beyond the positive range
        if (reversed_n > (std::pow(2, 31) / 10) || 
            reversed_n == (std::pow(2, 31) / 10) && d > 7)
        {
            reversed_n  = 0;
            return;
        }
        // Underflow if the number is about to go beyond the negative range
        if (reversed_n < (std::pow(-2, 31) / 10) || 
            reversed_n == (std::pow(-2, 31) / 10) && d < -8)
        {
            reversed_n  = 0;
            return;
        }
        reversed_n = reversed_n * 10 + d;
        doReverse(n / 10, reversed_n);
    }
    int reverse(int n) 
    { 
        if(n == INT32_MIN)
          return 0;
        int reversed_n = 0;
        bool isNegative = n < 0;
        if(isNegative) n *= (-1);
        doReverse(n, reversed_n);
        return isNegative ? (-1) * reversed_n : reversed_n;
    }
}