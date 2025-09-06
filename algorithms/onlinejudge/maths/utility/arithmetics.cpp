
#include <bits/stdc++.h>


namespace algorithms::onlinejudge::maths::utility::arithmetics
{
    int countDecimalDigits(double d) {
      // A small tolerance (epsilon) for floating-point comparisons.
      const double epsilon = 1e-9; 

      // Handle the integer case.
      if(std::abs(d - std::round(d)) < epsilon) {
        return 0;
      }

      int count = 0;
      double temp = d;

      // Loop until the number is very close to an integer.
      while(std::abs(temp - round(temp)) > epsilon) {
        temp *= 10.0;
        count++;
        // A safety break to prevent infinite loops for non-terminating
        // decimals like 1.0/3.0.
        if (count > 15) { // 15 is the typical precision limit for double
            return count; // or handle as an error
        }
      }
      return count;
    }

    // Calculates (base^exp)
    long long power(long long base, long long exp) {
      long long res = 1;
      while (exp > 0) {
        // If the current bit of exp is 1 (i.e., exp is odd)
        if(exp & 1) { res *= base; }
        // Square the base for the next bit position
        base *= base;
        // Move to the next bit of the exponent
        // This is equivalent to exp = exp / 2
        exp >>= 1;
      }
      return res;
    }

    long long __gcd(long long a, long long b) {
      if (b == 0)
       return a;
      return __gcd(b, a % b);
    }
}
