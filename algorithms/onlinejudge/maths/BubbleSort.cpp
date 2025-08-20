/*
───────────────────────────────────────────────────────────────
🧳 UVa 12004 Bubble Sort, rt: s
───────────────────────────────────────────────────────────────
 *
 * --- Mathematical Analysis ---
 *
 * The problem asks for the average number of swaps performed by the given bubble
 * sort implementation on a random, distinct permutation of N integers.
 *
 *
 * STEP 1: Connect Swaps to Inversions
 *
 * A fundamental property of bubble sort is that the total number of swaps it performs
 * is exactly equal to the number of "inversions" in the initial array. An inversion
 * is any pair of elements (a[i], a[j]) such that i < j but a[i] > a[j]. Each swap
 * corrects exactly one inversion, and the algorithm terminates only when no
 * inversions are left.
 *
 * Therefore, "Average number of swaps" is the same as "Average number of inversions".
 *
 *
 * STEP 2: Use Linearity of Expectation
 *
 * The average (or expected value) of a sum is the sum of the averages. The total
 * number of inversions is the sum of indicators for each pair of elements (where
 * the indicator is 1 if the pair is an inversion, 0 otherwise).
 *
 * Avg. Total Inversions = Sum over all pairs [ Avg. Inversions for that pair ]
 *
 * By symmetry, the average number of inversions for any pair is the same. Thus:
 * Avg. Total Inversions = (Total number of pairs) * (Probability of a random pair being an inversion)
 *
 *
 * STEP 3: Calculate the Total Number of Pairs
 *
 * We need to find how many unique pairs of elements can be formed from a set of N items.
 * This can be derived from first principles:
 *
 *   - The 1st element can form a pair with the (N-1) elements that follow it.
 *   - The 2nd element can form a pair with the (N-2) elements that follow it.
 *   - ...
 *   - The (N-1)th element can form a pair with the 1 element that follows it.
 *   - The Nth element can form 0 new pairs.
 *
 * Total Pairs = (N-1) + (N-2) + ... + 1 + 0
 *
 * This is the sum of the first (N-1) integers, for which the formula is k*(k+1)/2,
 * where k = N-1.
 *
 * Total Pairs = (N-1) * ((N-1) + 1) / 2
 * Total Pairs = (N-1) * N / 2
 *
 *
 * STEP 4: Calculate the Probability of an Inversion for a Single Pair
 *
 * Consider any two distinct numbers, say X and Y, with X < Y. In a random permutation,
 * they are equally likely to appear in the order (...X...Y...) or (...Y...X...).
 *
 *   - Order (...X...Y...): Not an inversion.
 *   - Order (...Y...X...): Is an inversion.
 *
 * Since both outcomes have an equal chance, the probability of the pair forming an
 * inversion is exactly 1/2.
 *
 *
 * STEP 5: Combine the Pieces for the Final Formula
 *
 * Avg. Swaps = (Total Pairs) * (Probability of Inversion)
 * Avg. Swaps = ( N * (N-1) / 2 ) * ( 1/2 )
 * Avg. Swaps = N * (N-1) / 4
 *
 * This O(1) formula allows us to calculate the result directly without any simulation.
 * The output requires simplifying this fraction.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;



ll __gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return __gcd(b, a % b);
}


namespace algorithms::onlinejudge::maths::bubble_sort
{
    /** https://onlinejudge.org/external/120/12004.pdf */
    int t_cases, t_case = 1;
    ll n;
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

        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%lld", &n);
          std::string ans ;
          ll nominator = n * (n - 1);
          ll denominator = 4;
          if((nominator % denominator)) {
            ll gcd = __gcd(nominator, denominator);
            nominator /= gcd;
            denominator /= gcd;
            ans += std::to_string(nominator) + "/" + std::to_string(denominator);
          } else {
            nominator /= denominator;
            ans += std::to_string(nominator);
          }
          printf("Case %d: %s\n", t_case++, ans.c_str());
        }
    }
}