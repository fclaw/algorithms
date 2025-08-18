/*
───────────────────────────────────────────────────────────────
🧳 UVa 10025 The ? 1 ? 2 ? ... ? n = k problem, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;


namespace algorithms::onlinejudge::maths::nk_problem
{
    /** https://onlinejudge.org/external/100/10025.pdf */
    int t_cases;
    ll target;
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
        while (t_cases--) {
          scanf("%lld", &target);
          
          if(target < 0) target *= -1;

          int num = 1;
          ll sum = 0;
          do {
            sum += num;
          } while(sum < target && ++num);
          int diff = sum - target;
          if(sum == target || !(diff % 2)) {
            printf("%d\n", num);
          } else {
            if(!(num % 2)) num += 1;
            else num += 2;
            printf("%d\n", num);
          }
          if(t_cases) printf("\n");
        }          
    }
}