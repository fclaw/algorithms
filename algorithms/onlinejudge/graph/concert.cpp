/*
───────────────────────────────────────────────────────────────
🧳 UVa 12875 Concert Tour, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cctype>



using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using ll = long long;

constexpr int inf = 1e5;

struct State
{
    int store;
    int concert;
};


namespace algorithms::onlinejudge::graph::concert_tour
{
    /** https://onlinejudge.org/external/128/12875.pdf */
    int t_cases, n_stores, n_concerts;
    int make_tour(State s, const vvi& profits, const vvi& travel_cost, vvi& memo) {
      int store = s.store;
      int concert = s.concert;

      if(concert == n_concerts) return 0;

      int& best_profit = memo[store][concert];
      if(~best_profit) return best_profit;

      best_profit = 0;
      int curr_profit = profits[store][concert];
      for(int next_store = 0; next_store < n_stores; ++next_store) {
        State ns = {next_store, concert + 1};
        int net_profit = curr_profit - travel_cost[store][next_store];
        best_profit = std::max(best_profit, net_profit + make_tour(ns, profits, travel_cost, memo));
      }

      return best_profit;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(n_stores, n_concerts);
          vvi profits(n_stores, vi(n_concerts));
          for(int s = 0; s < n_stores; ++s) {
            for(int c = 0; c < n_concerts; ++c) {
              while_read(profits[s][c]);
            }
          }
          
          vvi travel_cost(n_stores, vi(n_stores));
          for(int i = 0; i < n_stores; ++i) {
            for(int j = 0; j < n_stores; ++j) {
              while_read(travel_cost[i][j]);
            }
          }

          int max_profit = 0;
          vvi memo(n_stores + 1, vi(n_concerts + 1, -1));
          for(int store = 0; store < n_stores; ++store) {
            State init = {store, 0};
            max_profit = std::max(max_profit, make_tour(init, profits, travel_cost, memo));
          }
          std::cout << max_profit << std::endl;
        }
    }
}