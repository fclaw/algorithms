/*
───────────────────────────────────────────────────────────────
🧳 UVa 10174 Couple-Bachelor-Spinster Numbers, rt: s
───────────────────────────────────────────────────────────────
 * ======================================================================================
 * LOGIC EXPLANATION: The Math Behind Couple-Bachelor-Spinster Numbers
 * ======================================================================================
 *
 * THE CORE IDENTITY:
 * The problem asks if a number N can be expressed as a² - b². The key is to
 * factor the right side using the difference of squares identity:
 *   N = a² - b² = (a - b) * (a + b)
 *
 * Let's call the factors k1 = (a - b) and k2 = (a + b). So, N = k1 * k2.
 * Our goal is to find non-negative integers a and b that satisfy this.
 *
 * A CRUCIAL PROPERTY:
 * The two factors, k1 and k2, must have the same parity (both even or both odd).
 * Why? Their difference is k2 - k1 = (a + b) - (a - b) = 2b, which is always even.
 * The difference between two integers is even only if they are both even or both odd.
 *
 * This property allows us to solve the problem by considering two cases based on N's parity.
 *
 * CASE 1: N is an ODD number.
 * --------------------------------
 * If N is odd, its factors (k1 and k2) must also be odd.
 * We can choose the simplest possible factors: k1 = 1 and k2 = N.
 * This gives us a system of two equations:
 *   a - b = 1
 *   a + b = N
 *
 * Solving this system (e.g., by adding the two equations) gives:
 *   2a = N + 1  =>  a = (N + 1) / 2
 *   2b = N - 1  =>  b = (N - 1) / 2
 *
 * Since N is odd, (N+1) and (N-1) are both even, guaranteeing that 'a' and 'b'
 * will always be integers.
 * CONCLUSION: Every positive ODD number is a square-couple number.
 *
 * CASE 2: N is an EVEN number.
 * --------------------------------
 * If N is even, its factors (k1 and k2) must both be even (as they must have
 * the same parity).
 * Let's choose the simplest possible even factors: k1 = 2 and k2 = N / 2.
 * This gives us a system of equations:
 *   a - b = 2
 *   a + b = N / 2
 *
 * Solving this system gives:
 *   2a = N/2 + 2  =>  a = (N / 4) + 1
 *   2b = N/2 - 2  =>  b = (N / 4) - 1
 *
 * For 'a' and 'b' to be integers, N must be divisible by 4. If it's not, N/4 will
 * not be an integer and the solution fails.
 * CONCLUSION: An EVEN number is a square-couple number if and only if it is a
 * MULTIPLE OF 4.
 *
 * THE FINAL CLASSIFICATION (Bachelor Numbers):
 * =================================================
 * - If N is ODD, it's a square-couple.
 * - If N is a MULTIPLE OF 4, it's a square-couple.
 * - The only remaining case is numbers that are EVEN but NOT a multiple of 4.
 *   These are numbers of the form 4k + 2. These are the BACHELOR NUMBERS.
 *
 * (Note: N=0 is a special case. 0 = 0²-0², so it's a square-couple.)
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;


void solve_range(ll l, ll r) {
  ll bachelor_numbers = 0;
  for(ll s = l; s <= r; ++s) {
    if(!(s % 2) && (s % 4)) {
      bachelor_numbers++;
    }
  }
  printf("%lld\n", bachelor_numbers);
}

void solve_single_number(ll n) {

  if(n == 0) { printf("1 1\n"); return; }

  bool is_negative = n < 0;
  n = std::abs(n);
  // n is odd
  if((n % 2)) {
    ll a, b;
    if(!is_negative) {
      b = (n - 1) / 2;
      a = b + 1;
    } else {
      a = (n - 1) / 2;
      b = a + 1;  
     }
     printf("%lld %lld\n", a, b);
  } else if(!(n % 4)) {
    ll a, b;
    if(!is_negative) {
      b = n / 4 - 1;
      a = b + 2;
    } else {
      a = n / 4 - 1;
      b = a + 2;
    }
    printf("%lld %lld\n", a, b);
  } else printf("Bachelor Number.\n");
}


namespace algorithms::onlinejudge::maths::couple_bachelor_spinster
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

       std::string line;
       ll n1, n2;
       while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        ss >> n1;
        ss >> n2 ? solve_range(n1, n2) : solve_single_number(n1);
       }
    }
}