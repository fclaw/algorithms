/*
───────────────────────────────────────────────────────────────
🧳 UVa 910 TV game,  rt: s
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

struct Answer
{
    char yes;
    char no;
};

using map = std::unordered_map<char, Answer>;

struct State
{
    char pos;
    int moves;
};


namespace algorithms::onlinejudge::graph::tv_game
{
    /** https://onlinejudge.org/external/9/910.pdf */
    int n, threshold;
    std::unordered_set<char> targets;
    ll count_ways(State s, const map& answers, std::vector<std::vector<ll>>& memo) {
      char pos = s.pos;
      int moves = s.moves;

      // --- BASE CASE ---
      // The recursion stops when we have taken the required number of moves.
      if(moves == threshold) {
        // If we are at the target number of moves, we have "won" if and only if
        // the current position is a special target.
        return targets.count(pos) ? 1 : 0;
      }

      ll& ways = memo[(pos - 'A')][moves];
      if(~ways) return ways;

      Answer ans = answers.at(pos);
      ll yes = count_ways({ans.yes, moves + 1}, answers, memo);
      ll no = count_ways({ans.no, moves + 1}, answers, memo);
      ways = yes + no;
      return ways;
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
        
        while(while_read(n)) {
          targets.clear();
          char pos, yes, no, is_target;
          map answers;
          for(int i = 0; i < n; ++i) {
            while_read(pos, no, yes, is_target);
            answers[pos] = {yes, no};
            if(is_target == 'x') targets.insert(pos);
          }
          while_read(threshold);
          std::vector<std::vector<ll>> memo(n + 1, std::vector<ll>(threshold + 1, -1));
          std::cout << count_ways({'A', 0}, answers, memo) << std::endl;         
        }  
    }
}