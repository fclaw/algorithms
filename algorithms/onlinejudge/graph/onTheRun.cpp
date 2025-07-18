/*
───────────────────────────────────────────────────────────────
🧳 UVa 590 Always on the run, rt: s
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



constexpr int DAYS = 100;
constexpr int CITIES = 10;
constexpr int inf = 1e5;


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


struct State
{
    int city;
    int days; // how many days the journey lasts
};


namespace algorithms::onlinejudge::graph::on_the_run
{
    /** https://onlinejudge.org/external/5/590.pdf */
    int n, k, start, end, t_case = 1;
    int memo[CITIES + 1][DAYS + 1];
    int calculate_min_cost(State s, vvvi& flights) {    
      int curr_city = s.city;
      int days = s.days;
       
      if(days > k) return inf;

      if(curr_city == end) {
         if(days == k)  
           return 0;
      }

      int& best = memo[curr_city][days];
      if(~best) return best;
      
      best = inf;
      // try every cities
      for(int dest_city = 0; dest_city < n; ++dest_city) {
        if(curr_city == dest_city) continue;
        int period = (int)flights[curr_city][dest_city].size();
        int cost = flights[curr_city][dest_city][(days % period)];
        if(cost > 0) {
          State ns = {dest_city, days + 1};
          int local = calculate_min_cost(ns, flights);
          if(local != inf) {
            local += cost;
            best = std::min(best, local);
          }
        }
      }
      return best;
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
        
        bool first_case = true;  
        while(while_read(n, k)) {
          if(n == 0 && k == 0) break;
          vvvi flights(n, vvi(n));
          for(int start = 0; start < n; ++start) {
            for(int end = 0; end < n; ++end) {
              if(start != end) {
                int days, cost;
                while_read(days);
                vi schedule(days);
                for(int d = 0; d < days; ++d) {
                  while_read(cost);
                  schedule[d] = cost;
                }
                flights[start][end] = schedule;
              }
            }
          }

          start = 0, end = n - 1;
          std::memset(memo, -1, sizeof memo);
          int min_cost = calculate_min_cost({start, 0}, flights);
          std::string ans = min_cost != inf ? "The best flight costs " + std::to_string(min_cost) + "." : "No flight possible.";
          printf("Scenario #%d\n%s\n\n", t_case++, ans.c_str());
      }
    }
}