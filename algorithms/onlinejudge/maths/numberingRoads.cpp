/*
───────────────────────────────────────────────────────────────
🧳 UVa 11723 Numbering Roads!, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int MAX_LETTER = 26;

namespace algorithms::onlinejudge::maths::numbering_roads
{
    /** https://onlinejudge.org/external/117/11723.pdf */
    int roads, numbers, t_case = 1;
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
        
        while(while_read(roads, numbers) && roads && numbers) {
          int undesignated_roads = roads - numbers;
          int letters = undesignated_roads / numbers;
          int aux_letters = undesignated_roads % numbers > 0 ? 1 : 0;
          int min_letters = letters + aux_letters;
          printf("Case %d: %s\n", t_case++, min_letters > MAX_LETTER ? "impossible" : std::to_string(min_letters).c_str());
        }
    }
}