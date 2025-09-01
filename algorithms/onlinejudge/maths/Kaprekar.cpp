/*
───────────────────────────────────────────────────────────────
🧳 UVa 974 Kaprekar Numbers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using vb = std::vector<bool>;
const int MAX_KAPREKAR = 40000;


namespace algorithms::onlinejudge::maths::Kaprekar
{
    /** https://onlinejudge.org/external/9/974.pdf */
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

       vb kaprekar(MAX_KAPREKAR + 1, false);
       for(int i = 1; i <= MAX_KAPREKAR; ++i) {
         ll sq = (ll)i * (ll)i;
         auto sq_s = std::to_string(sq);
         for(int d = 1; d <= (int)sq_s.size(); ++d) {
          auto l_s = sq_s.substr(0, sq_s.size() - d);
          auto r_s = sq_s.substr(sq_s.size() - d);
          ll l = 0, r = 0;
          if(!l_s.empty()) l = std::stoll(l_s);
          if(!r_s.empty()) r = std::stoll(r_s);
          if(l > 0 && r > 0 && l + r == i) {
            kaprekar[i] = true;
            break;
          }
         }
       }
        
       int t_cases, t_case = 1;
       scanf("%d", &t_cases);
       while(t_cases--) {
         printf("case #%d\n", t_case++);
         int l, r;
         scanf("%d %d", &l, &r);
         bool found = false;
         for(int i = l; i <= r; ++i) {
            if(kaprekar[i]) {
              printf("%d\n", i);
              if(!found) found = true;
            }
         }
        if(!found) printf("no kaprekar numbers\n");
        if(t_cases) printf("\n");
       }
    }
}