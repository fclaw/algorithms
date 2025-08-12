/*
───────────────────────────────────────────────────────────────
🧳 UVa 12149 Feynman, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::Feynman
{
    /** https://onlinejudge.org/external/121/12149.pdf */
    int square_s;
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
        
        while(while_read(square_s) && square_s) {
          int nums = 0;
          for (int i = 1; i <= square_s; i++) {
            nums += i * i;
          }
          std::cout << nums << '\n';
        }        
    }
}