/*
───────────────────────────────────────────────────────────────
🧳 UVa 10525 New to Bangladesh?, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


constexpr int inf = 1e5;

struct Route
{
    int dist;
    int time;
    bool operator < (const Route& other) const { return time < other.time || (time == other.time && dist < other.dist); }
    bool operator == (const Route& other) const { return dist == other.dist && time == other.time; }
    bool operator != (const Route& other) const { return !(*this == other); }
    Route operator + (const Route& other) const { return {dist + other.dist, time + other.time}; }
};


using v_route = std::vector<Route>;
using vv_route = std::vector<v_route>;


namespace algorithms::onlinejudge::graph::Bangladesh
{
    /** https://onlinejudge.org/external/105/10525.pdf */
    int t_cases, places_n, roads_n;
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
          while_read(places_n, roads_n);
          vv_route routes(places_n, v_route(places_n, {inf, inf}));
          for(int place_id = 0; place_id < places_n; ++place_id) {
            routes[place_id][place_id] = {0, 0};
          }

          for(int road_id = 0; road_id < roads_n; ++road_id) {
            int from, to, length, time;
            while_read(from, to, time, length);
            --from; --to;
            routes[from][to] = std::min(routes[from][to], {length, time});
            routes[to][from] = routes[from][to];
          }

          for(int k = 0; k < places_n; ++k) {
            for(int i = 0; i < places_n; ++i) {
              for(int j = 0; j < places_n; ++j) {
                auto& d_ij = routes[i][j];
                auto d_ik = routes[i][k];
                auto d_kj = routes[k][j];
                if(d_ik.dist == inf || d_kj.dist == inf) continue;
                d_ij = std::min(d_ij, d_ik + d_kj);
              }
            }
          }

          int queries;
          while_read(queries);
          while(queries--) {
            int start, end;
            while_read(start, end);
            --start; --end;
            auto r = routes[start][end];
            if(r.dist != inf)
              printf("Distance and time to reach destination is %d & %d.\n", r.dist, r.time);
            else printf("No Path.\n");
          }
          if(t_cases) printf("\n");
        }
    }
}