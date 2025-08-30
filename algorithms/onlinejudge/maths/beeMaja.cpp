/*
───────────────────────────────────────────────────────────────
🧳 UVa 10182 Bee Maja, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ii = std::pair<int, int>;


ii get_start_comb(int curr, int target, int ring) {
  int next = curr + 6 * ring;
  if(next > target)
    return {curr, ring};
  return get_start_comb(next, target, ring + 1);
}

std::vector<ii> directions = {
  {-1, 0}, // left
  {0, -1}, // down
  {1, -1}, // down-right
  {1, 0},  // right
  {0, 1},  // up
  {-1, 1}  // up-left
};


ii get_coords(int comb, int ring, int target_comb) {
  ii start = {ring - 1, 1};
  if(comb == target_comb) return start;

  for(int i = 0; i < ring - 1; ++i) {
    int dir_x = directions[5].first;
    int dir_y = directions[5].second;
    start.first += dir_x;
    start.second += dir_y;
    comb += 1;
    if(comb == target_comb) 
      return start;
  }

  for(int i = 0; i < (int)directions.size() - 1; ++i) {
    int dir_x = directions[i].first;
    int dir_y = directions[i].second;
    for(int step = 0; step < ring; ++step) {
      start.first += dir_x;
      start.second += dir_y;
      comb += 1;
      if(comb == target_comb)
        return start;
    }
  }
  return {0, 0};
}



namespace algorithms::onlinejudge::maths::bee_Maja
{
    /** https://onlinejudge.org/external/101/10182.pdf */
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
         
        int comb;
        while(scanf("%d", &comb) == 1) {
          ii pos = get_start_comb(2, comb, 1);
          ii coords = get_coords(pos.first, pos.second, comb);
          printf("%d %d\n", coords.first, coords.second);
        }
    }
}