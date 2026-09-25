/*
───────────────────────────────────────────────────────────────
🧳 UVa 1231 ACORN, https://onlinejudge.org/external/12/1231.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;


struct Tree
{
    int idx;
    vi acorns;

};



int cache[2001][2001];

int dp(int idx, int height, const std::vector<Tree>& trees, int flight_drop) {

  if(height == 0) {
    return (cache[idx][height] = 0);
  }

  if(~cache[idx][height]) {
    return cache[idx][height];
  }

  int climb_down = trees[idx].acorns[height - 1] + dp(idx, height - 1, trees, flight_drop);
  int fly_over = 0;
  for(const Tree& t : trees) {
    if(t.idx != idx && 
       height > flight_drop) {
      fly_over = std::max(fly_over, trees[t.idx].acorns[height - flight_drop] + dp(t.idx, height - flight_drop, trees, flight_drop));
    }
  }

  return (cache[idx][height] = std::max(climb_down, fly_over));
}


// When the size of naive DP states are too large that causes the overall DP time complexity
// to be not-doable, think of another more efficient (but usually not obvious) way to represent
// the possible states. Using a good state representation is a potential major speed up for a
// DP solution. Remember that no programming contest problem is unsolvable, the problem
// author must have known a trick!!!
int get_maximum_acorns(const std::vector<Tree>& trees, int height, int flight_drop) {
  int max_acorns = 0;
  std::memset(cache, -1, sizeof cache);
  for(const Tree& t : trees) {
    max_acorns = std::max(max_acorns, dp(t.idx, height, trees, flight_drop));
  }
  return max_acorns;
}

namespace algorithms::onlinejudge::advanced_topics::ACORN
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

        int t_cases, terminus;
        std::cin >> t_cases;
        while(t_cases--) {
          int trees_n, height, flight_drop;
          while_read(trees_n, height, flight_drop);
          std::vector<Tree> tress(trees_n);
          for(int t = 0; t < trees_n; ++t) {
            int acorns_n, h;
            Tree tree;
            tree.idx = t;
            tree.acorns = vi(height + 1);
            std::cin >> acorns_n;
            for(int a = 0; a < acorns_n; ++a) {
              std::cin >> h;
              tree.acorns[h]++;
            }
            tress[t] = tree;
          }
          printf("%d\n", get_maximum_acorns(tress, height, flight_drop));
        }
        std::cin >> terminus;
    }
}