/*
───────────────────────────────────────────────────────────────
🧳 UVa 906 Rational Neighbor, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr double eps = 1e-12;

using ll = long long;


namespace algorithms::onlinejudge::maths::rational_neighbour
{
    /** https://onlinejudge.org/external/9/906.pdf */
    int a, b;
    double diff;
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
        
        while(while_read(a, b)) {
          while_read(diff);

          // we start from 1 to ensure denominator to be the smallest possible 
          // (the denominator d is as small as possible)
          ll d = 1;
          ll c;
          double dist;
          do {
            // --- CORRECTED CALCULATION for the numerator 'c' ---
            // We need to round to the nearest integer, not floor.
            // Or using integer arithmetic for rounding:
            c = 1 + (double)(a * d) / b;
            dist = (double)(c * b - a * d);
          //  a/b < c/d and the distance between the rationals a/b and c/d is smaller or equal than n  
          } while((a * d > c * b || dist > diff * d * b + eps) && d++);
          printf("%d %d\n", (int)c, (int)d);
        }
    }
}