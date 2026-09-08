/*
───────────────────────────────────────────────────────────────
🧳 UVa 1172 The Bridges of Kölsberg, https://onlinejudge.org/external/11/1172.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

struct State 
{
    int economical_value_of_bridges; // Primary metric to maximize
    int num_of_bridges;              // Secondary metric (tie-breaker)

    /**
     * Strict Weak Ordering (<) for std::max(a, b):
     * --------------------------------------------
     * std::max(a, b) selects 'b' whenever (a < b) evaluates to true:
     * 
     * 1. Primary     : MAXIMIZE economical_value_of_bridges (<)
     * 2. Tie-Breaker : MINIMIZE num_of_bridges (>)
     */
    bool operator < (const State& o) const {
        if (economical_value_of_bridges != o.economical_value_of_bridges) {
            return economical_value_of_bridges < o.economical_value_of_bridges;
        }
        return num_of_bridges > o.num_of_bridges; // Fewer bridges is better!
    }

    /**
     * Equality Operator (==)
     */
    bool operator == (const State& o) const {
      return economical_value_of_bridges == 
             o.economical_value_of_bridges &&
             num_of_bridges == o.num_of_bridges;
    }
};

struct City 
{
    int os_type; // mapped to integer
    int trade_value;
};

// Global or per-testcase City ID Mapper
std::unordered_map<std::string, int> os_to_id;
int unique_os_counter;

int get_id(const std::string& raw_os) {
  auto it = os_to_id.find(raw_os);
  if (it != os_to_id.end()) return it->second;
  os_to_id[raw_os] = unique_os_counter++;
  return os_to_id.at(raw_os);
}

using vv_state = std::vector<std::vector<State>>;


State get_min_bridges(int i, int j, const std::vector<City>& northern_bank, const std::vector<City>& southern_bank, vv_state& cache) {

  int N = (int)northern_bank.size();
  int S = (int)southern_bank.size();
  if(i >= N || j >= S) {
    return (cache[i][j] = {0, 0});
  }

  if(~cache[i][j].economical_value_of_bridges) {
    return cache[i][j];
  }

  State best = {0, INT32_MAX};
  // process northern bank
  // skip 
  State skip_northern_bank = get_min_bridges(i + 1, j, northern_bank, southern_bank, cache);
  best = std::max(best, skip_northern_bank);
  // ==========================================================================
  // 🌉 TAKE OPTION: Match City 'i' with the FIRST Compatible Southern City
  // ==========================================================================
  // We scan the southern bank starting from index 'j' to find the earliest 
  // city 'k' that shares the exact same OS belief (n_city.os_type == s_city.os_type).
  //
  // 💡 WHY THE 'break;' IS MATHEMATICALLY OPTIMAL & PREVENTS TLE:
  // -----------------------------------------------------------
  // 1. Suffix Maximization (Non-Crossing Invariant):
  //    To avoid crossing bridges, any future bridges MUST use northern cities > i 
  //    and southern cities > k.
  //    Choosing the EARLIEST valid southern match 'k' leaves the LARGEST possible 
  //    unclaimed southern suffix [k + 1 ... S - 1] available for future bridges!
  //
  // 2. What if a later city k' > k has a higher trade value?
  //    The DP already explores that scenario independently via the 'skip_southern_bank' 
  //    branch: get_min_bridges(i, j + 1, ...).
  //    Therefore, within this specific branch, testing any match after the first 
  //    is completely redundant!
  //
  // 3. Complexity Reduction (O(N^3) -> O(N^2)):
  //    - Without 'break': Looping through all S cities per state creates an 
  //      O(N * S * S) ≈ 10^9 operations monster ===> Instant TLE!
  //    - With 'break'   : The loop halts immediately upon the first match, 
  //      keeping total operations strictly O(N * S) ≈ 10^6 ===> Accepted in 0.250s!
  // ==========================================================================
  for(int k = j; k < S; ++k) {
    City n_city = northern_bank[i];
    City s_city = southern_bank[k];
    if(n_city.os_type == s_city.os_type) {
      // Build bridge between northern city 'i' and southern city 'k':  
      State curr = get_min_bridges(i + 1, k + 1, northern_bank, southern_bank, cache);
      int combined_trade_val = n_city.trade_value + s_city.trade_value;
      curr.economical_value_of_bridges += combined_trade_val;
      curr.num_of_bridges++;
      // Update best using our custom operator< (Max money, Min bridges on tie)
      best = std::max(best, curr);
      break;  // ⚡ STOP IMMEDIATELY! Earliest match is always optimal.
    }
  }
  
  // process southern bank
  // skip 
  State skip_southern_bank = get_min_bridges(i, j + 1, northern_bank, southern_bank, cache);
  best = std::max(best, skip_southern_bank);
  // take and find first matching on the northern bank;
  for(int k = i; k < N; ++k) {
    City n_city = northern_bank[k];
    City s_city = southern_bank[j];
    if(n_city.os_type == s_city.os_type) {
      State curr = get_min_bridges(k + 1, j + 1, northern_bank, southern_bank, cache);
      int combined_trade_val = n_city.trade_value + s_city.trade_value;
      curr.economical_value_of_bridges += combined_trade_val;
      curr.num_of_bridges++;
      best = std::max(best, curr);
      break; // ⚡ STOP IMMEDIATELY! Earliest match is always optimal.
    }
  }

  return (cache[i][j] = best);
}

namespace algorithms::onlinejudge::advanced_topics::bridges_of_Kölsberg
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

        unique_os_counter = 0;

        int t_cases, N, S, trade_val;
        std::string name, os;
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> N;
          std::vector<City> northern_bank(N);
          for(int i = 0; i < N; ++i) {
            std::cin >> name >> os >> trade_val;
            int os_id = get_id(os);
            northern_bank[i] = {os_id, trade_val};
          }
          std::cin >> S;
          std::vector<City> southern_bank(S);
          for(int i = 0; i < S; ++i) {
            std::cin >> name >> os >> trade_val;
            int os_id = get_id(os);
            southern_bank[i] = {os_id, trade_val};
          }
          vv_state cache(N + 1, std::vector<State>(S + 1, {-1, -1}));
          State ans = get_min_bridges(0, 0, northern_bank, southern_bank, cache);
          printf("%d %d\n", ans.economical_value_of_bridges, ans.num_of_bridges);
        }
    }
}
