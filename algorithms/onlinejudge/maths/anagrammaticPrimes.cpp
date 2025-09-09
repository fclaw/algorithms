/*
───────────────────────────────────────────────────────────────
🧳 UVa 897 Anagrammatic Primes, sieve; just need to check digit rotations,  rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Analysis: From Permutations to Divisibility Rules ---
 *
 * The problem asks us to find "anagrammatic primes": prime numbers where every
 * permutation of their digits is also prime. A naive approach of iterating through
 * numbers, checking primality, and then generating and checking all digit permutations
 * would be far too slow, especially for numbers up to 10^7.
 *
 * The key to an efficient solution is to use fundamental divisibility rules to
 * aggressively prune the search space. We are not looking for a clever way to
 * generate permutations, but rather a clever way to avoid it entirely.
 *
 *
 * ### The Core Insight: Exploiting Divisibility Checks ###
 *
 * An anagrammatic prime `P` (and all its permutations) must survive basic primality tests.
 * This leads to three powerful filtering conditions for any multi-digit candidate `P`.
 *
 * 1.  The "Even Digit" Rule (Divisibility by 2):
 *    If the digits of `P` contain an even number (0, 2, 4, 6, 8), we can form a
 *    permutation where that even digit is in the units place. This new number would
 *    be even and greater than 2, and therefore not prime. This violates the condition.
 *    >> Conclusion: A multi-digit anagrammatic prime cannot contain any even digits.
 *
 * 2.  The "'5' Digit" Rule (Divisibility by 5):
 *    Similarly, if the digits of `P` contain a '5', we can permute it to the end,
 *    creating a multiple of 5. This number would not be prime (unless it is 5 itself).
 *    >> Conclusion: A multi-digit anagrammatic prime cannot contain the digit 5.
 *
 *    Combining these two rules, we find that any anagrammatic prime greater than 10
 *    must be composed exclusively of the digits {1, 3, 7, 9}.
 *
 * 3.  The "Sum of Digits" Rule (Divisibility by 3):
 *    A number is divisible by 3 if and only if the sum of its digits is divisible by 3.
 *    All permutations of a number's digits have the same sum of digits. Therefore,
 *    if the sum of digits is a multiple of 3, all permutations will be divisible by 3.
 *    Unless the number itself is 3, none of these permutations can be prime.
 *    >> Conclusion: The sum of digits of an anagrammatic prime ( > 3) cannot be
 *       divisible by 3.
 *
 *
 * ### The Efficient Algorithm: Pre-calculation ###
 *
 * These pruning rules are so effective that they eliminate the vast majority of
 * numbers. The number of anagrammatic primes is very small. The best strategy is
 * to pre-calculate all of them within the problem's range (up to 10,000,000)
 * and then answer each query in O(log K) time, where K is the small count of
 * these special primes.
 *
 * 1.  **Sieve:** Generate all primes up to 10,000,000 for fast primality checks.
 * 2.  **Filter and Test:** Iterate through the sieved primes. For each prime `p`:
 *     a. Apply the fast divisibility/digit checks. If `p` contains a {0,2,4,5,6,8}
 *        or its digit sum is divisible by 3, discard it immediately.
 *     b. For the very few primes that pass, perform the full check: generate all
 *        unique permutations of its digits and test each for primality.
 *     c. If all permutations are prime, add `p` to a sorted list of anagrammatic primes.
 * 3.  **Query:** For each input `n`, use binary search (std::upper_bound) on the
 *     pre-calculated list to find the first anagrammatic prime greater than `n`.
 *
 * This approach turns a problem that seems to be about factorial complexity into a
 * simple pre-computation and lookup task.
 *
 * =====================================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;
namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;

using pll = std::pair<ll, ll>;
constexpr ll MAX = 10'000'000;



bool check_divisibility_2_3_5(ll prime) {
    // Single-digit primes are anagrammatic by definition.
    // The rules below apply to multi-digit numbers.
    if (prime < 10) {
        return true;
    }

    // We can analyze the number by converting it to a string.
    std::string s = std::to_string(prime);
    int digit_sum = 0;

    for (char c : s) {
        int digit = c - '0';

        // Rule 1 & 2: Check for even digits or the digit 5.
        // A multi-digit number with any of these digits can have a permutation
        // ending in that digit, making it divisible by 2 or 5, and thus not prime.
        if (digit % 2 == 0 || digit == 5) {
            return false; // Disqualified.
        }

        // Rule 3: Accumulate the sum of digits to check for divisibility by 3.
        digit_sum += digit;
    }

    // A number is divisible by 3 if its digit sum is. If so, all its
    // permutations are also divisible by 3 and thus not prime.
    if (digit_sum % 3 == 0) {
        return false; // Disqualified.
    }

    // If the number passed all checks, it's a potential candidate.
    return true;
}


namespace algorithms::onlinejudge::maths::anagrammatic_primes
{
    /** ... */
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
        primes::sieve(MAX); // generation of primes up to 1_000_000
        vll v_primes = primes::p;
        while(scanf("%lld", &num) == 1 && num) {
          int digits = (int)std::log10(num) + 1;
          ll next_10 = arithmetics::power(10, digits);
          auto lower_b = std::upper_bound(v_primes.begin(), v_primes.end(), num);
          auto upper_b = std::lower_bound(v_primes.begin(), v_primes.end(), next_10);

          int ans = 0;
          for(auto it = lower_b; it != upper_b; ++it) {
            if(check_divisibility_2_3_5(*it)) {
              std::string prime_s = std::to_string(*it);
               // *** THE CRITICAL FIX ***
              // Sort the digits in ascending order before starting.
              std::sort(prime_s.begin(), prime_s.end());
              bool is_anagram_prime = true;
              do {
                ll next_num = std::stoll(prime_s);
                if(!primes::isPrime(next_num)) {
                  is_anagram_prime = false;
                  break;
                }
              } while(std::next_permutation(prime_s.begin(), prime_s.end()));
              if(is_anagram_prime) 
              { ans = *it; goto finished; }
            }
          }

          finished: printf("%d\n", ans);
        }
    }
}