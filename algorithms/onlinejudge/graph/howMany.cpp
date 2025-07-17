/*
───────────────────────────────────────────────────────────────
🧳 UVa  986 How Many?, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <tuple>



enum Move { Up, Down };

using mii = std::tuple<Move, int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ll = long long;
using map = std::unordered_map<uint64_t, int>;


struct State
{
    int y;
    int x;
    Move move;
    int peaks_left;
};


// Define the bit layout
// | unused (47 bits) | x (6 bits) | y (5 bits) | move (1 bit) | peaks (5 bits) |
const int PEAKS_BITS = 5;
const int MOVE_BITS = 1;
const int Y_BITS = 5;
const int X_BITS = 6;

const int MOVE_SHIFT = PEAKS_BITS;
const int Y_SHIFT = MOVE_SHIFT + MOVE_BITS;
const int X_SHIFT = Y_SHIFT + Y_BITS;

// Helper function to pack a State into a uint64_t
uint64_t pack_state(const State& s) {
    uint64_t key = 0;
    key |= static_cast<uint64_t>(s.peaks_left);
    key |= (static_cast<uint64_t>(s.move) << MOVE_SHIFT);
    key |= (static_cast<uint64_t>(s.y) << Y_SHIFT);
    key |= (static_cast<uint64_t>(s.x) << X_SHIFT);
    return key;
}

// Helper function to unpack a uint64_t back into a State
State unpack_state(uint64_t key) {
    State s;
    s.peaks_left = key & ((1 << PEAKS_BITS) - 1);
    s.move = static_cast<Move>((key >> MOVE_SHIFT) & ((1 << MOVE_BITS) - 1));
    s.y = (key >> Y_SHIFT) & ((1 << Y_BITS) - 1);
    s.x = (key >> X_SHIFT) & ((1 << X_BITS) - 1);
    return s;
}

// For 2-directional movement ( north-east, south-east )
const std::vector<mii> dirs_2 = { {Up, 1, 1}, {Down, -1, 1} };


namespace algorithms::onlinejudge::graph::how_many
{
    /** https://onlinejudge.org/external/9/986.pdf */
    int n, r, k;
    bool in_bounds(int y, int x) { return y >= 0 && y <= n && x <= 2 * n; }
    ll count_ways(State s, map& memo) {

      int y = s.y;
      int x = s.x;
      Move move = s.move;
      int peaks_left = s.peaks_left;

      if(peaks_left < 0) return 0;

      if(y == 0 &&
         x == 2 * n) {    
        return peaks_left == 0 ? 1 : 0;
      }
       
      uint64_t key = pack_state(s);
      if(memo.count(key)) {
        return memo[key];
      }
      
      ll ways = 0;
      for(const auto& d : dirs_2) {
        Move nm = std::get<0>(d);
        int ny = y + std::get<1>(d);
        int nx = x + std::get<2>(d);
        if(in_bounds(ny, nx)) {
          State ns = {ny, nx, nm, peaks_left};   
          if(move == Up && nm == Down && y == k) {
            --ns.peaks_left;
          }
          ways += count_ways(ns, memo);
        }
      }
      return memo[key] = ways;
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
        
        while(while_read(n, r, k)) {
          map memo;
          State init = {0, 0, Up, r};
          std::cout << count_ways(init, memo) << std::endl;
        }
    }
}