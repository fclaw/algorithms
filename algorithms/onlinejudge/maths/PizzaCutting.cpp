/*
───────────────────────────────────────────────────────────────
🧳 UVa 10079 Pizza Cutting, https://onlinejudge.org/external/100/10079.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>





using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::pizza_cutting
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


       int max_cuts;
       while(scanf("%d", &max_cuts) == 1 && max_cuts >= 0) {
         if(max_cuts == 0) {
           printf("1\n");
           continue;
         }

         // T(n) = T(n - 1) + n 
         ull curr_regions = 0;
         ull prev_regions = 1; // base case: 0 cuts there is only 1 piece, T(0) = 1
         for(ull cut = 1; cut <= (ull)max_cuts; ++cut) {
           curr_regions = prev_regions + cut;
           prev_regions = curr_regions;
         }
         printf("%llu\n", curr_regions);
       }
    }
}