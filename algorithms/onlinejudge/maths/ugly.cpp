/*
───────────────────────────────────────────────────────────────
🧳 UVa 136 Ugly Numbers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ll = long long;
using vs = std::vector<ll>;


namespace algorithms::onlinejudge::maths::ugly
{
    /** https://onlinejudge.org/external/1/136.pdf */
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
        
    
        vs ugly = {1};
        int ptr2 = 0, ptr3 = 0, ptr5 = 0;
        int cnt = 0;
        while(++cnt < 1500) {
          ll ugly2 = ugly[ptr2] * 2;
          ll ugly3 = ugly[ptr3] * 3;
          ll ugly5 = ugly[ptr5] * 5;
          ll min_ugly = std::min({ugly2, ugly3, ugly5});
          ugly.push_back(min_ugly);
          if(min_ugly == ugly2) { ++ptr2; }
          if(min_ugly == ugly3) { ++ptr3; }
          if(min_ugly == ugly5) { ++ptr5; }
        }
        printf("The 1500'th ugly number is %lld.\n", ugly.back());
    }
}