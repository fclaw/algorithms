/*
───────────────────────────────────────────────────────────────
🧳 UVa 11417 GCD, https://onlinejudge.org/external/114/11417.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>

namespace arithmetics = algorithms::onlinejudge::maths::utility::arithmetics;


auto __gcd = arithmetics::__gcd<int>;

namespace algorithms::onlinejudge::maths::gcd
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

        int n;
        while(scanf("%d", &n) == 1 && n) {
          int gcd = 0;
          for(int i = 1; i < n; ++i)
            for(int j = i + 1; j <= n; ++j)
              gcd += __gcd(i, j);
          printf("%d\n", gcd);    
        }
    }
}