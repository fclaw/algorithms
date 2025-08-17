/*
───────────────────────────────────────────────────────────────
🧳 UVa 846 Steps, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::steps
{
    /** https://onlinejudge.org/external/8/846.pdf */
    int t_cases, start, end;
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
        
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d", &start, &end);

          if(start == end) {
            printf("0\n");
            continue;
          }

          int D = end - start;
          // the base arch (1...k...1)
          int k = std::sqrt(D);
          int left_sum = k * (k + 1) / 2; // from 1 to k
          int right_sum = k * (k - 1) / 2; // from k - 1 to 1
          int base_dist = left_sum + right_sum;
          int base_steps = 2 * k - 1;

          int gap = D - base_dist;
          if(gap == 0) {
            printf("%d\n", base_steps);
          } else {
            //  Calculate the number of extra steps needed to cover the gap.
            //  We use the largest available step size, 'k', to do this + 1
            int extra_steps = std::ceil((double)gap / k);
            printf("%d\n", base_steps + extra_steps);
          }
        }   
    }
}