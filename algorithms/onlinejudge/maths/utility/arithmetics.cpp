
#include "big_integer.cpp"
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class



namespace bg = algorithms::onlinejudge::maths::utility::big_integer;
namespace mp = boost::multiprecision;

using ll = long long;


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

    // In your arithmetics library
    template<typename T = long long>
    T mod_multiply(T a, T b, T mod) {
        T res = 0;
        a %= mod;
        while (b > 0) {
            if (b % 2 == 1) {
                res = (res + a) % mod;
            }
            a = (a * 2) % mod;
            b /= 2;
        }
        return res;
    }

    // In your arithmetics library
    template<typename T = long long>
    T mod_add(T a, T b, T mod) {
        a %= mod;
        b %= mod;
        // The addition can exceed 'mod' but is safe from overflowing T.
        T res = a + b; 
        // If res >= mod, subtract mod to bring it back into the [0, mod-1] range.
        if (res >= mod) {
            res -= mod;
        }
        // This is equivalent to (a + b) % mod but can be slightly faster
        // as it avoids a division/modulo operation.
        return res;
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

    // Your generic modInverse function
    template<typename T = long long>
    ModInverse<T> modInverse(T b, T m) {
      long long x, y;

      // --- THE FIX ---
      // Cast the unsigned inputs to signed long long for the internal calculation.
      long long b_ll = static_cast<long long>(b);
      long long m_ll = static_cast<long long>(m);

      long long gcd = extended_euclid(b_ll, m_ll, x, y);

      if (gcd != 1) {
        return { static_cast<T>(-1), Failure }; // Inverse doesn't exist
      }

      // The result 'x' is a signed long long. We need to convert it
      // back to the requested type T (e.g., unsigned long long).
      // The 'mod' helper function correctly handles negative x.
      return { static_cast<T>(mod(x, m_ll)), Success };
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

    std::vector<ll> factorial;
    std::vector<ll> invFactorial;

    // Pre-computation function (run once)
    void precompute_fact_and_fact_inv_mod(ll n_max, ll mod) {
      factorial.resize(n_max + 1);
      invFactorial.resize(n_max + 1);

      factorial[0] = 1;
      for (int i = 1; i <= n_max; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
      }

      ModInverse<ll> res = modInverse(factorial[n_max], mod);
      // Assert that the inverse must exist. If this fails, it means our 
      // mathematical approach is invalid for the given 'n_max' and 'mod'
      // (because n_max! is not coprime to the modulus).
      assert(res.status == Success);
      invFactorial[n_max] = res.val;
      for (int i = n_max - 1; i >= 0; i--) {
        invFactorial[i] = mod_multiply(invFactorial[i + 1], (ll)i + 1, mod);
      }
    }


    ll combinations(ll n, ll k, ll mod) {
      if (k < 0 || k > n) return 0;
      ll num = factorial[n];
      ll den = mod_multiply(invFactorial[k], invFactorial[n - k], mod);
      return mod_multiply(num, den, mod);
    }

    bg::bigint combinations_bigint(int n, int k) {
      if (k < 0 || k > n) {
        return bg::bigint(0);
      }
    
      // Use the symmetry C(n, k) = C(n, n-k) for a massive speedup
      // when k is large.
      if (k > n / 2) {
        k = n - k;
      }

      if(k == 0) {
        return bg::bigint(1);
      }
    
      bg::bigint numerator(1);
      bg::bigint denominator(1);
    
      // Calculate the numerator: n * (n-1) * ... * (n-k+1)
      // and denominator: k!
      for(int i = 1; i <= k; ++i) {
        numerator = numerator * bg::bigint(n - i + 1);
        denominator = denominator * bg::bigint(i);
      }

      // The final result is numerator / denominator.
      // Your BigInt library must have a correct division operator.
      return numerator / denominator;
    }


    mp::cpp_int combinations_bigint_boost(int n, int k) {
      if (k < 0 || k > n) {
        return 0;
      }
    
      // Use the symmetry C(n, k) = C(n, n-k) for a massive speedup
      // when k is large.
      if (k > n / 2) {
        k = n - k;
      }

      if(k == 0) {
        return 1;
      }
    
      mp::cpp_int numerator(1);
      mp::cpp_int denominator(1);
    
      // Calculate the numerator: n * (n-1) * ... * (n-k+1)
      // and denominator: k!
      for(int i = 1; i <= k; ++i) {
        numerator = numerator * mp::cpp_int(n - i + 1);
        denominator = denominator * mp::cpp_int(i);
      }

      // The final result is numerator / denominator.
      // Your BigInt library must have a correct division operator.
      return numerator / denominator;
    }


    // O(1) query for a single Catalan number
    ll catalan_formula(ll n, ll mod) {
      ll term1 = combinations(2 * n, n, mod);
      ModInverse<ll> res = modInverse(n + 1, mod);
      // Assert that the inverse must exist. If this fails, it means our 
      // mathematical approach is invalid for the given 'n + 1' and 'mod'
      // (because (n + 1)! is not coprime to the modulus).
      assert(res.status == Success);
      ll term2 = res.val;
      return mod_multiply(term1, term2, mod);
    }

    // O(N) pre-computation for all Catalan numbers up to n_max
    std::vector<ll> catalan_all(int n_max, ll mod) {
      std::vector<ll> Cat(n_max + 1);
      Cat[0] = 1;
      for (int n = 1; n <= n_max; ++n) {
        ll numerator = 4LL * n - 2;
        ll denominator = n + 1;
        ModInverse<ll> res = modInverse(denominator, mod);
        // Assert that the inverse must exist. If this fails, it means our 
        // mathematical approach is invalid for the given 'n_max' and 'mod'
        // (because n_max! is not coprime to the modulus).
        assert(res.status == Success);
        ll inv_denom = res.val;
        ll term1 = mod_multiply(numerator, Cat[n - 1], mod);
        Cat[n] = mod_multiply(term1, inv_denom, mod);
      }
      return Cat;
    }

    bg::bigint catalan_all_bigint_rec(int n, std::unordered_map<int, bg::bigint>& memo) {
      if(n == 0) return 1;

      if(memo.count(n)) 
        return memo[n];

      bg::bigint ways(0);
      // C_n = Sum C_i * C_{n-1-i}, Catalan recurrence 
      for(int i = 0; i < n; ++i) {
        // Break the problem into a left subproblem of 'i' elements
        // and a right subproblem of 'n - 1 - i' elements.
        ways += catalan_all_bigint_rec(i, memo) * catalan_all_bigint_rec(n - 1 - i, memo);
      }
      return memo[n] = ways;
    }

    std::vector<bg::bigint> catalan_all_bigint(int n_max) {
      std::unordered_map<int, bg::bigint> memo;
      std::vector<bg::bigint> Cat(n_max + 1);
      Cat[0] = bg::bigint(1);
      for(int n = 1; n <= n_max; ++n) {
        Cat[n] = catalan_all_bigint_rec(n, memo);
      }
      return Cat;
    }

    mp::cpp_int catalan_all_bigint_boost_rec(int n, std::unordered_map<int, mp::cpp_int>& memo) {
      if(n == 0) return 1;

      if(memo.count(n)) 
        return memo[n];

      mp::cpp_int ways(0);
      // C_n = Sum C_i * C_{n-1-i}, Catalan recurrence 
      for(int i = 0; i < n; ++i) {
        // Break the problem into a left subproblem of 'i' elements
        // and a right subproblem of 'n - 1 - i' elements.
        ways += catalan_all_bigint_boost_rec(i, memo) * catalan_all_bigint_boost_rec(n - 1 - i, memo);
      }
      return memo[n] = ways;
    }

    std::vector<mp::cpp_int> catalan_all_boost_bigint(int n_max) {
      std::unordered_map<int, mp::cpp_int> memo;
      std::vector<mp::cpp_int> Cat(n_max + 1);
      Cat[0] = 1;
      for(int n = 1; n <= n_max; ++n) {
        Cat[n] = catalan_all_bigint_boost_rec(n, memo);
      }
      return Cat;
    }

    std::vector<ll> super_catalans_all(int n_max) {
      std::vector<ll> s(n_max + 1);

      // Set the correct base cases
      if (n_max >= 0) s[0] = 1;
      if (n_max >= 1) s[1] = 1;

      // DP loop using the recurrence
      for (int n = 2; n <= n_max; ++n) {
        long long term1 = (6LL * n - 3) * s[n - 1];
        long long term2 = (long long)(n - 2) * s[n - 2];
        
        // The division by (n+1) is guaranteed to be clean (no remainder).
        s[n] = (term1 - term2) / (n + 1);
      }
      return s;
    }

    std::vector<bg::bigint> super_catalans_all_bigint(int n_max) {
      std::vector<bg::bigint> s(n_max + 1);

      // Set the correct base cases
      if (n_max >= 0) s[0] = bg::bigint(1);
      if (n_max >= 1) s[1] = bg::bigint(1);


      // DP loop using the recurrence
      for (int n = 2; n <= n_max; ++n) {
        bg::bigint term1 =  (6LL * n - 3) * s[n - 1];
        bg::bigint term2 = (long long)(n - 2) * s[n - 2];
        bg::bigint divisor = bg::bigint(n + 1);
        
        // The division by (n+1) is guaranteed to be clean (no remainder).
        s[n] = (term1 - term2) / divisor;
      }
      return s;
    }

    std::vector<mp::cpp_int> super_catalans_all_bigint_boost(int n_max) {
      std::vector<mp::cpp_int> s(n_max + 1);

      // Set the correct base cases
      if (n_max >= 0) s[0] = 1;
      if (n_max >= 1) s[1] = 1;


      // DP loop using the recurrence
      for (int n = 2; n <= n_max; ++n) {
        mp::cpp_int term1 =  (6LL * n - 3) * s[n - 1];
        mp::cpp_int term2 = (long long)(n - 2) * s[n - 2];
        mp::cpp_int divisor = n + 1;
        
        // The division by (n+1) is guaranteed to be clean (no remainder).
        s[n] = (term1 - term2) / divisor;
      }
      return s;
    }
}
