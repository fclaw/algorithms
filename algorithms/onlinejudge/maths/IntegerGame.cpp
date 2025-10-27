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

    if((take == 3 || take == 6 || take == 9) && freq[take] > 0) {
      int new_sum = sum - take * freq[take];
      if(new_sum >= 0 &&
         new_sum % 3 == 0) {
        int old_freq = freq[take];
        freq[take] = 0;
        bool res = is_win(new_sum, freq);
        freq[take] = old_freq;
        if(freq[take] % 2 != 0 && !res)
          return memo[{sum, freq}] = true;
        else if(old_freq % 2 == 0 && !res)
          return memo[{sum, freq}] = false;
        else if (old_freq % 2 != 0 && res)
          return memo[{sum, freq}] = false;
        else if (old_freq % 2 == 0 && res)
          return memo[{sum, freq}] = true;
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