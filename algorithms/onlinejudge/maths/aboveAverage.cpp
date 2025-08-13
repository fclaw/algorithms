/*
───────────────────────────────────────────────────────────────
🧳 UVa 10370 Above Average, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;


namespace algorithms::onlinejudge::maths::above_average
{
    /** https://onlinejudge.org/external/103/10370.pdf */
    int t_cases, n;
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

        while_read(t_cases);
        while(t_cases--) {
          while_read(n);
          vi grades(n);
          for(int i = 0; i < n; ++i) {
            while_read(grades[i]);
          }
          int sum = std::accumulate(grades.begin(), grades.end(), 0);
          double avg = (double)sum / n;
          int above_avg = 0;
          for(int grade : grades) {
            if(grade > avg) above_avg++;
          }
          printf("%.3f%%\n", (double)above_avg / n * 100);
        }
    }
}