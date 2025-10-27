/*
───────────────────────────────────────────────────────────────
🧳 UVa 11489 Integer Game, https://onlinejudge.org/external/114/11489.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi =  std::vector<int>;


enum Player { S, T };

Player switch_player(Player p) {
  return p == S ? T : S;
}

std::string player_to_string(Player p) {
  return p == S ? "S" : "T";
}


bool all_zeros(const std::vector<int>& freq) {
  bool is_all_zeros = true;
  for(int i = 1; i <= 9; ++i)
    is_all_zeros = is_all_zeros && (freq[i] == 0);
  return is_all_zeros;
}

std::map<std::pair<int, std::vector<int>>, bool> memo;

bool is_win(int sum, std::vector<int>& freq) {

  if(all_zeros(freq)) return false;

  if(memo.count({sum, freq}))
    return memo[{sum, freq}];

  for(int take = 1; take <= 9; ++take) {

    // --- Strategic Shortcut: The "Pass the Turn" Optimization ---
    //
    // The core insight for making this solution efficient is to handle digits divisible
    // by 3 ({3, 6, 9}) as a special case.
    //
    // WHY IS IT SPECIAL?
    // When a player removes a digit 'd' where (d % 3 == 0), the sum of the remaining
    // digits modulo 3 DOES NOT CHANGE. (S - d) % 3 == S % 3.
    // This means if the opponent was not in a position to make an immediate winning
    // move before, they are STILL not in a position to win. Such a move doesn't
    // change the strategic landscape of the game; it effectively just "passes the turn."
    //
    // THE OPTIMIZATION:
    // Instead of recursively simulating the removal of these "passing" moves one by one,
    // which would be very slow if there are many of them, we can determine the winner of
    // this "mini-game" of turn-passing with a single parity argument.
    //
    // We can "fast-forward" by imagining all 'k' = freq[take] of these digits are the
    // only moves left to play. Players will take them one by one.
    //   - If 'k' is ODD: The first player (us) will take the 1st, 3rd,..., last one.
    //     This leaves the OPPONENT to face the remaining subgame.
    //   - If 'k' is EVEN: The first player (us) will take the 1st, 3rd,..., (k-1)th one.
    //     The opponent takes the last one, leaving US to face the remaining subgame.
    //
    // THE LOGIC:
    // Let `res = is_win(subgame)` be the result of the game *after* all these digits are gone.
    //   - If freq[take] is ODD: We want the opponent to lose. So, we win if `!res` is true.
    //   - If freq[take] is EVEN: We want ourselves to lose the subgame (since the opponent wins it). No, we want ourselves to win.
    //     If `freq[take]` is even, we are the one left to face the subgame. So we win if `res` is true.
    //
    // This block implements this parity logic, effectively pruning a long, linear chain
    // from the game tree and replacing it with an O(1) calculation. This is critical for
    // passing the time limit on large inputs.

    if((take == 3 || 
        take == 6 || 
        take == 9) && 
        freq[take] > 0) {
      int new_sum = sum - take * freq[take];
      if(new_sum >= 0 &&
         new_sum % 3 == 0) {
        int old_freq = freq[take];
        freq[take] = 0;
        bool opponent_wins_sub_game = is_win(new_sum, freq);
        freq[take] = old_freq;
       
        // Apply the parity logic
        if(old_freq % 2 != 0) { // ODD number of these moves. Opponent faces the sub-game.
          if(!opponent_wins_sub_game) {
            return memo[{sum, freq}] = true; // We can force a win.
          }
        } else { // EVEN number of these moves. We face the sub-game.
          if(opponent_wins_sub_game) { // It's our turn, and we know it's a winning sub-game for the current player.
            return memo[{sum, freq}] = true; // We can force a win.
          }
        }
        // This path was not a guaranteed win, so we continue the main loop to check other moves.
        continue; // A 'continue' makes the intent clear.
      }
    }

    int new_sum = sum - take;
    if(freq[take] > 0 && 
       new_sum >= 0 &&
       new_sum % 3 == 0) {
      freq[take]--;
      if(!is_win(new_sum, freq)) {
        freq[take]++;
        return memo[{sum, freq}] = true;
      }
      freq[take]++;
    }
  }
  return memo[{sum, freq}] = false;
}


namespace algorithms::onlinejudge::maths::integer_game
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

        int t_cases, t_case = 1;
        std::string s;
        scanf("%d", &t_cases);
        while(t_cases--) {
          while_read(s);
          vi freq(10, 0);
          int sum = 0;
          Player player = S;
          for(char c : s) {
            int n = c - '0';
            freq[n]++;
            sum += n;
          }

          printf("Case %d: %s\n", t_case++, (is_win(sum, freq) ? player_to_string(player) : player_to_string(switch_player(player))).c_str());
        }
    }
}