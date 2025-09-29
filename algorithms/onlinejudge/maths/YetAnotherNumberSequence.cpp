/*
───────────────────────────────────────────────────────────────
🧳 UVa 10689 Yet another Number Sequence, (easy if you know Pisano (a.k.a Fibonacci) period, https://onlinejudge.org/external/106/10689.pdf,  rt: s
───────────────────────────────────────────────────────────────
 * --- Strategy for Finding the Last 'm' Digits of a Generalized Fibonacci Sequence ---
 *
 * This problem combines several key number theory concepts to efficiently solve for
 * results that are too large to compute directly.
 *
 * 1.  THE SEQUENCE:
 *     The problem uses a Generalized Fibonacci Sequence, G(n), defined by the
 *     recurrence G(n) = G(n-1) + G(n-2) with arbitrary starting values G(0)=a, G(1)=b.
 *
 * 2.  THE CLOSED-FORM CONVERSION:
 *     Any such sequence can be expressed as a linear combination of the standard
 *     Fibonacci sequence F(n) (where F(0)=0, F(1)=1). The conversion formula is:
 *     G(n) = a * F(n-1) + b * F(n)
 *     (Requires defining F(-1)=1 for the n=0 case, or using an alternative formula).
 *
 * 3.  THE CORE INSIGHT: "LAST 'm' DIGITS" => MODULAR ARITHMETIC
 *     The task of finding the "last m digits" of a number is mathematically
 *     equivalent to calculating that number modulo 10^m.
 *     - Let M = 10^m. Our goal is to compute G(n) mod M.
 *
 * 4.  APPLYING MODULAR ARITHMETIC TO THE FORMULA:
 *     We can apply the modulus to our entire formula:
 *     G(n) mod M = ( (a * F(n-1)) + (b * F(n)) ) mod M
 *     G(n) mod M = ( (a%M * F(n-1)%M) + (b%M * F(n)%M) ) mod M
 *
 * 5.  HANDLING LARGE 'n' WITH THE PISANO PERIOD:
 *     To calculate F(n)%M for a very large 'n', we use the Pisano Period.
 *     a) Calculate the Pisano Period, p = π(M). This is the length of the cycle of
 *        the Fibonacci sequence modulo M. This must be done via simulation.
 *     b) Find the effective index: n' = n mod p.
 *     c) We now have F(n) mod M = F(n') mod M.
 *
 * 6.  THE FINAL ALGORITHM:
 *     a) Given 'm', set the modulus M = 10^m.
 *     b) Calculate the Pisano Period p = π(M).
 *     c) Given 'n', 'a', and 'b', calculate the effective indices:
 *        n_prime = n % p
 *        n_minus_1_prime = (n - 1 + p) % p // Safely handle n=0 case
 *     d) Compute F(n_prime) % M and F(n_minus_1_prime) % M using a simple DP loop.
 *     e) Plug these values into the modular formula from Step 4.
 *     f) The result is the answer. Pad with leading zeros if necessary to print 'm' digits.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

using ll = long long;
using v_ll = std::vector<ll>;

ll getPisanoPeriod(ll m) {
  ll a = 0, b = 1, c = a + b;
  for(ll i = 0; i < m * m; i++) {
    c = (a + b) % m;
    a = b;
    b = c;
    if (a == 0 && b == 1) return i + 1;
  }
  return 0; // Should never reach here for m >= 2
}

ll getFibonacciSimple(ll n, ll m) {
    if (n <= 1) {
        return n;
    }

    ll a = 0, b = 1;
    for (ll i = 0; i < n - 1; i++) {
        ll c = (a + b) % m;
        a = b;
        b = c;
    }
    return b;
}

ll fibonacciModulo(ll n, ll m, ll period) {
    // Edge cases
    if (n <= 1) {
        return n % m;
    }
    if (m <= 1) {
        return 0;
    }

    // Step 2: Reduce n using the period to get a smaller equivalent index.
    // The sequence F(n) mod m repeats every 'period' terms.
    ll reduced_n = n % period;

    // Step 3: Calculate the Fibonacci number for the smaller, reduced index.
    return getFibonacciSimple(reduced_n, m);
}


namespace algorithms::onlinejudge::maths::yet_another_number_sequence
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        v_ll piscano_periods(5);
        for(ll i = 1; i <= 4; i++) {
          piscano_periods[i] = getPisanoPeriod(arith::power(10LL, i));
        }

        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          ll a, b, n, m;
          scanf("%lld %lld %lld %lld", &a, &b, &n, &m);
          ll mod = arith::power(10LL, m);
          if(n == 0) printf("%lld\n", a % mod);
          else if(n == 1) printf("%lld\n", b % mod);
          else printf("%llu\n", ((a % mod) * fibonacciModulo(n - 1, mod, piscano_periods[m]) + ((b % mod) * fibonacciModulo(n, mod, piscano_periods[m]))) % mod);
        }
    }
}