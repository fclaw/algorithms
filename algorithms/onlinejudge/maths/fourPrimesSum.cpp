/*
───────────────────────────────────────────────────────────────
🧳 UVa 10168 Summation of Four Primes, backtracking with pruning, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: From Brute-Force Search to a Goldbach-Based Insight ---
 *
 * The problem asks to express a given integer N (up to 10^7) as the sum of four
 * primes. A naive brute-force or an unconstrained backtracking search across all
 * primes would be far too slow.
 *
 * The key insight is that we only need to explore a tiny fraction of the available
 * primes to construct a valid solution. This can be justified by leveraging the
 * Goldbach Conjecture and analyzing the parity (even/odd) of N.
 *
 * The Goldbach Conjecture (unproven but verified for numbers far larger than 10^7)
 * states that every even integer greater than 2 can be expressed as the sum of two primes.
 * We can use this to reduce our 4-prime problem into a simpler 2-prime problem.
 *
 *
 * ### Step 1: Reduce the Problem Based on N's Parity ###
 *
 * Our goal is to find p1 + p2 + p3 + p4 = N.
 *
 * #### Case A: N is Even ####
 * To simplify the search, we can fix the first two primes to be the smallest possible
 * prime, which is 2.
 * Let p1 = 2 and p2 = 2.
 * The equation becomes: 2 + 2 + p3 + p4 = N
 * This simplifies to: p3 + p4 = N - 4
 *
 * Since N is even, N-4 is also an even number. According to the Goldbach Conjecture,
 * we are guaranteed to find a pair of primes (p3, p4) that sum to N-4, as long as
 * N-4 > 2 (i.e., N > 6). For the problem constraints (N>=8), this always holds.
 *
 * #### Case B: N is Odd ####
 * For the sum of four primes to be odd, at least one of them must be the only even
 * prime, 2. Let's fix p1 = 2.
 * To make the remaining sum `p2 + p3 + p4` odd, one of the remaining primes must also
 * be 2, or all three must be odd. The latter is more general. Let's fix the next
 * smallest odd prime, p2 = 3.
 *
 * Let p1 = 2 and p2 = 3.
 * The equation becomes: 2 + 3 + p3 + p4 = N
 * This simplifies to: p3 + p4 = N - 5
 *
 * Since N is odd, N-5 is an even number. Again, by the Goldbach Conjecture, we are
 * guaranteed to find a pair of primes (p3, p4) that sum to N-5 (for N > 7).
 *
 *
 * ### Step 2: The Justification for a Tiny Search Space ###
 *
 * The analysis above proves that a valid solution can always be constructed by starting
 * with `2 + 2` (for even N) or `2 + 3` (for odd N). We never need to consider starting
 * with larger primes like 5, 7, 11, etc. for our first two terms.
 *
 * This is why a backtracking search that tries the smallest primes first is incredibly
 * efficient. It's not a guess; it's a search that is guaranteed by number theory to
 * find a solution in its very first branches. It doesn't need to explore primes up to
 * 1000, or even 100. It only needs to find one of the many possible Goldbach pairs
 * for `N-4` or `N-5`.
 *
 *
 * ### Final Algorithm ###
 *
 * 1. Pre-compute primes up to N using a sieve.
 * 2. If N is even: print "2 2" and find two primes (a, b) that sum to N-4.
 * 3. If N is odd: print "2 3" and find two primes (a, b) that sum to N-5.
 *
 * The search for the final pair (a, b) is very fast: iterate through your prime list
 * with a prime `p` and check if `(Target - p)` is also prime.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 1000;
constexpr int NUMS = 3;

vll ans;

void backtrack(int prev, ll num, int left, vll v_primes, bool& is_found, vll& nums) {
  if(left == 0) {
    if(primes::isPrime(num)) {
      ans = nums;
      ans.push_back(num);
      is_found = true;
    }
    return;
  }

  auto it = std::upper_bound(v_primes.begin(), v_primes.end(), num);
  int bound = it - v_primes.begin();
  for(int i = prev; i < bound; ++i) {
    if(num > v_primes[i]) {
      nums.push_back(v_primes[i]);
      backtrack(i, num - v_primes[i], left - 1, v_primes, is_found, nums);
      nums.pop_back();
    }
    if(is_found) return;
  }
}


namespace algorithms::onlinejudge::maths::four_primes_summation
{
    /** https://onlinejudge.org/external/101/10168.pdf */
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        ll num;
        bool is_found;
        vll nums;
        std::string s;
        primes::sieve(MAX);
        vll v_primes = primes::p;
        while(scanf("%lld", &num) == 1) {
          is_found = false;
          nums.clear();
          s.clear();
          backtrack(0, num, NUMS, v_primes, is_found, nums);
          for(ll n : ans) s += std::to_string(n) + " ";
          s.pop_back();
          printf("%s\n", is_found ? s.c_str() : "Impossible.");
        }
    }
}