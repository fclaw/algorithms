/*
───────────────────────────────────────────────────────────────
🧳 UVa 11311 Exclusively Edible, https://onlinejudge.org/external/113/11311.pdf, rt: s
   game theory, reducible to Nim game; 
   we can view the game that Hansel and Gretel are playing as Nim game, 
   where there are 4 heaps - cakes left/below/right/above the topping; 
   take the Nim sum of these 4 values and if they are equal to 0, Gretel loses)
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::exclusively_edible
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

        int t_cases, m, n, r, c;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d %d %d %d", &m, &n, &r, &c);
          printf("%s\n", r ^ c ^ (m - r - 1) ^ (n - c - 1) ? "Gretel" : "Hansel");
        }
    }
}