/*
───────────────────────────────────────────────────────────────
🧳 UVa 10684 The jackpot, https://onlinejudge.org/external/106/10684.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;



namespace algorithms::onlinejudge::complete_search::jackpot
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

        int N;
        while(std::cin >> N && N) {
          vi bets(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> bets[i];
          }

          // Kadane's algorithm
          int curr_sum = 0;
          int winning_streak = 0;

          for(int bet : bets) {
            curr_sum += bet;
            winning_streak = std::max(winning_streak, curr_sum);
            if(curr_sum < 0) {
              curr_sum = 0; // Reset to 0 and start from next element!
            }
          }
          if(winning_streak <= 0) {
            printf("Losing streak.\n");
          } else {
            printf("The maximum winning streak is %d.\n", winning_streak);
          }
        }
    }
}