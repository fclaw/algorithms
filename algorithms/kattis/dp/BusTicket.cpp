/*
───────────────────────────────────────────────────────────────
🧳 Bus Ticket, https://open.kattis.com/problems/busticket, rt: s
───────────────────────────────────────────────────────────────
*/


#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using ll = long long;
using vll = std::vector<ll>;


namespace algorithms::kattis::dp::bus_ticket
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

        int single_trip_cost;
        int period_ticket_cost;
        int period_coverage;
        int trips_n;
        while(while_read(
          single_trip_cost, 
          period_ticket_cost, 
          period_coverage, 
          trips_n)) {
          vi trips(trips_n);
          for(int i = 0; i < trips_n; ++i) {
            std::cin >> trips[i];
          }
          
          vll dp(trips_n + 1, INT64_MAX);
          dp[0] = 0;
          for(int i = 0; i < trips_n; ++i) {
            if(dp[i] != INT64_MAX) {
              dp[i + 1] = std::min(dp[i + 1], single_trip_cost + dp[i]);
              int j = find_next_trip_pos(trips, i, period_coverage);
              dp[j] = std::min(dp[j], period_ticket_cost + dp[i]);            
            }
          }

          std::cout << dp[trips_n] << std::endl;
        }
    }
}