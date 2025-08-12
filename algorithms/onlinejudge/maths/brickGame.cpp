/*
───────────────────────────────────────────────────────────────
🧳 UVa 11875 Brick Game, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;


namespace algorithms::onlinejudge::maths::brick_game
{
    /** https://onlinejudge.org/external/118/11875.pdf */
    int t_cases, t_case = 1;
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
          int n;
          while_read(n);
          vi team(n);
          for (int i = 0; i < n; i++)
            while_read(team[i]);
          printf("Case %d: %d\n", t_case++, *(team.begin() + team.size() / 2));  
        }        
    }
}