/*
───────────────────────────────────────────────────────────────
🧳 UVa 11970 Lucky Numbers, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int MAX_LUCKY = 32000;
using vi = std::vector<int>;


namespace algorithms::onlinejudge::maths::lucky
{
    /** https://onlinejudge.org/external/119/11970.pdf */
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
         
        vi squares(MAX_LUCKY);  
        for(int n = 1; n <= MAX_LUCKY; ++n) {
          squares[n - 1] = n * n;
        }

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n;
          scanf("%d", &n);
          printf("Case %d: ", t_case++);

          vi lucky_numbers;
          for(int s = 0; s < MAX_LUCKY; ++s) {
            int lucky = n - squares[s];
            if(lucky > 0 && !(lucky % (s + 1))) {
              lucky_numbers.push_back(lucky);
            }
          }
          std::sort(lucky_numbers.begin(), lucky_numbers.end());
          for(size_t i = 0; i < lucky_numbers.size(); ++i) {
            printf("%d", lucky_numbers[i]);
            if(i != lucky_numbers.size() - 1) printf(" ");
          }
          printf("\n");
        }
    }
}