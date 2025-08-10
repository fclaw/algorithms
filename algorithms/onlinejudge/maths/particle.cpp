/*
───────────────────────────────────────────────────────────────
🧳 UVa 10071 Back to High School Physics, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::particle
{
    /** https://onlinejudge.org/external/100/10071.pdf */
    int velocity, time;
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
        
        while(while_read(velocity, time)) {
          std::cout << (velocity * 2 * time) << std::endl;
        }
    }
}