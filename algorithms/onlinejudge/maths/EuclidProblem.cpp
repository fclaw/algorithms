/*
───────────────────────────────────────────────────────────────
🧳 UVa 10104 Euclid Problem, pure Ext Euclid problem, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;
using ld = long double;


namespace algorithms::onlinejudge::maths::euclid_problem
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

       ll a, b;
       while(scanf("%lld %lld", &a, &b) == 2) {
         ll x, y;
         ll gcd = arith::extended_euclid(a, b, x, y);
         // If a or b is zero, EEA might produce strange results. Handle this case.
         // However, for this problem, inputs are positive.
         if(b == 0) { // Base case of Euclid. a*1 + 0*0 = a
          printf("1 0 %lld\n", a);
          continue;
         }

         // --- Start of the resolution logic ---
         // There are infinite solutions. We have one: (x, y).
         // All others are of the form:
         // x' = x + k * (b / gcd)
         // y' = y - k * (a / gcd)
         // We want to find the k that minimizes |x'| + |y'|.
         // This happens when x' is close to 0.
    
         ll b_g = b / gcd;
         ll a_g = a / gcd;

         // Calculate the two best integer candidates for k.
         // Use long double for precision with division.
         ld k_float = - (ld)x / b_g;
         ll k1 = std::floor(k_float);
         ll k2 = std::ceil(k_float);

         // Generate the two potential best solutions
         ll x1 = x + k1 * b_g;
         ll y1 = y - k1 * a_g;

         ll x2 = x + k2 * b_g;
         ll y2 = y - k2 * a_g;

         // Compare them based on the problem's criteria
         ll cost1 = std::abs(x1) + std::abs(y1);
         ll cost2 = std::abs(x2) + std::abs(y2);

         ll final_x, final_y;

         if(cost1 < cost2) {
           final_x = x1;
           final_y = y1;
         } else if(cost2 < cost1) {
           final_x = x2;
           final_y = y2;
        } else { // costs are equal, apply second rule: x <= y
          if(x1 <= y1) {
            final_x = x1;
            final_y = y1;
          } else {
            final_x = x2;
            final_y = y2;
          }
        }
        printf("%lld %lld %lld\n", final_x, final_y, gcd);
       }
    }
}