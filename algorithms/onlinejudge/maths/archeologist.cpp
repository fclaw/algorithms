/*
───────────────────────────────────────────────────────────────
🧳 UVa 701 The Archeologists’ Dilemma, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using ld = long double;

constexpr int MAX_LENGTH = 100000000;


namespace algorithms::onlinejudge::maths::archeologist
{
    /** https://onlinejudge.org/external/7/701.pdf */
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

        int n;
        while(scanf("%d", &n) == 1) {
          ld log2_N = std::log2l(static_cast<ld>(n));
          ld log2_N_1 = std::log2l(static_cast<ld>(n + 1));
          ld log2_10 = std::log2l(10.0L);

          // --- The Search Loop ---
          // more than half of the digits are missing
          ll exp = std::floorl(std::log10l(n)) + 2;
          while(std::ceill(log2_N + exp * log2_10) != 
                std::floorl(log2_N_1 + exp * log2_10)) {
            if(exp >= MAX_LENGTH) goto done;
            ++exp;
          }

          done:
          auto ans = exp < MAX_LENGTH ? std::to_string((int)std::floorl(log2_N_1 + exp * log2_10)) : "no power of 2";    
          printf("%s\n", ans.c_str());
        }
    }
}