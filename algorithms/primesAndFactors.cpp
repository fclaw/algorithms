#include <vector>
#include <iostream>

namespace algorithms::mathematics
{
    /*
      The following function prime checks if a given integer n is prime. The function
      attempts to divide n by all integers between 2 and ⌊√n⌋, and if none of them divides
      n, then n is prime.
    */
    bool isPrime(int n)
    {
        if(n < 2)
          return true;
        for (int x = 2; x * x <= n; x++)
          if(n % x == 0)
            return false;
        return true;
    }

    /*
      Then, the following function factors constructs a vector that contains the prime
      factorization of n. The function divides n by its prime factors and adds them to the
      vector. The process ends when the remaining number n has no factors between 2 and ⌊√n⌋.
      If n > 1, it is prime and the last factor.
    */
    std::vector<int> getFactors(int n)
    {
        std::vector<int> factors;
        for (int x = 2; x * x <= n; x++)
          while(n % x == 0)
          {
              factors.push_back(x);
              n /= x;
          }

        if(n > 1) 
          factors.push_back(n);
        
        return factors;
    }

    std::vector<int> sieveOfEratosthenes(int n)
    {
        std::vector<int> primes(n + 1, 0);
        primes[0] = 0;
        primes[1] = 0;
        for (int x = 2; x <= n; x++)
        {
            if(primes[x])
              continue;
            for (int u = 2 * x; u <= n; u += x)
              primes[u] = 1;
              
        }
        return primes;
    }

     // gcd(a, b)  a if b = 0, else gcd(b, a mod b) 
    int gcd(int a, int b)
    {
        if(b == 0)
          return a;
        return gcd(b, a %= b);
    }

    int modpow(int a, int b, int m) 
    { 
        if (b == 0) 
          return 1 % m;
        long long u = modpow(a, b/2, m);
        u = (u * u) % m;
        if (b % 2 == 1)
          u = (u * a) % m;
        return u; 
    }

    // Euclid’s algorithm can also be extended so that it gives integers x and y for which
    // ax + by = gcd(a, b)
    // the following function returns a tuple (x, y, gcd(a, b)) that satisfies the equation
    std::tuple<int, int, int> extendedEuclidAlgo(int a, int b)
    {
        if(b == 0)
          return {1, 0, a};

        int x, y, g;
        std::tie(x, y, g) = extendedEuclidAlgo(b, a % b);
        return {y, x - (a / b) * y, g};  
    }

    // binomial coefficients can be recursively computed using the formula:
    // base case: dp[n][0] ~ dp[n][n] = 1
    // recurrent equation: dp[n][k] = dp[n - 1][k - 1] + dp[n - 1][k] 
    unsigned long long binomialCoeffDP(int n, int k)
    {
        std::vector<std::vector<unsigned long long>> dp(n + 1, std::vector<unsigned long long>(k + 1, -1));

        for (int i = 0; i <= n; i++)
          for(int j = 0; j <= std::min(i, k); j++)
            if(j == 0 || j == i)
              dp[i][j] = 1;
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

        return dp[n][k];
    }
}