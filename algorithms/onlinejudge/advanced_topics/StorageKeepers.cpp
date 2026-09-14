/*
───────────────────────────────────────────────────────────────
🧳 10163 Storage Keepers, https://onlinejudge.org/external/101/10163.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * 🧠 THE TWO-PHASE ARCHITECTURE: Capacity Capping via L_max (UVa 10163)
 * ============================================================================
 * 
 * 1. THE CAPACITY CAP INSIGHT (L defines the Workload Limit):
 * -----------------------------------------------------------
 * According to Rule 3, if keeper 'i' with ability P_i watches K_i storages,
 * each storage has a safety rating:
 * 
 *         U_j = floor(P_i / K_i)
 * 
 * To maintain a minimum safe line L across all storages (U_j >= L):
 * 
 *         floor(P_i / K_i) >= L   <===>   K_i <= floor(P_i / L)
 * 
 * 💡 The safe line L acts as an INVERSE CAPACITY CAP!
 * For any given L, keeper 'i' can guard AT MOST:
 * 
 *         s_upper_bound = floor(P_i / L)  storages.
 * 
 * 2. PHASE 1: Maximizing the Safe Line (L_max)
 * --------------------------------------------
 * A safe line L is achievable if and only if the sum of maximum allowable 
 * capacities across all M keepers can cover all N storages:
 * 
 *         Total Capacity = Σ floor(P_i / L) >= N
 * 
 * Since total capacity is monotonically non-increasing with respect to L, 
 * we scan downwards from max(P_i) to 1 to find the absolute highest L_max!
 * 
 * 3. PHASE 2: Minimizing the Paycheck (Bounded Knapsack DP)
 * ---------------------------------------------------------
 * Once L_max is locked in, keeper 'i' can be assigned any integer number 
 * of storages:
 * 
 *         s ∈ [0, floor(P_i / L_max)]
 * 
 * Wage Rule: 
 *   - If s == 0 : Keeper is not hired   ===> Cost = 0
 *   - If s >  0 : Keeper is hired       ===> Cost = P_i (Fixed wage!)
 * 
 * State: dp(i, storages_used)
 *   Finds the cheapest subset of keepers that assigns EXACTLY N storages 
 *   while respecting each keeper's individual capacity cap.
 * 
 * 4. EDGE CASE (L_max = 0):
 * -------------------------
 * If even L = 1 cannot cover N storages, no safe line can be established.
 * The company hires nobody, yielding: L = 0, Cost = 0.
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;


constexpr int INF = (int)1e9;
constexpr int MAX_STORAGES = 100;
constexpr int MAX_KEEPERS = 100;

int cache[MAX_KEEPERS + 1][MAX_STORAGES + 1];

int dp(int i, int storages_used_so_far, int total_storages, const vi& job_seekers_abilities, int max_safe_line) {

  if(i == (int)job_seekers_abilities.size()) {
    if(storages_used_so_far == total_storages) {
      return (cache[i][storages_used_so_far] = 0);
    }
    return (cache[i][storages_used_so_far] = INF);
  }

  if(~cache[i][storages_used_so_far]) {
    return cache[i][storages_used_so_far];
  }

  int best = INF;
  int s_upper_bound = job_seekers_abilities[i] / max_safe_line;
  for(int s = 0; s <= s_upper_bound; ++s) {
    int p = s > 0 ? job_seekers_abilities[i] : 0;
     best = std::min(best,  p + dp(i + 1, storages_used_so_far + s, total_storages, job_seekers_abilities, max_safe_line));
  }

  return (cache[i][storages_used_so_far] = best);
}


std::pair<int, int> get_max_safe_line(int storages, const vi& job_seekers_abilities) {

  int safe_line_upper_bound = *std::max_element(job_seekers_abilities.begin(), job_seekers_abilities.end());
  int max_safe_line = safe_line_upper_bound;
  for(int l = safe_line_upper_bound; l >= 1; --l) {
    int total_storages = 0;
    for(int i = 0; i < (int)job_seekers_abilities.size(); ++i) {
      int storages_n = job_seekers_abilities[i] / l;
      total_storages += storages_n;
    }
    if(total_storages >= storages) {
      max_safe_line = l;
      break;
    }
  }

  int min_paycheck = dp(0, 0, storages, job_seekers_abilities, max_safe_line);
  if(min_paycheck == INF) {
    max_safe_line = 0;
    min_paycheck = 0;
  }
  return {max_safe_line, min_paycheck};
}


namespace algorithms::onlinejudge::advanced_topics::storage_keepers
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

        
        int storages_n, job_seekers_m;
        while(while_read(storages_n, job_seekers_m) && 
              (storages_n && job_seekers_m)) {
          vi job_seekers_abilities(job_seekers_m);
          for(int i = 0; i < job_seekers_m; ++i) {
            std::cin >> job_seekers_abilities[i];
          }
          std::memset(cache, -1, sizeof cache);
          std::pair<int, int> ans = get_max_safe_line(storages_n, job_seekers_abilities);
          printf("%d %d\n", ans.first, ans.second);
        }
    }
}
