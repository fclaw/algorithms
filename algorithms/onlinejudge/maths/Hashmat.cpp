/*
───────────────────────────────────────────────────────────────
🧳 UVa 10055 Hashmat the brave warrior, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;



namespace algorithms::onlinejudge::maths::Hashmat
{
    /** https://onlinejudge.org/external/100/10055.pdf */
    // the numbers are not greater then 2 ^ 32. to fit in 2 ^ 32 ll is required
    ll x, y;
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
        
        while(while_read(x, y)) {
          std::cout << std::abs(x - y) << std::endl;
        }
    }
}