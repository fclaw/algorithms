/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10187 From Dusk till Dawn, rt: s
 * ───────────────────────────────────────────────────────────────
 * When working with time-based inputs (like departure times in hours), it's natural to expect all 
 * departure times to fall within a valid range, typically 0–23 hours for a 24-hour day.
 *
 * **Input Validation**:
 * Ideally, the program should rely on well-defined input constraints, where the departure time 
 * will always be within this range. In such a case, there is no need for any adjustment or correction 
 * of input data, and the input can be directly used for further processing.
 * 
 * However, if there is any possibility that the input could be malformed or inconsistent (due to
 * external data sources or user input errors), it's a good practice to ensure the departure times 
 * are valid before using them. This can be done by checking the input:
 *   if (departure >= 0 && departure < 24) { ... }
 *   Otherwise, handle the error gracefully (e.g., skip invalid routes or raise an error).
 *
 * **Safe Handling with Modulus**:
 * When there is uncertainty about the input's validity, the modulus operation can be used as a 
 * safeguard. By applying `departure % 24`, we ensure that any invalid departure times (e.g., 25, 30) 
 * are **wrapped** into the valid range (e.g., 25 becomes 1, 30 becomes 6). This guarantees that the 
 * program continues to function even when faced with erroneous data. 
 * 
 * Using the modulus operation is a defensive programming technique to ensure that unexpected values 
 * do not cause runtime errors, such as memory access issues or incorrect comparisons. While this is 
 * not ideal if the input is guaranteed to be valid, it adds robustness to the program in case of 
 * unforeseen input anomalies.
 * 
 * **Summary**:
 * - If input validation guarantees that departure times are valid, the modulus operation is not needed, 
 *   and input should be checked for validity explicitly.
 * - If input is potentially malformed, the modulus operation is a safe fallback to handle any erroneous 
 *   values and ensure the program doesn't break unexpectedly.
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



typedef std::pair<int, int> pii;

template<typename W>
inline constexpr W inf = std::numeric_limits<W>::max();

struct Route
{
    std::string city; // name of the city
    int departure; // departure time
    int time; // travel time
}; 

struct State
{
    std::string city; // name of the city
    int arrival_tm;
    int blood_consumed; // blood consumed to reach this state
    int travel_tm;
    bool operator < (const State& other) const {
      // We want the priority queue to pop the state with the lowest blood_consumed
      return 
        blood_consumed > other.blood_consumed || 
        (blood_consumed == other.blood_consumed && 
         travel_tm > other.travel_tm); // Min-heap based on blood_consumed and travel time
    }
};



constexpr int MAX_HOURS_IN_DAY = 24;
constexpr int noon = 12;


namespace algorithms::onlinejudge::graph::from_dusk_till_dawn
{
    /** https://onlinejudge.org/external/101/10187.pdf */
    int t_cases, R, c = 1;
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
        
        std::cin >> t_cases;
        while(t_cases--) {
          std::cin >> R;
          std::unordered_map<std::string, std::vector<Route>> routes;
          std::unordered_map<std::string, int> city_to_idx;
          int index = 0;
          for(int i = 0; i < R; ++i) {
            std::string from, dest;
            int departure, time;
            while_read(from, dest, departure, time);
            // Add cities to the index
            // This will ensure that each city has a unique index
            // and we can use it to represent the graph
            // in a more compact way
            // This is useful for the priority queue and distance array
            if(city_to_idx.find(from) == city_to_idx.end())
              city_to_idx[from] = index++;
            if(city_to_idx.find(dest) == city_to_idx.end())
              city_to_idx[dest] = index++;

            routes[from].push_back({dest, departure % MAX_HOURS_IN_DAY, time}); 
          }

          int min_blood = inf<int>;
          std::string start_city, dest_city;
          while_read(start_city, dest_city);

          if(start_city == dest_city) {
            printf("Test Case %d.\nVladimir needs 0 litre(s) of blood.\n", c++);
            continue;
          }

          int V = index; // Number of unique cities
          bool can_start = false;
          std::priority_queue<State> queue;
          std::vector<std::vector<pii>> blood(V, std::vector<pii>(MAX_HOURS_IN_DAY, {inf<int>, inf<int>}));
          for(auto& p : routes) {
            if(p.first == start_city) {  
              int idx = city_to_idx.at(start_city);
              for(auto& r : p.second) {
                if(r.departure > 6 && r.departure < 18) continue;
                if(!can_start) can_start = true;
                blood[idx][r.departure] = {0, 0};
                // Starting point, no blood consumed
                queue.push({start_city, r.departure, 0, 0});
              }
            }
          }

          while(can_start && !queue.empty()) {
            State state = queue.top(); queue.pop();
            std::string curr_city = state.city;
            int arrival_tm = state.arrival_tm;
            int blood_consumed = state.blood_consumed;
            int travel_tm = state.travel_tm;
    
            if (blood_consumed > blood[city_to_idx.at(state.city)][arrival_tm].first) {
                continue;
            }

            if(routes.find(state.city) == routes.end()) { continue; }

            // If we reached the destination with enough blood
            if(curr_city == dest_city) {
              min_blood = blood_consumed; break;
            }

            // Explore all routes from the current city
            for(const Route& route : routes[state.city]) {
              if((route.departure >= 7 && route.departure <= 17)) continue;
              if (route.time > 12) continue;

              int new_arrival_tm = (route.departure + route.time) % MAX_HOURS_IN_DAY;
              if(new_arrival_tm >= 7 && new_arrival_tm <= 17) continue;

              // LOGIC FIX: Correctly calculate blood needed.
              // An extra litre is needed if the waiting period at a station includes 12:00 (noon).
              int new_blood_consumed = state.blood_consumed;
              int time_to_wait = (route.departure - state.arrival_tm + MAX_HOURS_IN_DAY) % MAX_HOURS_IN_DAY;

              if(time_to_wait > 0) {
                // Check every hour of the waiting period.
                for(int i = 0; i < time_to_wait; ++i) {
                  int hour_of_day = (state.arrival_tm + i) % MAX_HOURS_IN_DAY;
                  if(hour_of_day == noon) {
                    new_blood_consumed++;
                    break; // Only one litre needed per waiting period.
                  }
                }
              }

              int next_idx = city_to_idx.at(route.city);
              int new_travel_tm = travel_tm + time_to_wait + route.time;
              pii new_state_cost = {new_blood_consumed, new_travel_tm};
              if(new_state_cost < blood[next_idx][new_arrival_tm]) {
                blood[next_idx][new_arrival_tm] = new_state_cost;
                queue.push({route.city, new_arrival_tm, new_blood_consumed, new_travel_tm});
              }
            }
          }
          printf("Test Case %d.\n", c++);
          min_blood == inf<int> ? printf("There is no route Vladimir can take.\n") : printf("Vladimir needs %d litre(s) of blood.\n", min_blood);
        }
    }
}