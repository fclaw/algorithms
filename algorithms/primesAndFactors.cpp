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
}