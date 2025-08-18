/*
───────────────────────────────────────────────────────────────
🧳 UVa 11130 Billiard bounces, (use billiard table reflection technique:
  mirror the billiard table to the right (and/or top) so that we will only deal
  with one straight line instead of bouncing lines  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

namespace algorithms::onlinejudge::maths::billiard
{
    /** https://onlinejudge.org/external/111/11130.pdf */
    int a, b, v, alpha, s;
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
       
        while(scanf("%d %d %d %d %d", &a, &b, &v, &alpha, &s) == 5) {
          if(a == 0 && b == 0 && v == 0 && alpha == 0 && s == 0) break;
          double path = v * s;
          double x_delta = path * std::cos(alpha * M_PI / 180);
          double y_delta =  path * std::sin(alpha * M_PI / 180);
          int v_bounces = x_delta / a;
          int h_bounces = y_delta / b;
          if((v_bounces % 2)) v_bounces++;
          if((h_bounces % 2)) h_bounces++;
          printf("%d %d\n", v_bounces / 2, h_bounces / 2);
        }
    }
}