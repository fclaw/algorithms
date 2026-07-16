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
          v_trip_legs legs(n_legs);
          for(int i = 0; i < n_legs; ++i) {
            TripLeg leg;
            std::cin >> leg.time >> leg.feces;
            legs[i] = leg;
          }

          std::memset(cache, -1, sizeof cache);
          std::cout << calculate_min_time(legs, 0, 0) << std::endl;
        }
    }
}