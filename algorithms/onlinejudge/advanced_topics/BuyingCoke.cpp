/*
───────────────────────────────────────────────────────────────
🧳 UVa 10626 Buying Coke, https://onlinejudge.org/external/106/10626.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



int cache[160][150][60];

int min_coins_required(int bottles, int coins5, int coins10, int bottles_needed, int total_money) {

  if(bottles == bottles_needed) {
    return 0;
  }

  if(~cache[bottles][coins5][coins10]) {
    return cache[bottles][coins5][coins10];
  }

  // conversation law
  int coins1 = total_money - 5 * coins5 - 10 * coins10 - 8 * bottles;
  int best = INT32_MAX;
  // 8 coins1
  if(coins1 >= 8) {
    best = std::min(best, 8 + min_coins_required(bottles + 1, coins5, coins10, bottles_needed, total_money));
  }

  // 2 coins5
  if(coins5 >= 2) {
    best = std::min(best, 2 + min_coins_required(bottles + 1, coins5 - 2, coins10, bottles_needed, total_money));
  }

  // 1 coins5 and 3 coins1
  if(coins5 >= 1 && coins1 >= 3) {
    best = std::min(best, 4 + min_coins_required(bottles + 1, coins5 - 1, coins10, bottles_needed, total_money));
  }

  // 1 coins10
  if(coins10 > 0) {
   best = std::min(best, 1 + min_coins_required(bottles + 1, coins5, coins10 - 1, bottles_needed, total_money)); 
  }

  // 1 coins10, 3 coins1 -> 1 bottle and 1 coins5 in exchange
  if(coins10 >= 1 && coins1 >= 3) {
    best = std::min(best, 4 + min_coins_required(bottles + 1, coins5 + 1, coins10 - 1, bottles_needed, total_money)); 
  }

  return (cache[bottles][coins5][coins10] = best);
}


namespace algorithms::onlinejudge::advanced_topics::buying_coke
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

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int bottles, coins1, coins5, coins10;
          while_read(bottles, coins1, coins5, coins10);
          std::memset(cache, -1, sizeof cache);
          int total_money = 1 * coins1 + 5 * coins5 + 10 * coins10;
          int min_coins = min_coins_required(0, coins5, coins10, bottles, total_money);
          printf("%d\n", min_coins != INT32_MAX ? min_coins : 0); 
        }
    }
}