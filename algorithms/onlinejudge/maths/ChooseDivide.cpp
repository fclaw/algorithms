/*
───────────────────────────────────────────────────────────────
🧳 UVa 10375 Choose and divide, https://onlinejudge.org/external/103/10375.pdf, keep an intermediate result small to avoid overflow,  rt: s
───────────────────────────────────────────────────────────────
  1*2*3*4*5*6 / 1*2
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ull = unsigned long long;


constexpr int MAX = 10000;
constexpr double BASE = 10;


namespace algorithms::onlinejudge::maths::choose_and_divide
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

         // --- PRE-COMPUTATION is much faster ---
        // Pre-compute the log factorials (sum of logs) up to n.
        // actual constraint on the upper bound > 1m renders this approach useless
        std::vector<long double> log_factorials(MAX + 1, 0.0);
        for (int i = 1; i <= MAX; ++i) {
          log_factorials[i] = log_factorials[i - 1] + std::log10l((long double)i);
        } 

        int p, q, r, s;
        while(scanf("%d %d %d %d", &p, &q, &r, &s) == 4) {
          long double fac_p = log_factorials[p];
          long double fac_q = log_factorials[q];
          long double fac_p_q = log_factorials[p - q];
          long double fac_r = log_factorials[r];
          long double fac_s = log_factorials[s];
          long double fac_r_s = log_factorials[r - s];
          printf("%.5Lf\n", std::powl(BASE, fac_p + fac_r_s + fac_s - fac_r - fac_p_q - fac_q));
        }
    }
}