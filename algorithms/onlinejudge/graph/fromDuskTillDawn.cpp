/*
 * ───────────────────────────────────────────────────────────────
 * 🧳 UVa 10187 From Dusk till Dawn, rt: s
 * ───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/dfs.cpp"

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




namespace tools = algorithms::onlinejudge::graph::tools;

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
    int arrival; // arrival time
    int blood_consumed; // blood consumed to reach this state
    int travel_time;
    bool operator < (const State& other) const {
      // We want the priority queue to pop the state with the lowest blood_consumed
      return 
        blood_consumed > other.blood_consumed || 
        (blood_consumed == other.blood_consumed && 
         travel_time > other.travel_time); // Min-heap based on blood_consumed and travel time
    }
};

constexpr int MAX_ARRIVAL = 25;
constexpr int HOUR_24 = 24;


namespace algorithms::onlinejudge::graph::from_dusk_till_dawn
{
    /** https://onlinejudge.org/external/101/10187.pdf */
    int t_cases, c = 1;
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
          int R;
          while_read(R);
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

          int V = index; // Number of unique cities
          int min_blood = inf<int>;
          std::string start_city, dest_city;
          while_read(start_city, dest_city);
          int start_index = city_index[start_city];
          std::priority_queue<State> queue;
          tools::vvi blood(V, tools::vi(MAX_ARRIVAL, inf<int>));
          blood[start_index][0] = 0; // Starting point, no blood consumed
          queue.push({start_city, 0, 0}); // (city, arrival time, blood consumed)
          while(!queue.empty()) {
            State state = queue.top(); queue.pop();
            std::string curr_city = state.city;
            int arrival = state.arrival;
            int blood_consumed = state.blood_consumed;
    
            // If we reached the destination with enough blood
            if(curr_city == dest_city) {
               min_blood = blood_consumed; 
                break;
            }
    
            // Explore all routes from the current city
            for(const Route& route : routes[state.city]) {
              int next_city_index = city_index.at(route.city);
              int next_arrival = (route.departure + route.time) % HOUR_24; // Wrap around after 24 hours

              if(route.departure  > 6 && route.departure  < 18) continue;

              if(arrival < route.departure) {
                int new_blood_consumed = blood_consumed + (next_arrival < arrival ? 1 : 0); // Blood consumed if we arrive after midnight
                // If we can reach the next city with less blood consumed
                if(new_blood_consumed < blood[next_city_index][next_arrival]) {
                  blood[next_city_index][next_arrival] = new_blood_consumed;
                  queue.push({route.city, next_arrival, new_blood_consumed});
                }
              }
            }
          }
          printf("Test Case %d.\n", c++);
          min_blood == inf<int> ? printf("There is no route Vladimir can take.\n") : printf("Vladimir needs %d litre(s) of blood.\n", min_blood);
        }
    }
}