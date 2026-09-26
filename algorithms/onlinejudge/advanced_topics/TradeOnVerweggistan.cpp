/*
───────────────────────────────────────────────────────────────
🧳 UVa 812 Trade on Verweggistan, https://onlinejudge.org/external/8/812.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;



bool cache[55][1010];

void dp(int idx, const vvi& all_boxes, int curr_val, std::unordered_set<int>& values) {
 
  if(idx == (int)all_boxes.size()) {
    if(values.count(curr_val) == 0) {
      values.insert(curr_val);
    }
    return;
  }

  if(cache[idx][curr_val]) {
    return;
  }

  cache[idx][curr_val] = true;
  for(int b : all_boxes[idx]) {
    dp(idx + 1, all_boxes, curr_val + b, values);
  }
}


std::pair<int, std::string> get_max_profit(const vvi& piles) {

  int total_max_profit = 0;
  std::vector<vi> all_boxes;

  for (int i = 0; i < (int)piles.size(); ++i) {
    const vi& stack = piles[i];
    
    int max_profit = 0;
    vi best_counts = {0}; // Buying 0 boxes gives profit 0!
    
    int cumulative_profit = 0;
    for (int b = 0; b < (int)stack.size(); ++b) {
      cumulative_profit += (10 - stack[b]);
        
      if (cumulative_profit > max_profit) {
        max_profit = cumulative_profit;
        best_counts.clear();
        best_counts.push_back(b + 1); // 1-based count!
      } else if (cumulative_profit == max_profit) {
        best_counts.push_back(b + 1); // Another count gives the same max!
      }
    }
    
    total_max_profit += max_profit;
    all_boxes.push_back(best_counts);
  }
 
  std::unordered_set<int> s_values;
  std::memset(cache, false, sizeof cache);
  dp(0, all_boxes, 0, s_values);
  vi v_values(s_values.begin(), s_values.end());
  std::sort(v_values.begin(), v_values.end());
  std::string values;
  int counter = 0;
  for(int v : v_values) {
    if(counter >= 10) {
      break;
    }
    counter++;
    values += std::to_string(v) + " ";
  }
  values.pop_back();
  return {total_max_profit, values};
}


namespace algorithms::onlinejudge::advanced_topics::trade_on_Verweggistan
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

        int piles_n, workyards_n = 1;
        bool is_first_case = true;
        while(std::cin >> piles_n 
              && piles_n) {

          if(is_first_case) {
            is_first_case = false;
          } else {
            std::cout << "\n";
          }

          vvi piles;
          for(int p = 0; p < piles_n; ++p) {
            int stacks_n;
            std::cin >> stacks_n;
            if(stacks_n > 0) {
              vi stacks(stacks_n);
              for(int s = 0; s < stacks_n; ++s) {
                std::cin >> stacks[s];
              }
              piles.push_back(stacks);
            }
          }
          std::pair<int, std::string> ans = get_max_profit(piles);
          printf("Workyards %d\nMaximum profit is %d.\nNumber of pruls to buy: %s\n", workyards_n++, ans.first, ans.second.c_str());
        }
    }
}