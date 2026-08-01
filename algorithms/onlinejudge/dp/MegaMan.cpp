/*
────────────────────────────────────────────────────────────────────────────────
🧳 UVa 11795 - Mega Mans Missions
   URL: https://onlinejudge.org/external/117/11795.pdf
   Verdict: Accepted | Runtime: ~ 0.020s
───────────────────────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>; 
using ll = long long;


int ALL_ROBOTS;
int V;

int find_first_zero_idx(int mask) {
  int idx = 0;
  while (mask & (1 << idx)) { // Loop while bit 'idx' is 1
    idx++;
  }
  return idx; // Returns the index of the first 0 bit
}

bool can_be_defeated(int u, int robots, const vvi& weapons_graph) {
  int mask = robots;
  while(mask < ALL_ROBOTS) {
    int idx = find_first_zero_idx(mask);
    if(weapons_graph[idx][u]) {
      return true;
    }
    mask |= (1 << idx);
  }
  return false;
}


ll cache[1 << 17];


ll count_ways_to_defeat_all_robots(const vvi& weapons_graph, int robots) {

  if(robots == 0) {
    return (cache[robots] = 1LL);
  }

  if(~cache[robots]) {
    return cache[robots];
  }

  ll ways = 0LL;
  // direct attack by Buster if Buster can defeat a robot
  for (int v = 1; v <= V; ++v) {
    int bit = (1 << v);
    if((robots & bit) && can_be_defeated(v, robots, weapons_graph)) {
      ways += count_ways_to_defeat_all_robots(weapons_graph, robots & ~bit);
    }
  }

  return (cache[robots] = ways);
}




namespace algorithms::onlinejudge::dp::mega_man
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
        std::cin >> t_cases;
        while(t_cases--) {
          std::string in;
          std::cin >> V;
          vvi weapons_graph(V + 1, vi(V + 1));
          for (int i = 0; i <= V; ++i) {
            std::string line;
            std::cin >> line; // Reads the single N-character string for row i
            for(int j = 1; j <= V; ++j) {
              if (line[j - 1] == '1') {
                weapons_graph[i][j] = 1; // Robot j is 0-indexed (0 to N)
              } else {
               weapons_graph[i][j] = 0;
              }
            }
          }
          ALL_ROBOTS = (1 << (V + 1)) - 1;
          std::memset(cache, -1, sizeof cache);
          printf("Case %d: %lld\n", t_case++, count_ways_to_defeat_all_robots(weapons_graph, ALL_ROBOTS & ~(1 << 0)));
        }
    }
}