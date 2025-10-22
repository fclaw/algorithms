/*
───────────────────────────────────────────────────────────────
🧳 UVa 10111 Find the Winning Move, https://onlinejudge.org/external/101/10111.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ull = unsigned long long;


namespace algorithms::onlinejudge::maths::tic_tac_toe
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

        int piles, stones;
        while(scanf("%d", &piles) == 1 && piles) {
          int is_win_pos = 0;
          for(int p = 0; p < piles; ++p) {
            scanf("%d", &stones);
            is_win_pos = is_win_pos ^ stones;
          }
          printf("%s\n", is_win_pos != 0 ? "Yes" : "No");
        }
    }
}