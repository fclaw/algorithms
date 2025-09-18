/*
───────────────────────────────────────────────────────────────
🧳 UVa 324 Factorial Frequencies, https://onlinejudge.org/external/3/324.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>




namespace bi = algorithms::onlinejudge::maths::utility::big_integer;


namespace algorithms::onlinejudge::maths::factorial_freq
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

        int num;
        while(scanf("%d", &num) == 1 && num) {
          bi::BigInt fac =  bi::BigInt(1);
          for(int n = 2; n <= num; ++n) fac *= n;
          std::array<int, 10> freq = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
          for(auto& d : fac.get_digits()) freq[d]++;

          printf("%d!--\n(0) %d (1) %d (2) %d (3) %d (4) %d\n(5) %d (6) %d (7) %d (8) %d (9) %d\n", 
                 num, freq[0], freq[1], freq[2], freq[3], freq[4], 
                 freq[5], freq[6], freq[7], freq[8], freq[9]);
        }
    }
}