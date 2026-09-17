/*
───────────────────────────────────────────────────────────────
🧳 UVa 12563 Jin Ge Jin Qu hao, https://onlinejudge.org/external/125/12563.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;

constexpr int JinGeJinQu_BONUS = 678;
constexpr int MAX_TOTAL_TIME = 9000;

struct State
{
    int time;
    int candidates;

    bool operator < (const State& s) const {
      return (candidates < s.candidates) || 
             (candidates == s.candidates && time < s.time);
    }
};


State dp(int i, int time_left, const vi& song_lengths, std::vector<std::vector<State>>& cache) {
  
    if(i == (int)song_lengths.size()) {
      return (cache[i][time_left] = {0, 0});
    }

    if(~cache[i][time_left].time) {
      return cache[i][time_left];
    }

    State best = {0, 0};
    if(time_left > song_lengths[i]) {
      best = dp(i + 1, time_left - song_lengths[i], song_lengths, cache);
      best.time += song_lengths[i];
      best.candidates++;
    }

    best = std::max(best, dp(i + 1, time_left, song_lengths, cache));
    return (cache[i][time_left] = best);
}

std::pair<int, int> get_maximal_number_of_songs(const vi& song_lengths, int time_left) {

  std::vector<std::vector<State>> cache(song_lengths.size() + 1, std::vector<State>(time_left + 1, {-1, 0}));
  State ans = dp(0, time_left, song_lengths, cache);

  // Final Answer (including Jin Ge Jin Qu):
  int final_songs = ans.candidates + 1;
  int final_time  = ans.time + JinGeJinQu_BONUS;

  return {final_songs, final_time};
}

namespace algorithms::onlinejudge::advanced_topics::JinGeJinQu
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
          int n, time_left;
          std::cin >> n >> time_left;
          vi song_lengths(n);
          for(int i = 0; i < n; ++i) {
            std::cin >> song_lengths[i];
          }
          std::pair<int, int> ans = get_maximal_number_of_songs(song_lengths, time_left);
          printf("Case %d: %d %d\n", t_case++, ans.first, ans.second);
        }
    }
}