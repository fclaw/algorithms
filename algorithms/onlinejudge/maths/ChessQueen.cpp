/*
───────────────────────────────────────────────────────────────
🧳 UVa 11538 Chess Queen, https://onlinejudge.org/external/115/11538.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ull = unsigned long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;


// Renamed to 'binominal' to match your original code's convention.
// This function calculates C(n, k), the binomial coefficient "n choose k".
ull binominal(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 2) return (ull)n * (n - 1) / 2;
    if (k == 3) return (ull)n * (n - 1) * (n - 2) / 6;
    // ... add other cases or a general formula if needed ...
    return 1;
}


namespace algorithms::onlinejudge::maths::chess_queen
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


        ull rows_in, cols_in;
        while(scanf("%llu %llu", &rows_in, &cols_in) == 2 && 
              (rows_in != 0 && cols_in != 0)) {

          ull rows = rows_in;
          ull cols = cols_in;
          if(cols > rows) std::swap(rows, cols);

          // rows
          ull count_rows = rows * binominal(cols, 2);
          // cols
          ull count_cols = cols * binominal(rows, 2);
          // diagonals
          ull count_diags = 2 * (rows - cols + 1) * binominal(cols, 2);
          for(int i = cols - 1; i > 0; --i)
            count_diags += 4 * binominal(i, 2);
          printf("%llu\n", 2 * (count_rows + count_cols + count_diags));
        }
    }
}