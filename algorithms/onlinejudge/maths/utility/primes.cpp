// courtesy of https://cpbook.net, ch5/primes.cpp

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef unordered_map<ll, int> map_ll_i;


namespace algorithms::onlinejudge::maths::utility::primes
{

    ll _sieve_size;
    bitset<10000010> bs;                             // 10^7 is the rough limit
    vll p;                                           // compact list of primes

    void sieve(ll upperbound) {                      // range = [0..upperbound]
      _sieve_size = upperbound + 1;                  // to include upperbound
      bs.set();                                      // all 1s
      bs[0] = bs[1] = 0;                             // except index 0+1
      for (ll i = 2; i < _sieve_size; ++i) if (bs[i]) {
        // cross out multiples of i starting from i*i
        for (ll j = i*i; j < _sieve_size; j += i) bs[j] = 0;
        p.push_back(i);                              // add prime i to the list
      }
    }

    bool isPrime(ll N) {                             // good enough prime test
      if (N < _sieve_size) return bs[N];             // O(1) for small primes
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        if (N % p[i] == 0)
          return false;
      return true;                                   // slow if N = large prime
    } // note: only guaranteed to work for N <= (last prime in vll p)^2


    auto nearest_prime_low(ll n) { return std::lower_bound(p.begin(), p.end(), n); }
    auto nearest_prime_up(ll n) { return std::upper_bound(p.begin(), p.end(), n); }

    // second part

    vll primeFactors(ll N) {                         // pre-condition, N >= 1
      vll factors;
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N % p[i] == 0) {                        // found a prime for N
          N /= p[i];                                 // remove it from N
          factors.push_back(p[i]);
        }
      if (N != 1) factors.push_back(N);              // remaining N is a prime
      return factors;
    }

    map_ll_i primeFactors_power(ll N) {                         // pre-condition, N >= 1
      map_ll_i factors;
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        if(N % p[i] == 0) {
          int power = 0;
          while (N % p[i] == 0) {                        // found a prime for N
            N /= p[i];                                 // remove it from N
            power++;
          }
          factors[p[i]] = power;
        }
      }
      if (N != 1) factors[N] = 1;              // remaining N is a prime
      return factors;
    }


    // third part

    int numPF(ll N) {
      int ans = 0;
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N % p[i] == 0) 
        { N /= p[i]; ++ans; }
      return ans + (N != 1);
    }

    int numDiffPF(ll N) {
      int ans = 0;
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        if (N % p[i] == 0) ++ans;                      // count this prime factor
        while (N%p[i] == 0) N /= p[i];               // only once
      }
      if (N != 1) ++ans;
      return ans;
    }

    ll sumPF(ll N) {
      ll ans = 0;
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i)
        while (N % p[i] == 0) 
        { N /= p[i]; ans += p[i]; }
      if (N != 1) ans += N;
      return ans;
    }

    /*
    * =====================================================================================
    * Function: numDiv(N) - Counts the number of divisors of an integer N.
    *
    * --- Mathematical Principle ---
    *
    * The function is based on the Fundamental Theorem of Arithmetic. Every integer N > 1
    * has a unique prime factorization: N = p1^a1 * p2^a2 * ... * pk^ak.
    *
    * The number of divisors is found by the formula:
    *   num_divisors = (a1 + 1) * (a2 + 1) * ... * (ak + 1)
    *
    * This works because any divisor of N must be formed by choosing a power of p1
    * from 0 to a1 (a1+1 choices), a power of p2 from 0 to a2 (a2+1 choices), etc.,
    * and multiplying them together.
    *
    * --- Algorithm Breakdown ---
    *
    * The code first finds the prime factorization of N using an optimized trial division
    * method and simultaneously calculates the product of (power + 1) for each prime factor.
    *
    * It assumes a pre-computed list of primes is available (e.g., in `std::vector<int> p`).
    *
    * int numDiv(ll N) {
    *     int ans = 1;                                // Initialize the product of (power+1) terms.
    *
    *     // Loop through primes up to sqrt(N). This is an efficient way to find
    *     // all but at most one prime factor of N.
    *     for (int i = 0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i) {
    *
    *         int power = 0;                           // Counter for the exponent of the current prime p[i].
    *
    *         // Repeatedly divide N by the current prime p[i] to find its exponent.
    *         while (N % p[i] == 0) {
    *             N /= p[i];
    *             ++power;
    *         }
    *
    *         // Apply the formula: multiply the result by (power + 1).
    *         ans *= power + 1;
    *     }
    *
    *     // --- The Crucial Final Step ---
    *     // After the loop, two cases are possible:
    *     // 1. N has been reduced to 1. This means all prime factors of the original N
    *     //    were less than or equal to its square root. The calculation is complete.
    *     // 2. N is not 1. This means the remaining value of N is a prime factor itself.
    *     //    This happens when the original N had exactly one prime factor larger
    *     //    than its square root (e.g., for N=10, the loop handles prime 2, leaving N=5).
    *     //    The exponent of this large prime factor must be 1.
    *     //
    *     //    Therefore, we must account for this last prime factor by multiplying
    *     //    our answer by (1 + 1) = 2.
    *
    *     return (N != 1) ? 2 * ans : ans;
    * }
    *
    * =====================================================================================
    */
    int numDiv(ll N) {
      int ans = 1;                                   // start from ans = 1
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        int power = 0;                               // count the power
        while (N % p[i] == 0) 
        { N /= p[i]; ++power; }
        ans *= power + 1;                              // follow the formula
      }
      return (N != 1) ? 2 * ans : ans;                 // last factor = N^1
    }

    ll sumDiv(ll N) {
      ll ans = 1;                                    // start from ans = 1
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        ll multiplier = p[i], total = 1;
        while (N % p[i] == 0) {
          N /= p[i];
          total += multiplier;
          multiplier *= p[i];
        }                                            // total for
        ans *= total;                                // this prime factor
      }
      if (N != 1) ans *= (N + 1);                      // N^2-1/N-1 = N+1
      return ans;
    }

    ll EulerPhi(ll N) {
      ll ans = N;                                    // start from ans = N
      for (int i = 0; i < (int)p.size() && p[i]*p[i] <= N; ++i) {
        if (N % p[i] == 0) ans -= ans/p[i];            // count unique
        while (N % p[i] == 0) N /= p[i];               // prime factor
      }
      if (N != 1) ans -= ans/N;                      // last factor
      return ans;
    }

    // Returns largest power of p that divides n! 
    int legendre(ll n, ll p)  { 
      // Base Case
      if(n == 0) return 0;
      // Recursive Case
      return n / p + legendre(n / p, p);
    } 
}