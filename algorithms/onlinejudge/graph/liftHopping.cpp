/*
───────────────────────────────────────────────────────────────
🧳 UVa  10801 Lift Hopping, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cctype>
#include <utility>
#include <functional>
#include <set>
#include <sstream>
#include <cmath>




using vi = std::vector<int>;
using vvi = std::vector<vi>;

// The State struct represents a node in a State-Space Graph, containing attributes such as 
// travel_tm (edge weight), floor, and lift_id. 
// It also defines a custom comparison operator < for use in priority queues, 
// prioritising states with smaller travel_tm values
struct State 
{
    int travel_tm; // an edge
    int floor; // a part of State-Space Graph Representation
    int lift_id; // a part of State-Space Graph Representation
    // for priority queue
    bool operator < (const State& other) const { return travel_tm > other.travel_tm; }
};


constexpr int MAX_FLOOR = 100;
constexpr int MAX_LIFTS = 6;
constexpr int inf = std::numeric_limits<int>::max();
constexpr int WAIT_TM = 60;

namespace algorithms::onlinejudge::graph::lift_hopping
{
    /** https://onlinejudge.org/external/108/10801.pdf */
    int N, target_floor;
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
        
        while(while_read(N, target_floor)) {
          vi lifts_velocity(N);
          for(int n = 0; n < N; ++n) {
            while_read(lifts_velocity[n]);
          }
          std::cin.ignore();
          vvi lifts(N);
          for(int n = 0; n < N; ++n) {
            int floor;
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            while(ss >> floor) lifts[n].push_back(floor);
          }

          vvi time(MAX_FLOOR, vi(MAX_LIFTS, inf));
          std::priority_queue<State> queue;
          // init multi-source Dijkstra
          for(int lift_id = 0; lift_id < N; ++lift_id) {
            vi xs = lifts[lift_id];
            bool is_serve_ground_floor = std::binary_search(xs.begin(), xs.end(), 0);
            if(is_serve_ground_floor) {
              time[0][lift_id] = 0;
              queue.push({0, 0, lift_id});
            }
          }

          while(!queue.empty()) {
            // ....
            State state = queue.top(); queue.pop();
            int travel_tm = state.travel_tm;
            int curr_floor = state.floor;
            int curr_lift_id = state.lift_id;
            
            if(travel_tm > time[curr_floor][curr_lift_id]) continue;

            for(int lift_id = 0; lift_id < N; ++lift_id) {
              // go on on the current lift
              if(lift_id == curr_lift_id) {
                int v = lifts_velocity[curr_lift_id];
                // Get the list of stops for the lift we are currently in.
                vi& stops_on_this_lift = lifts[curr_lift_id];
                // Loop through ALL possible destinations on this same lift line.
                // This single loop handles both UP and DOWN travel.
                for (int next_floor : stops_on_this_lift) {
                  // You can't travel from a floor to itself.
                  if (next_floor == curr_floor) continue;
                  // Calculate cost and update queue if a shorter path is found.
                  int travel_cost = v * std::abs(next_floor - curr_floor);
                  int new_total_time = travel_tm + travel_cost;
                  if(new_total_time < time[next_floor][curr_lift_id]) {
                    time[next_floor][curr_lift_id] = new_total_time;
                    queue.push({new_total_time, next_floor, curr_lift_id});
                  }
                }
              } else {  // take another lift if serves this floor
                vi xs = lifts[lift_id];
                bool is_serve = std::binary_search(xs.begin(), xs.end(), curr_floor);
                if(is_serve) {
                  int new_travel_tm = travel_tm + WAIT_TM;
                  if(new_travel_tm < time[curr_floor][lift_id]) {
                    time[curr_floor][lift_id] = new_travel_tm;
                    queue.push({new_travel_tm, curr_floor, lift_id});
                  }
                }
              }
            }
          }

          int min_sec = inf;
          for(int n = 0; n < N; ++n) {
            min_sec = std::min(min_sec, time[target_floor][n]);
          }
          std::cout << (min_sec != inf ? std::to_string(min_sec) : "IMPOSSIBLE") << std::endl;
        }
    }
}