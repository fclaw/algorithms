/*
───────────────────────────────────────────────────────────────
🧳 UVa 11254 Consecutive Integers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::consecutive_integers
{
    /** https://onlinejudge.org/external/112/11254.pdf */
    int num;
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
        
        while(scanf("%d", &num) == 1 && num != -1) {
          int n, first;
          for(int curr_n = std::sqrt(2 * num); curr_n >= 1; --curr_n) {
            if(!((2 * num) % curr_n) && !(((2 * num) / curr_n - curr_n + 1) % 2)) {
              first = ((2 * num) / curr_n - curr_n + 1) / 2;
              n = curr_n;
              goto solution;
            }
          }
          solution:
          int last = 2 * num / n - first;
          printf("%d = %d + ... + %d\n", num, first, last);
        }
    }
}