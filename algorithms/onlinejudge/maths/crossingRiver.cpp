/*
───────────────────────────────────────────────────────────────
🧳 UVa 10773 Back to Intermediate Math, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



namespace algorithms::onlinejudge::maths::crossing_river
{
    /** https://onlinejudge.org/external/107/10773.pdf */
    int t_cases, t_case = 1;
    double river_width, river_vel, boat_vel;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while_read(t_cases);
        while(t_cases--) {
          while_read(river_width, river_vel, boat_vel);
          if(boat_vel <= river_vel || (river_width == 0 && river_vel == 0)) {
            printf("Case %d: can't determine\n", t_case++);
            continue;
          }
          // shortest path: boat speed must be greater then that of the river
          double shortest_path_speed = std::sqrt(boat_vel * boat_vel - river_vel * river_vel);
          double shortest_path_tm = river_width / shortest_path_speed;
          double fastest_path_tm = river_width / boat_vel;
          double diff = shortest_path_tm - fastest_path_tm;
          if(river_width > 0 && 
             shortest_path_tm == 
             fastest_path_tm) 
           printf("Case %d: can't determine\n", t_case++);
          else printf("Case %d: %.3f\n", t_case++, diff);
        }
    }
}