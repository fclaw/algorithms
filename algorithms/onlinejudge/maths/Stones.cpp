/*
───────────────────────────────────────────────────────────────
🧳 UVa 12469 Stones, https://onlinejudge.org/external/124/12469.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum Player { Roberto, Alicia };


std::string player_to_str(Player p) {
  return p == Roberto ? "Roberto" : "Alicia";
}

constexpr int MAX_STONES = 1000;


bool memo[MAX_STONES + 1][MAX_STONES + 1];
bool is_used[MAX_STONES + 1][MAX_STONES + 1];


bool can_win(int stones_left, int allowed_to_remove, bool is_first_round) {
  if(!is_first_round &&
     stones_left <= allowed_to_remove && 
     allowed_to_remove >= 1)
    return true;
    
  if(is_used[stones_left][allowed_to_remove]) { 
    return memo[stones_left][allowed_to_remove];
  }

  is_used[stones_left][allowed_to_remove] = true;
  bool is_win_pos = false;
  int stones = 
    is_first_round ? 
      stones_left - 1 : 
      std::min(stones_left, allowed_to_remove);
  for(int s = 1; s <= stones; ++s) {
    is_win_pos |= !can_win(stones_left - s, 2 * s, false);
  }
  return memo[stones_left][allowed_to_remove] = is_win_pos;
}


namespace algorithms::onlinejudge::maths::stones
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

        int stones;
        std::memset(memo, false, sizeof memo);
        std::memset(is_used, false, sizeof is_used);
        while(scanf("%d", &stones) == 1 && stones) {
          bool is_first_round = true;
          printf("%s\n", (can_win(stones, MAX_STONES, is_first_round) ? player_to_str(Alicia) : player_to_str(Roberto)).c_str());
        }
    }
}