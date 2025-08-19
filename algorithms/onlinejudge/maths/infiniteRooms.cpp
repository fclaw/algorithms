/*
───────────────────────────────────────────────────────────────
🧳 UVa 10170 The Hotel with Infinite Rooms, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using ld = long double;

// When group S checks out, a total of S days have passed.
// When group S+1 checks out, a total of S + (S+1) days have passed.
// When group S+2 checks out, a total of S + (S+1) + (S+2) days have passed.
// So, we're looking for the smallest K (where K >= S) that satisfies:
// S + (S+1) + ... + K >= D
// The missing part is the sequence: (1 + 2 + 3 + ... + S-1) add and subtract it
// New Sum = (1 + 2 + ... + S-1) + [ S + (S+1) + ... + K ] - (1 + 2 + ... + S-1)
ll solve(ll S, ll D) {
  // Step 1: Calculate the "offset" of days that passed before group S arrived.
  // This is the sum 1 + 2 + ... + (S-1).
  ll days_before_S = (S - 1) * S / 2;

  // Step 2: Calculate the total number of days that must be covered, as if
  // the process started from a group of size 1.
  ll total_days_needed = D + days_before_S;

  // Step 3: Solve K*(K+1)/2 >= total_days_needed using the quadratic formula.
  // K^2 + K - 2*total_days_needed >= 0
  // We use long double for precision with large numbers.
  ld kd = (-1.0 + std::sqrtl(1.0 + 8.0 * total_days_needed)) / 2.0;

  // The answer is the smallest integer K greater than or equal to k_val,
  // which is the ceiling of k_val.
  return static_cast<ll>(std::ceil(kd));
}




namespace algorithms::onlinejudge::maths::infinite_rooms
{
    /** https://onlinejudge.org/external/101/10170.pdf */
    ll size, day;
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
        
        while(scanf("%lld %lld", &size, &day) == 2) {
          printf("%lld\n", solve(size, day));
        }
    }
}