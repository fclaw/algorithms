/*
───────────────────────────────────────────────────────────────
🧳 UVa 12135 Switch Bulbs, https://onlinejudge.org/external/121/12135.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 
using vi = std::vector<int>;

constexpr int MAX_BULBS = 15;

void precompute(const vi& switches, vi& memo) {

  std::queue<int> queue;
  memo[0] = 0;
  queue.push(0);
  while(!queue.empty()) {
    int state = queue.front(); queue.pop();
    int steps = memo[state];
    for(int toggled : switches) {
      int new_state = state ^ toggled;
      if(!(~memo[new_state])) {
        memo[new_state] = 1 + steps;
        queue.push(new_state);
      }
    }
  }
}


namespace algorithms::onlinejudge::advanced_topics::switch_bulbs
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
        bool is_first = true;
        std::cin >> t_cases;
        while(t_cases--) {
          
          if(is_first) {
            is_first = false;
          } else {
            std::cout << std::endl;
          }

          int bulbs_n, switches_n;
          std::cin >> bulbs_n >> switches_n;
          vi switches(switches_n);
          for(int i = 0; i < switches_n; ++i) {
            int d, bulb, mask = 0;
            std::cin >> d;
            for(int j = 0; j < d; ++j) {
              std::cin >> bulb;
              mask |= (1 << bulb);
            }
            switches[i] = mask;
          }
          
          // memo table
          vi memo(1 << bulbs_n, -1);

          // ============================================================
          // 1. RUN THIS ONCE (Precompute all 32,768 states)
          // ============================================================
          precompute(switches, memo);

          printf("Case %d:\n", t_case++);

          int queries_n;
          std::cin >> queries_n;
          while(queries_n--) {
            std::string mask_s;
            std::cin >> mask_s;
            std::bitset<MAX_BULBS> bits(mask_s);
            std::cout << memo[(int)bits.to_ulong()] << "\n";
          }
        }
    }
}
