/*
───────────────────────────────────────────────────────────────
🧳 UVa 11545 Avoiding Jungle in the Dark, rt: s
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
constexpr int MAX = 1010;
constexpr int WALK_TM = 16;
constexpr int REST_TM = 8; 
constexpr int NIGHT_START = 18;
constexpr int NIGHT_END = 6;
constexpr int TIME_24 = 24; 


 bool is_jungle[MAX];

bool can_walk(int walk_tm) { return walk_tm < WALK_TM; }
bool is_night(int tm) { return (tm >= NIGHT_START && tm <= 23) || (tm >= 0 && tm <= NIGHT_END); }
bool is_pos_safe(int pos, int tm) { 
  return !is_jungle[pos] ||
         (is_jungle[pos] && 
          !is_night(tm));
}

struct State
{
    int pos;
    int clock_tm;
    int on_foot_tm;
};


namespace algorithms::onlinejudge::graph::pilgrim
{
    /** https://onlinejudge.org/external/115/11545.pdf */
    int t_cases, dest, c = 1;
    int minimize_pilgrimage_time(State s, vvi& memo) {
      int pos = s.pos;
      int on_foot_tm = s.on_foot_tm;
      int clock_tm = s.clock_tm;
 
      if(pos == dest) return 0;

      int& best_tm = memo[pos][clock_tm];
      if(~best_tm) return best_tm;
      best_tm = inf;

      if(can_walk(on_foot_tm)) {
        int go_on = inf;
        int go_on_clock_tm = (clock_tm + 1) % TIME_24;
        if(is_pos_safe(pos + 1, go_on_clock_tm)) {
          State go_on_s = {pos + 1, go_on_clock_tm, 1 + on_foot_tm};
          go_on = 1 + minimize_pilgrimage_time(go_on_s, memo);
        }
        int rest_clock_tm = (clock_tm + REST_TM) % TIME_24;
        int rest = inf;
        if(is_pos_safe(pos, rest_clock_tm)) {
          State rest_s = {pos, rest_clock_tm, 0};
          rest = REST_TM + minimize_pilgrimage_time(rest_s, memo);
        }

        best_tm = std::min(best_tm, std::min(rest, go_on));
      } else {
        // either we are on the plain (no time of clock matters) or 
        // in a jungle during daylight
        if(is_pos_safe(pos, clock_tm)) {
           int rest_clock_tm = (clock_tm + REST_TM) % TIME_24;
           if(is_pos_safe(pos, rest_clock_tm)) {
             State rest_s = {pos, rest_clock_tm, 0};
             best_tm = std::min(best_tm, REST_TM + minimize_pilgrimage_time(rest_s, memo));
           }
        }
      }

      return best_tm;
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
          std::string s;
          while_read(s);
          int l = (int)s.size();
          std::memset(is_jungle, false, sizeof is_jungle);
          for(int i = 0; i < l; ++i) {
            if(s[i] == '*') is_jungle[i] = true;
            if(s[i] == 'D') dest = i;
          }
          vvi memo(l + 1, vi(TIME_24 + 1, -1));
          State init = {0, 6, 0};
          int min_tm = minimize_pilgrimage_time(init, memo);
          printf("Case #%d: %d\n", c++, min_tm != inf ? min_tm : -1);
        }
    }
}