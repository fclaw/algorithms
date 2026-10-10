/*
───────────────────────────────────────────────────────────────
🧳 UVa 12030 Help the Winners, https://onlinejudge.org/external/120/12030.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum Status {
  INCOMPLETE  = 0,  // Tainted by at least one '0', and NO '2' yet (Needs a 2 to win!)
  FULL_MATCH  = 1, // All pairs so far are '1' (Clean: no 0, no 2)
  HAS_SUPER   = 2, // At least one '2' picked (Victory already guaranteed!)
  NONE        = 3
};

Status update_status(int cell, Status s) {

  // If we already have a super-match, we NEVER lose it!
  if (s == HAS_SUPER) {
    return s;
  }

  if(s == INCOMPLETE) {
    if(cell == 0 || 
       cell == 1) {
      return INCOMPLETE;
    } else {
      return HAS_SUPER;
    }
  }

  if(s == FULL_MATCH) {
    if(cell == 0) {
      return INCOMPLETE;
    } else if(cell == 1) {
      return s;
    } else {
      return HAS_SUPER;
    }
  }

  return static_cast<Status>(cell);
}


ll cache[1 << 15][4];


ll dp(int id, int mask, Status s, const vvi& matching_map, int N) {
  if(__builtin_popcount(mask) == N) {
    // Invalid (Had a 0 and never found a 2!)
    if(s == INCOMPLETE) {
      return (cache[mask][s] = 0LL);
    }
    return (cache[mask][s] = 1LL);
  }

  if(~cache[mask][s]) {
    return cache[mask][s];
  }

  ll ways = 0LL;
  for(int j = 0; j < N; ++j) {
    int bit = 1 << j;
    if(!(mask & bit)) {
      int m = matching_map[id][j];
      Status ns = update_status(m, s);
      ways += dp(id + 1, mask | bit, ns, matching_map, N);
    }
  }
  return (cache[mask][s] = ways);
}


ll get_ways_to_form_pairs(const vvi& matching_map, int N) {
  std::memset(cache, -1LL, sizeof cache);
  return dp(0, 0, NONE, matching_map, N);
}


namespace algorithms::onlinejudge::advanced_topics::help_the_winners
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
        stdin_read(t_cases);
        while(t_cases--) {
          int n_pairs;
          stdin_read(n_pairs);
          vvi matching_map(n_pairs, vi(n_pairs));
          for(int i = 0; i < n_pairs; ++i) {
            for(int j = 0; j < n_pairs; ++j) {
              stdin_read(matching_map[i][j]);
            }
          }
          printf("Case %d: %llu\n", t_case++, get_ways_to_form_pairs(matching_map, n_pairs));
        }
    }
}