/*
───────────────────────────────────────────────────────────────
🧳 UVa 10014 Simple calculations, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vd = std::vector<double>;


namespace algorithms::onlinejudge::maths::simple_calculations
{
    /** https://onlinejudge.org/external/100/10014.pdf */
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

        // a_1 = 2 * a_0 + a_n_1 - 4 * sum i = 1, n - 1 c_i - 2 * c_n;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d", &n);
          double a_0, a_n_1;
          scanf("%lf %lf", &a_0, &a_n_1);
          vd c(n);
          for(int i = 0; i < n; ++i) {
            scanf("%lf", &c[i]);
          }
           
          double sum_c = 0.0;
          for(int i = n; i >= 1; --i) 
            sum_c += 2 * i * c[n - i];

          double a_1 = (n * a_0 + a_n_1 - sum_c) / (n + 1);
          printf("%.2lf\n", a_1);
          if(t_cases) printf("\n");
        }
    }
}