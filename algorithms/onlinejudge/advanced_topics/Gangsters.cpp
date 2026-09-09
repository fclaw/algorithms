/*
───────────────────────────────────────────────────────────────
🧳 UVa 672 Gangsters, https://onlinejudge.org/external/6/672.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * 🧠 ARCHITECTURAL INSIGHT: The Reachability Cone & The "Unused T" Paradox
 * ============================================================================
 * 
 * 1. THE REACHABILITY CONE (Your Notepad Derivation):
 * ---------------------------------------------------
 * In Δt = (T_next - T_curr) seconds, the door speed limit is 1 unit/second.
 * Starting from openness S_curr, the door can physically reach any width in:
 * 
 *     min_openness = max(0, S_curr - Δt)
 *     max_openness = min(K, S_curr + Δt)
 * 
 * A future gangster with stoutness S_next is reachable IF AND ONLY IF:
 *     S_next ∈ [min_openness, max_openness]  <===>  |S_next - S_curr| <= Δt
 * 
 * 2. WHY PARAMETER 'T' (Closing Time) IS COMPLETELY REDUNDANT:
 * ------------------------------------------------------------
 * • By problem definition, all gangsters arrive before closing time (T_i <= T).
 * • There is NO requirement to return the door to state 0 when the restaurant closes.
 * • Once the last admitted gangster walks in, all profit has been gathered. 
 *   Anything that happens between the last gangster's arrival and T is irrelevant!
 * 
 * • Parameter T exists only for the naive O(T * K) second-by-second DP table.
 *   In our optimal O(N^2) event-based jump model, T is safely discarded!
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


struct Gangster
{
    /**
     * 1. arrival_time (T_i)
     * ---------------------
     * The exact second (0 <= T_i <= T) when the gangster arrives at the restaurant.
     * Primary sorting key for DP: Gangsters must be processed chronologically!
     */
    int arrival_time;

    /**
     * 2. prosperity (P_i)
     * -------------------
     * The amount of money/value this gangster brings into the restaurant (0 <= P_i <= 300).
     * This is the objective value we want to maximize.
     */
    int prosperity;

    /**
     * 3. stoutness (S_i)
     * ------------------
     * The body width / required door openness (1 <= S_i <= K).
     * Rule: The door's openness must be EXACTLY equal to S_i at arrival_time T_i!
     */
    int stoutness;

    /**
     * Chronological Sort Comparator:
     * ------------------------------
     * Sorts gangsters by arrival_time ascending so the DP can process them in order.
     */
    bool operator < (const Gangster& other) const {
      if(arrival_time != other.arrival_time) {
        return arrival_time < other.arrival_time;
      }
      return stoutness < other.stoutness;
    }
};


void print_gangsters(const std::vector<Gangster>& gangsters) {
    std::cerr << "===================== GANGSTER ROSTER (" << gangsters.size() << ") =====================\n";
    std::cerr << "  #  | Arrival Time (T) | Stoutness / Width (S) | Prosperity ($)\n";
    std::cerr << "---------------------------------------------------------------\n";
    for (size_t i = 0; i < gangsters.size(); ++i) {
        std::fprintf(stderr, "  %-2zu | %16d | %21d | $%12d\n",
                     i + 1, 
                     gangsters[i].arrival_time, 
                     gangsters[i].stoutness, 
                     gangsters[i].prosperity);
    }
    std::cerr << "===============================================================\n";
}

int K, T;

std::pair<int, int> get_accumulated_prosperity(int i, int curr_openness, const std::vector<Gangster>& mobsters) {

  int j = i;
  int at = mobsters[i].arrival_time;
  int S = (int)mobsters.size();
  int accumulated_prosperity = 0;
  while(j < S && at == mobsters[j].arrival_time) {
    int stoutness = mobsters[j].stoutness;
    int prosperity = mobsters[j].prosperity;
    if(stoutness == curr_openness) {
      accumulated_prosperity += prosperity;
    }
    j++;
  }
  return {j, accumulated_prosperity};
}


int get_max_total_prosperity(int i, int curr_openness, const std::vector<Gangster>& mobsters, vvi& cache) {

  // 1. BASE CASE: All gangsters have been processed
  if(i == (int)mobsters.size()) {
    return (cache[i][curr_openness] = 0);
  } 

  // 2. MEMOIZATION CHECK: Using the ~ bitwise trick (~(-1) == 0)
  if(~cache[i][curr_openness]) {
    return cache[i][curr_openness];
  }

  // 3. PHYSICAL REACHABILITY CONE:
  // Calculate time elapsed since the previous event (T[i] - T[i - 1]).
  // Note: For i = 1, mobsters[0] is our dummy mobster (T=0, S=0).
  int t_diff = mobsters[i].arrival_time - mobsters[i - 1].arrival_time;
  // In t_diff seconds, the door speed limit is 1 unit/second.
  // The door can physically reach any openness in [min_openness, max_openness]:
  int min_openness = std::max(0, curr_openness - t_diff);
  int max_openness = std::min(K, curr_openness + t_diff);
  int best = 0;
  // 4. TRANSITIONS: Try setting the door to every physically achievable width 'o'
  for(int o = min_openness; o <= max_openness; ++o) {
    // Collect all gangsters arriving at T[i] whose stoutness matches 'o'
    // (Simultaneously handles multiple gangsters arriving at the same timestamp!)
    //   - res.second: Total prosperity of all gangsters admitted at width 'o'
    //   - res.first : Index of the first gangster arriving at a future timestamp
    auto res = get_accumulated_prosperity(i, o, mobsters);
    int curr_prosperity = res.second;
    int next_i = res.first;
    best = std::max(best, curr_prosperity + get_max_total_prosperity(next_i, o, mobsters, cache));
  }
  return (cache[i][curr_openness] = best);
}


namespace algorithms::onlinejudge::advanced_topics::gangsters
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

        int t_cases, N;
        std::cin >> t_cases;
        bool is_first = true;
        while(t_cases--) {

          if(!is_first) std::cout << "\n";
          is_first = false;

          std::cin >> N >> K >> T;
          std::vector<Gangster> mobsters(N);
          for(int p = 0; p < 3; ++p) {
            for(int i = 0; i < N; ++i) {
              if(p == 0) {
                std::cin >> mobsters[i].arrival_time;
              } else if (p == 1) {
                std::cin >> mobsters[i].prosperity;
              } else {
                std::cin >> mobsters[i].stoutness;
              }
            }
          }
          std::sort(mobsters.begin(), mobsters.end());
          mobsters.insert(mobsters.begin(), {0, 0, 0}); // dummy mobster
          vvi cache(N + 2, vi(K + 1, -1));
          printf("%d\n", get_max_total_prosperity(1, 0, mobsters, cache));
        }
    }
}
