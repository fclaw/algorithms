
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
    T mod_power(T base, T exp, T mod) {
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
    template<typename T = long long>
    T extended_euclid(T a, T b, T &x, T &y) {
      T xx = y = 0;
      T yy = x = 1;
      while (b) {                                    // repeats until b == 0
        T q = a / b;
        std::tie(a, b) = std::make_tuple(b, a % b);
        std::tie(x, xx) = std::make_tuple(xx, x - q * xx);
        std::tie(y, yy) = std::make_tuple(yy, y - q * yy);
      }
      return a;                                      // returns gcd(a, b)
    }

    template<typename T = long long>
    T mod(T a, T m) { return ((a % m) + m) % m; } // ensure positive answer

    enum ModInverseStatus { Failure, Success };
    template<typename T = long long>
    struct ModInverse {
      T val;
      ModInverseStatus status;
    };

    template<typename T = long long>
    ModInverse<T> modInverse(T b, T m) {               // returns b^(-1) (mod m)
      T x, y;
      T gcd = extended_euclid(b, m, x, y); // to get b * x + m * y == d
      if(gcd != 1) return { -1, Failure }; // to indicate failure
      // b * x + m * y == 1, now apply (mod m) to get b * x == 1 (mod m)
      return { mod(x, m), Success };
    }

    template<typename T = long long>
    T modInverse_fermat(T a, T p) { // Fermat’s little theorem, a and p are coprime
      return mod_power(a, p - 2, p);
    }

    template<typename T = long long>
    struct Diophantine {
      bool exists;
      T x;    // One particular solution for x
      T y;    // One particular solution for y
      T gcd;  // The greatest common divisor of the original coefficients a and b

      // To generate all solutions, use the formulas:
      // x_k = x + k * (b / gcd)
      // y_k = y - k * (a / gcd)
      // for any integer k.
    };

    template<typename T = long long>
    std::ostream& operator << (std::ostream& os, const Diophantine<T>& d) {
      return os << "{x: " << d.x << ", y: " << d.y << ", gcd: " << d.gcd << ", exists: " << d.exists << "}"; 
    }


    template<typename T = long long>
    Diophantine<T> diophantine_equation(T a, T b, T c) {
      // Handle edge case where a and b are both 0
      if(a == 0 && b == 0) {
        if (c == 0) {
        // 0x + 0y = 0 has infinite solutions. {0, 0} is one of them.
          return {true, 0, 0, 0};
        }
        // 0x + 0y = c (where c != 0) has no solution.
        return {false, 0, 0, 0};
      }

      T x0, y0;
      T g = extended_euclid(std::abs(a), std::abs(b), x0, y0);

      // Check for solvability
      if(c % g != 0) {
        return {false, 0, 0, g}; // No integer solution exists
      }

      // Scale the solution from ax + by = g  to  ax + by = c
      T factor = c / g;
      T final_x = x0 * factor;
      T final_y = y0 * factor;

      // Adjust signs for the original a and b
      if (a < 0) final_x = -final_x;
      if (b < 0) final_y = -final_y;

      return {true, final_x, final_y, g};
    }

    // Pre-calculated constants for performance
    const double PI = acos(-1.0);
    const double LOG10_OF_2_PI = log10(2.0 * PI);

    /**
     * Calculates an approximation of log10(n!) using Stirling's Approximation.
     * This is an O(1) operation and works for very large n.
     * Returns 0 for n=0 or n=1 as log10(1) = 0.
     */
    double stirling(int n) {
      if(n <= 1) {
        return 0.0;
      }
      // Using the more accurate version of Stirling's formula for ln(n!):
      // ln(n!) ≈ n*ln(n) - n + 0.5*ln(2*pi*n)
      // We convert to log10 by dividing by ln(10) which is log(10.0) in C++.
      return (double)n * log10((double)n) - (double)n / log(10.0) + 0.5 * (LOG10_OF_2_PI + log10((double)n));
    }

}
