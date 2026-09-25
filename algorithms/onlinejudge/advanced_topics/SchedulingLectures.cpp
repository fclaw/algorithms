/*
───────────────────────────────────────────────────────────────
🧳 UVa 607 Scheduling Lectures, https://onlinejudge.org/external/6/607.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int INF = (int)1e9;

using vi = std::vector<int>;


/**
 * Represents the dual-objective outcome of a lecture schedule.
 *
 * In UVa 607, optimization is strictly lexicographical:
 *   1. Primary Goal:   Minimize total number of lectures.
 *   2. Secondary Goal: Minimize total Dissatisfaction Index (DI) to break ties.
 */
struct Schedule
{
    // Primary Objective: Total number of lectures used to cover the topics
    int lectures;

    // Secondary Objective (Tie-Breaker): Total accumulated dissatisfaction index (DI)
    int dissatisfaction_index;

    /**
     * Lexicographical comparator:
     * - A schedule with fewer lectures is ALWAYS strictly preferred.
     * - If lecture counts are tied, the schedule with smaller dissatisfaction wins.
     *
     * Overloading operator< allows direct usage of std::min(best_schedule, candidate_schedule)!
     */
    bool operator < (const Schedule& o) const {
        if (lectures != o.lectures) {
            return lectures < o.lectures;
        }
        return dissatisfaction_index < o.dissatisfaction_index;
    }
};


int calc_di(int time_left, int C) {
  if(time_left >= 1 && 
     time_left <= 10) {
    return -C;
  } else if (time_left > 10) {
    return (time_left - 10) * (time_left - 10);;
  } else {
    return 0;
  }
}


Schedule dp(int idx, const vi& topics, int max_lecture_length, const vi& prefix_sum, int C, std::vector<Schedule>& cache) {

  if(idx == (int)topics.size()) {
    return (cache[idx] = {0, 0});
  }

  if(~cache[idx].lectures) {
    return cache[idx];
  }

  Schedule best = {INF, INF};
  for(int i = idx; i < (int)topics.size(); ++i) {
    Schedule base = dp(i + 1, topics, max_lecture_length, prefix_sum, C, cache);
    int lec_length = prefix_sum[i + 1] - prefix_sum[idx];
    if(lec_length <= max_lecture_length) {
      int tl =  max_lecture_length - lec_length;
      base.dissatisfaction_index += calc_di(tl, C);
      base.lectures++;
      best = std::min(best, base);
    }
  }

  return (cache[idx] = best);
}


namespace algorithms::onlinejudge::advanced_topics::scheduling_lectures
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

        int topics_n, t_case = 1;
        bool is_first_case = true;
        while(std::cin >> topics_n && 
              topics_n) {
         
          if(is_first_case) {
            is_first_case = false;
          } else {
            std::cout << "\n";
          }

          int max_lecture_length, C;
          std::cin >> max_lecture_length >> C;
          vi topics(topics_n);
          for(int i = 0; i < topics_n; ++i) {
            std::cin >> topics[i]; 
          }
          vi prefix_sum(topics_n + 2, 0);
          prefix_sum[1] = topics.front();
          for(int i = 2; i <= topics_n; ++i) {
            prefix_sum[i] = topics[i - 1] + prefix_sum[i - 1];
          }
          std::vector<Schedule> cache(topics_n + 5, {-1, -1});
          Schedule ans = dp(0, topics, max_lecture_length, prefix_sum, C, cache);
          printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n", t_case++, ans.lectures, ans.dissatisfaction_index);
        }
    }
}