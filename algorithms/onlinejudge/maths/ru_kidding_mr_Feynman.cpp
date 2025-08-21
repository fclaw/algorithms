/*
───────────────────────────────────────────────────────────────
🧳 UVa 10509 R U Kidding Mr. Feynman?, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::ru_kidding_mr_Feynman
{
    /** https://onlinejudge.org/external/105/10509.pdf */
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
        
        double n;
        while(scanf("%lf", &n) == 1 && n != 0) {
          double cb = std::cbrt(n);
          double cb_i;
          bool is_integer = std::modf(cb, &cb_i) == 0;
          if(is_integer) { // full cubic root
            printf("%.4lf\n", cb_i);
          } else if(cb_i > 0) { // positive 
            double dx = (n - cb_i * cb_i * cb_i) / (3 * cb_i * cb_i);
            printf("%.4lf\n", cb_i + dx);
          } else { // negative
            cb_i -= 1; // shift dx above 0
            double dx = (n - (double)cb_i * cb_i * cb_i) / (3 * cb_i * cb_i);
            printf("%.4lf\n", cb_i + dx);
          }
        }
    }
}