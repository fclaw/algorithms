/*
───────────────────────────────────────────────────────────────
🧳 UVa 10682 Forró Party, https://onlinejudge.org/external/106/10682.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;

constexpr int MAX_CITY = 500;
constexpr int MAX_SPEED = 1000;

/**
 * Represents an undirected road leading to 'to_city' with speed limit 'velocity'.
 */
struct Edge 
{
    int to_city;     // Destination city index (0 to N-1)
    int speed;       // Road speed limit V (0 < V <= 1000)
};

// Graph representation:
// adj[u] = list of outgoing roads from city u
using Graph = std::vector<std::vector<Edge>>;

struct State
{
    /**
     * 1. city_idx (Current Location)
     * ------------------------------
     * The integer index (0 to N-1) of the city Chico is currently in.
     */
    int city_idx;

    /**
     * 2. last_velocity (Current Speed)
     * --------------------------------
     * The speed of the road Chico took to ENTER this city.
     * 
     * Rule: The next road's speed must satisfy: next_speed >= last_speed
     * (Start city initial speed = 0).
     */
    int last_speed;

    /**
     * 3. path (Visited Cities History)
     * --------------------------------
     * List of city indices visited from start to this state.
     * Needed to print the final route output: "CityA CityB CityC...".
     */
    vi path;
};


int get_city_id(int& idx, const std::string& name, std::unordered_map<std::string, int>& city_to_id) {
  auto it = city_to_id.find(name);
  if (it != city_to_id.end()) {
    return it->second; // Already exists
  }
  // New city: assign new index and store in vector
  int new_id = idx++;
  city_to_id[name] = new_id;
  return new_id;
}

std::string get_min_route(const Graph& graph, const std::vector<std::string>& id_to_city, int source, int dest) {

  std::queue<State> queue;
  vvi visited(MAX_CITY + 1, vi(MAX_SPEED + 1, -1));
  queue.push({source, 0, {source}});
  visited[source][0] = 1;

  vi route;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int curr_idx = state.city_idx;
    int last_speed = state.last_speed;
    vi& path_so_far = state.path;

    if(curr_idx == dest) {
      if(route.empty() || 
         (path_so_far.size() < route.size()) ||
         (path_so_far.size() == route.size() 
          && path_so_far < route)) {
        route = path_so_far;
      }
      continue;
    }

    for(const Edge& edge : graph[curr_idx]) {
      int idx = edge.to_city;
      int speed = edge.speed;
      if(!(~visited[idx][speed]) && 
         last_speed <= speed) {
        visited[idx][speed] = 1;
        path_so_far.push_back(idx);
        queue.push({idx, speed, path_so_far});
        path_so_far.pop_back();
      }
    }
  }
  
  if(route.empty()) {
    return "No valid route.";
  } else {
    std::string s_route;
    for(int id : route) {
      auto name = id_to_city[id];
      s_route += name + " ";
    }
    s_route.pop_back();
    return s_route;
  }
}


namespace algorithms::onlinejudge::advanced_topics::forró_party
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

        int R;
        bool is_first = true;
        while(std::cin >> R) {

          // 1. Print blank line BETWEEN test cases
          if (!is_first) {
            std::cout << "\n";
          }
          is_first = false;

          int speed, idx = 0;
          std::string from, to;
          Graph graph(MAX_CITY + 1);
          std::unordered_map<std::string, int> city_to_id;
          for(int r = 0; r < R; ++r) {
            while_read(from, to, speed);
            int from_id = get_city_id(idx, from, city_to_id);
            int to_id = get_city_id(idx, to, city_to_id);
            graph[from_id].push_back({to_id, speed});
            graph[to_id].push_back({from_id, speed});
          }
          std::string source, dest;
          std::cin >> source >> dest;
          int source_id = get_city_id(idx, source, city_to_id);
          int desc_id = get_city_id(idx, dest, city_to_id);


          // 1. Create a vector with the exact size of the map
          std::vector<std::string> id_to_city(city_to_id.size());

          // 2. Populate the vector: id_to_city[id] = name
          for (const auto& pair : city_to_id) {
            const std::string& name = pair.first;
            int id = pair.second;
            id_to_city[id] = name;
          }

          printf("%s\n", get_min_route(graph, id_to_city, source_id, desc_id).c_str());
        }
    }
}