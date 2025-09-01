/*
───────────────────────────────────────────────────────────────
🧳 UVa 443 Humble Numbers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ll = long long;
using vs = std::vector<ll>;


namespace algorithms::onlinejudge::maths::humble
{
    /** https://onlinejudge.org/external/4/443.pdf */
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
        while(scanf("%d", &n) == 1 && n != 0) {
          vs humbles = {1};
          auto ptr2 = 0, ptr3 = 0, ptr5 = 0, ptr7 = 0;
          int cnt = 0;
          while(++cnt < n) {
            ll humble2 = humbles[ptr2] * 2;
            ll humble3 = humbles[ptr3] * 3;
            ll humble5 = humbles[ptr5] * 5;
            ll humble7 = humbles[ptr7] * 7;
            ll min_humble = std::min({humble2, humble3, humble5, humble7});
            humbles.push_back(min_humble);
            if(min_humble == humble2) { ++ptr2; }
            if(min_humble == humble3) { ++ptr3; }
            if(min_humble == humble5) { ++ptr5; }
            if(min_humble == humble7) { ++ptr7; }
          }
          printf("The %d%s humble number is %lld.\n", n, (n % 10 == 1 && n % 100 != 11) ? "st" : (n % 10 == 2 && n % 100 != 12) ? "nd" : (n % 10 == 3 && n % 100 != 13) ? "rd" : "th", humbles.back());
        }
    }
}