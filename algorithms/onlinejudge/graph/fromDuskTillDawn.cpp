/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10187 From Dusk till Dawn, rt: s
 * ───────────────────────────────────────────────────────────────
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


constexpr int MAX_TIME = 25;
constexpr int HOUR_24 = 24;


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
          std::unordered_map<std::string, int> city_index;
          int index = 0;
          for(int i = 0; i < R; ++i) {
            std::string from, dest;
            int departure, time;
            while_read(from, dest, departure, time);

            if(routes.find(from) == routes.end()) {
              routes[from] = std::vector<Route>();
              routes[from].push_back({dest, departure, time});
            } else routes[from].push_back({dest, departure, time});

            // Add cities to the index
            // This will ensure that each city has a unique index
            // and we can use it to represent the graph
            // in a more compact way
            // This is useful for the priority queue and distance array
            if(!city_index.count(from))
              city_index[from] = index++;
            if(!city_index.count(dest))
              city_index[dest] = index++;
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
          std::vector<std::vector<pii>> blood(V, std::vector<pii>(MAX_TIME, {inf<int>, inf<int>}));
          for(auto& p : routes) {
            if(p.first == start_city) {  
              int idx = city_index.at(start_city);
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
    
            // If we reached the destination with enough blood
            if(curr_city == dest_city) {
              min_blood = blood_consumed; break;
            }

            // Explore all routes from the current city
            for(const Route& route : routes[state.city]) {
              if((route.departure > 6 &&
                  route.departure < 18) || 
                  route.time > 12)
                continue;
              int next_idx = city_index.at(route.city);
              int diff = (route.departure - arrival_tm + HOUR_24) % HOUR_24;
              int new_arrival_tm = (route.departure + route.time) % HOUR_24;

              if(new_arrival_tm > 6 && new_arrival_tm < 18) continue;

              int daylight_minutes = 0;
              for (int i = 0; i < diff; ++i) {
                int t = (arrival_tm + i) % 24;
                if (t >= 7 && t < 18) ++daylight_minutes;
              }

              int new_blood_consumed = blood_consumed + (int)(daylight_minutes > 0);
              int new_travel_tm = travel_tm + diff + route.time;
              pii new_blood = {new_blood_consumed, new_travel_tm};
              if(new_blood < blood[next_idx][new_arrival_tm]) {
                blood[next_idx][new_arrival_tm] = new_blood;
                queue.push({route.city, new_arrival_tm, new_blood_consumed, new_travel_tm});
              }
            }
          }
          printf("Test Case %d.\n", c++);
          min_blood == inf<int> ? printf("There is no route Vladimir can take.\n") : printf("Vladimir needs %d litre(s) of blood.\n", min_blood);
        }
    }
}