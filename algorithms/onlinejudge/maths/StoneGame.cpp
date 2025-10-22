/*
───────────────────────────────────────────────────────────────
🧳 UVa 10165 Stone Game, https://onlinejudge.org/external/101/10165.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




namespace algorithms::onlinejudge::maths::stone_game
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
         // --- The Nim-Sum Solution for Impartial Games ---
         // This game is a variant of the classic impartial game of Nim. The winner is determined
         // by whether the starting position is a "Winning" or "Losing" state.
         // The state of any Nim game can be characterized by its "Nim-Sum," which is the
         // bitwise XOR sum of the sizes of all the piles.
          int is_win_pos = 0;
          for(int p = 0; p < piles; ++p) {
            scanf("%d", &stones);
            is_win_pos ^= stones;
          }
          // Bouton's Theorem states the winning condition:
          // - If the Nim-Sum is non-zero, it is a Winning Position (the current player can force a win).
          // - If the Nim-Sum is zero, it is a Losing Position (the current player will lose if the
          //   opponent plays optimally).
          // Since the problem asks if the first player can win, we just need to check if the initial Nim-Sum is non-zero.
          printf("%s\n", is_win_pos != 0 ? "Yes" : "No");
        }
    }
}