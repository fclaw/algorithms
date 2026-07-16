/*
───────────────────────────────────────────────────────────────
🧳 UVa 12324 Philip J. Fry Problem, https://onlinejudge.org/external/123/12324.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



struct TripLeg
{
    int time;
    int feces;
};


using v_trip_legs = std::vector<TripLeg>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;


int cache[101][10001];


int calculate_min_time(const v_trip_legs& legs, int leg_idx, int feces_left) {

   if(feces_left < 0) {
    return INT32_MAX;
   }

   if(leg_idx == (int)legs.size()) {
      return (cache[leg_idx][feces_left] = 0);
   }

   if(~cache[leg_idx][feces_left]) {
    return cache[leg_idx][feces_left];
   }

   int leg_time = legs[leg_idx].time;
   int leg_feces = legs[leg_idx].feces;
   int min_time = INT32_MAX;
   if(feces_left > 0) {
     int skip = leg_time + calculate_min_time(legs, leg_idx + 1, leg_feces + feces_left);
     int take = leg_time / 2 + calculate_min_time(legs, leg_idx + 1, leg_feces + feces_left - 1);
     min_time = std::min(min_time, std::min(skip, take));
   } else {
      int skip = leg_time + calculate_min_time(legs, leg_idx + 1, leg_feces + feces_left);
      min_time = std::min(min_time, skip);
   }
   return (cache[leg_idx][feces_left] = min_time);
}



namespace algorithms::onlinejudge::dp::Philip_Fry_problem
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

        int n_legs;
        while(std::cin >> n_legs && n_legs) {
          int total_feces = 0;
          v_trip_legs legs(n_legs);
          for(int i = 0; i < n_legs; ++i) {
            TripLeg leg;
            std::cin >> leg.time >> leg.feces;
            legs[i] = leg;
            total_feces += leg.feces;
          }

        //   std::memset(cache, -1, sizeof cache);
        //   std::cout << calculate_min_time(legs, 0, 0) << std::endl;

          
          vvi dp(n_legs + 1, vi(total_feces + 1, INT32_MAX));
          
          // Base Case: 0 legs completed, 0 feces accumulated, 0 time taken
          dp[0][0] = 0;

          for (int i = 0; i < n_legs; ++i) {
            int leg_time = legs[i].time;
            int leg_feces = legs[i].feces;

            for (int j = 0; j <= total_feces; ++j) {
              // If this state is unreachable, skip it
              if (dp[i][j] == INT32_MAX) continue;

              // Option 1: Skip cleanup on leg i
              int next_feces_skip = j + leg_feces;
              if (next_feces_skip <= total_feces) {
                int skip = dp[i + 1][next_feces_skip];
                dp[i + 1][next_feces_skip] = std::min(skip, dp[i][j] + leg_time);
              }

              // Option 2: Clean up (Take) on leg i (only valid if we had feces left, i.e., j > 0)
              if (j > 0) {
                int next_feces_take = j + leg_feces - 1;
                if (next_feces_take <= total_feces) {
                  int take = dp[i + 1][next_feces_take];
                  dp[i + 1][next_feces_take] = std::min(take, dp[i][j] + (leg_time / 2));
                }
              }
            }
          }
  
          // The answer is the minimum time to complete all n_legs, regardless of ending feces count
          int min_time = INT32_MAX;
          for(int j = 0; j <= total_feces; ++j) {
            min_time = std::min(min_time, dp[n_legs][j]);
          }

          std::cout << min_time << std::endl;
        }
    }
}