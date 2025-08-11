/*
───────────────────────────────────────────────────────────────
🧳 UVa 11805 Bafana Bafana, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::bafana
{
    /** https://onlinejudge.org/external/118/11805.pdf */
    int t_cases, n, k, p, t_case = 1;
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
        while(t_cases--) {
          while_read(n, k, p);
          int last_player = (p % n + k) % n;
          printf("Case %d: %d\n", t_case++, last_player == 0 ? n : last_player);
        }  
    }
}