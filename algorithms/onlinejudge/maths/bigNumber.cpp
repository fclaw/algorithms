/*
───────────────────────────────────────────────────────────────
🧳 UVa 1185 Big number, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::maths::big_number
{
    /** https://onlinejudge.org/external/11/1185.pdf */
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
         
        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n;
          scanf("%d", &n);
          double digits = 1;
          for(int i = 1; i <= n; i++) {
            digits += std::log10(i);
          }
          printf("%d\n", (int)digits);
        }
    }
}