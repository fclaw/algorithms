/*
───────────────────────────────────────────────────────────────
🧳 UVa 10127 Ones, no factor of 2 and 5 implies that there is no trailing zero, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;


namespace algorithms::onlinejudge::maths::ones
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

       ll num;
       while(scanf("%lld", &num) == 1) {
         ll rem = 0;
         ll exp = 0;
         int digits = 0;
         do {
           rem = (rem + arith::mod_power((ll)10, exp++, num)) % num;
           digits++;
          } while(rem != 0);
         printf("%d\n", digits);
       }
    }
}