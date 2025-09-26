/*
───────────────────────────────────────────────────────────────
🧳 UVa 374 Big Mod, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;


namespace algorithms::onlinejudge::maths::big_mod
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

       ll b, p, m;
       while(scanf("%lld %lld %lld", &b, &p, &m) == 3) {
         ll res = arith::mod_power<>(b, p, m);
         printf("%lld\n", res);
       }
    }
}