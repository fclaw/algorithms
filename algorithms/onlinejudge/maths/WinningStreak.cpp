/*
───────────────────────────────────────────────────────────────
🧳  UVa 11176 Winning Streak, https://onlinejudge.org/external/111/p11176.pdf,  rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ld = long double;
using vd = std::vector<ld>;
using vvd = std::vector<vd>;


void backtrack(int games, int streak_so_far, int total_games, ld win_prob, int max_streak, ld prob, ld& avg_prob) {
  if(games == total_games) {
    avg_prob += std::max(max_streak, streak_so_far) * prob;
    return;
  }

  // win the game, streak + 1
  backtrack(games + 1, streak_so_far + 1, total_games, win_prob, max_streak, prob * win_prob, avg_prob);
  // lose the game, streak reset to zero
  backtrack(games + 1, 0, total_games, win_prob, std::max(streak_so_far, max_streak), prob * (1.0 - win_prob), avg_prob);
}


namespace algorithms::onlinejudge::maths::winning_streak
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

        int games;
        double prob;
        while(scanf("%d %lf", &games, &prob) == 2 && games) {
          ld avg_prob = 0.0;
          backtrack(0, 0, games, prob, 0, 1.0, avg_prob);
          printf("%0.10Lf\n", avg_prob);
        }
    }
}
