/*
───────────────────────────────────────────────────────────────
🧳 UVa 672 Gangsters, https://onlinejudge.org/external/6/672.pdf, rt: s
───────────────────────────────────────────────────────────────
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


int get_max_total_prosperity(int i, int time_so_far, int curr_openness, const std::vector<Gangster>& mobsters, vvvi& cache) {

  if(i == (int)mobsters.size()) {
    return (cache[i][curr_openness][time_so_far] = 0);
  } 

  if(~cache[i][curr_openness][time_so_far]) {
    return cache[i][curr_openness][time_so_far];
  }

  int curr_prosperity = 0;
  int next_i = i;
  if(mobsters[i].arrival_time == time_so_far) {
    auto res = get_accumulated_prosperity(i, curr_openness, mobsters);
    curr_prosperity = res.second;
    next_i = res.first;
  }

  int best = 0;
  if(time_so_far <= T) {
    best = std::max(best, curr_prosperity + get_max_total_prosperity(next_i, time_so_far + 1, curr_openness, mobsters, cache));
    if(curr_openness >= 1) {
      best = std::max(best, curr_prosperity + get_max_total_prosperity(next_i, time_so_far + 1, curr_openness - 1, mobsters, cache));
    }
    if(curr_openness <= K) {
       best = std::max(best, curr_prosperity + get_max_total_prosperity(next_i, time_so_far + 1, curr_openness + 1, mobsters, cache));
    }
  }

  return (cache[i][curr_openness][time_so_far] = best);

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
        while(t_cases--) {
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
          vvvi cache(N + 1, vvi(K + 10, vi(T + 10, -1)));
          printf("%d\n\n", get_max_total_prosperity(0, 0, 0, mobsters, cache));
        }
    }
}
