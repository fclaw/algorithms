
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
    template<typename T = long long>
    T power(T base, T exp) {
      T res = 1;
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

    // Calculates (base^exp % mod)
    template<typename T = long long>
    T power_mod(T base, T exp, T mod) {
      T res = 1;
      base %= mod; // Initial reduction
      while (exp > 0) {
        // If the current bit of exp is 1 (i.e., exp is odd)
        if(exp & 1)
        // Apply modular multiplication here
        { res = (res * base) % mod; }
        // Square the base for the next bit position
        base = (base * base) % mod;
        // Move to the next bit of the exponent
        // This is equivalent to exp = exp / 2
        exp >>= 1;
      }
      return res;
    }

    template<typename T = long long>
    T __gcd(T a, T b) {
      if (b == 0)
       return a;
      return __gcd(b, a % b);
    }

    template<typename T = long long>
    T __lcm(T a, T b) {
      return (a * b) / __gcd(a, b);
    }

    // Function for extended Euclidean Algorithm 
    int extended_euclid(int a, int b, int &x, int &y) {
      // Base Case 
      if(a == 0) {
        x = 0; 
        y = 1; 
        return b; 
      } 

      int x1, y1; 
      int gcd = extended_euclid(b % a, a, x1, y1); 

      // Update x and y using results of 
      // recursive call 
      x = y1 - (b / a) * x1; 
      y = x1;
      return gcd; 
    }
}
