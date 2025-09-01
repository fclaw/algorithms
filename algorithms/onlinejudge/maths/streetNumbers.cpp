/*
───────────────────────────────────────────────────────────────
🧳 UVa 138 Street Numbers, rt: s
───────────────────────────────────────────────────────────────
 * --- Analysis ---
 *
 * The problem requires finding integer pairs (k, n) that satisfy the equation:
 *   Sum(1..k-1) = Sum(k+1..n)
 *
 * This simplifies to the Diophantine equation:
 *   2k^2 = n(n+1)
 *
 * which is a form of Pell's equation that can be written as (2n+1)^2 - 8k^2 = 1.
 *
 * The solutions can be generated via a recurrence relation. If (k_i, n_i) is a
 * solution, the next is (k_{i+1}, n_{i+1}):
 *   k_{i+1} = 3*k_i + 2*n_i + 1
 *   n_{i+1} = 4*k_i + 3*n_i + 1
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ll = long long;

// solve the equation: n^2 + n - 2k ^ 2 = 0
// std::vector<std::pair<ll, ll>> results;
// for(ll i = 6; i <= 100000000; ++i) {
//   results.push_back({i, 1 + 8 * i * i});
// }

// for(const auto& [k, discriminant] : results) {
//   double root;
//   bool is_integer = std::modf(std::sqrtl(discriminant), &root) == 0;          
//   if(is_integer) {
//     ll n = -1 + (ll)root;
//     if(!(n % 2) && n > k) {
//       printf("%10lld%10lld\n", k, n / 2);
//     }
//   }
// }

//          6         8
//         35        49
//        204       288
//       1189      1681
//       6930      9800
//      40391     57121
//     235416    332928
//    1372105   1940449
//    7997214  11309768
//   46611179  65918161
//   85225144 120526554


namespace algorithms::onlinejudge::maths::street_numbers
{
    /** https://onlinejudge.org/external/1/138.pdf  */
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
        
        std::vector<std::pair<ll, ll>> results = {
          {6, 8},
          {35, 49},
          {204, 288},
          {1189, 1681},
          {6930, 9800},
          {40391, 57121},
          {235416, 332928},
          {1372105, 1940449},
          {7997214, 11309768},
          {46611179, 65918161}
        };
        
        for(const auto& [k, n] : results) {
          printf("%10lld%10lld\n", k, n);
        }
        
    }
}