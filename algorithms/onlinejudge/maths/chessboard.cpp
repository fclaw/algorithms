/*
───────────────────────────────────────────────────────────────
🧳 UVa 10751 Chessboard, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::chessboard
{
    /** https://onlinejudge.org/external/107/10751.pdf */
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
        
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d", &n);

          if(n == 1) {
            printf("0.000\n");
            if(t_cases) printf("\n");
            continue;
          }

          if(n == 2) {
            printf("4.000\n");
            if(t_cases) printf("\n");
            continue;
          }

          // --- GENERAL CASE: N > 2 ---
          // The following logic seems to be an attempt to calculate the path length by
          // summing different categories of segments. The names suggest a pattern
          // involving fixed segments, diagonal connections, and diagonals of
          // varying lengths.
          double sum_fixed_segs = 2 * (n - 1) + 5;
          // This variable seems to count the number of connections made via diagonals.
          double sum_diag_conns = 2 * n - 7;
          // This part calculates the length of diagonals. sqrt(2 * L*L) is L*sqrt(2).
          // It starts with a diagonal of length (n-2)*sqrt(2).
          double sum_diags = std::sqrt(2 * (n - 2) * (n - 2));
          // It then adds more diagonals with lengths from 1*sqrt(2) to (n-3)*sqrt(2).
          for(int i = 1; i <= n - 3; ++i) 
            sum_diags += 2 * std::sqrt(2 * (i * i));
          double path = sum_fixed_segs + sum_diag_conns + sum_diags;
          printf("%.3lf\n", path);
          if(t_cases) printf("\n");
        }
    }
}