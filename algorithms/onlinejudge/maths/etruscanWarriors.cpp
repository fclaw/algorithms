/*
───────────────────────────────────────────────────────────────
🧳 UVa 11614 Etruscan Warriors Never Play Chess, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * ALGORITHMIC STRATEGY: UVa 11614 - Etruscan Warriors Never Play Chess
 * =====================================================================================
 *
 * The problem asks for the maximum number of rows 'n' that can be formed by a given
 * number of warriors 'X'. The solution is found by deriving a direct mathematical

 * formula based on a clever geometric insight.
 *
 * --- The Geometric Derivation ---
 *
 * 1.  **Model the Formation on a Square Grid:**
 *     Imagine an `n x n` square grid of cells. The total number of cells in this
 *     square is `n * n`.
 *
 * 2.  **Deconstruct the Square:**
 *     This `n x n` square can be partitioned by its main diagonal into three distinct
 *     , non-overlapping parts:
 *       a) The cells **ON** the main diagonal. There are exactly `n` such cells.
 *       b) The cells **ABOVE** the main diagonal.
 *       c) The cells **BELOW** the main diagonal.
 *
 * 3.  **Relate to the Warriors:**
 *     The problem's triangular formation `1 + 2 + ... + n` warriors can be perfectly
 *     mapped to the cells ON and ABOVE the main diagonal.
 *     - Total Warriors (`X`) = (Cells ON diagonal) + (Cells ABOVE diagonal).
 *
 * 4.  **Count the "Empty" Cells:**
 *     By symmetry, the number of cells ABOVE the diagonal is equal to the number
 *     of cells BELOW the diagonal. Let's call this the "sum of empty cells."
 *     Total Cells = (Cells ON diagonal) + 2 * (Sum of empty cells)
 *     `n * n = n + 2 * (Sum of empty cells)`
 *     `2 * (Sum of empty cells) = n*n - n = n * (n - 1)`
 *     `Sum of empty cells = n * (n - 1) / 2`
 *
 *     This is a brilliant independent derivation of the formula for the (n-1)-th
 *     triangular number.
 *
 * 5.  **Form the Final Equation:**
 *     We can now form an equality for the total number of warriors `X`:
 *     Total Warriors (`X`) = Total Cells in Square - Sum of empty cells
 *     `X = n*n - (n * (n - 1) / 2)`
 *
 *     Let's simplify this to solve for `n`:
 *     `2X = 2n² - n(n - 1)`
 *     `2X = 2n² - n² + n`
 *     `2X = n² + n`
 *     `n² + n - 2X = 0`
 *
 * 6.  **The Solution:**
 *     This is the same quadratic equation derived via the arithmetic series method.
 *     Solving for the positive root `n` using the quadratic formula gives the answer.
 *     The final number of full rows is `floor(n)`.
 *
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



// Change all internal types to long double
std::vector<double> solve_quadratic_precise(long double a, long double b, long double c) {
    std::vector<double> solutions;

    // --- Calculate the Discriminant using long double ---
    long double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) { // For very large numbers, the epsilon check is less meaningful
        // Two solutions (which might be the same if discriminant is 0)
        long double sqrt_discriminant = std::sqrt(discriminant);
        long double x1 = (-b + sqrt_discriminant) / (2 * a);
        long double x2 = (-b - sqrt_discriminant) / (2 * a);
        
        // Convert back to double for the return vector
        solutions.push_back(static_cast<double>(x1));
        solutions.push_back(static_cast<double>(x2));
    }
    // else: no real solutions, return empty vector
    
    return solutions;
}


namespace algorithms::onlinejudge::maths::etruscan_warriors
{
    /** https://onlinejudge.org/external/116/11614.pdf */
    int t_cases;
    long long warriors_n;
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
        while (t_cases--) {
          while_read(warriors_n);
          auto roots = solve_quadratic_precise(1.0L, 1.0L, -2.0L * warriors_n);
          long long row = roots.front();
          std::cout << row << std::endl;
        }
  
    }
}