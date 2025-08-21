/*
───────────────────────────────────────────────────────────────
🧳 UVa 651 Deck, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>






namespace algorithms::onlinejudge::maths::deck
{
    /** https://onlinejudge.org/external/6/651.pdf */
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

        printf("# Cards Overhang\n");  
        int cards_n;
        while(scanf("%d", &cards_n) == 1) {
          double max_overhang = 0.0;
          for(int c = 1; c <= cards_n; ++c) 
            max_overhang += ((double)1 / (2 * c));
          printf("%5d %9.3f\n", cards_n, max_overhang);
        }
    }
}