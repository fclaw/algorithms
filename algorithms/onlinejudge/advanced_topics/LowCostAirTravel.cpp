/*
───────────────────────────────────────────────────────────────
🧳 UVa 1048 Low Cost Air Travel, https://onlinejudge.org/external/10/1048.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;



struct Ticket
{
    int id;        // Ticket ID (1-based: 1, 2, ..., N) required for output!
    int cost;      // Ticket price in dollars
    vi cities;     // Ordered sequence of airports: e.g. {1, 4, 3}
};


struct Itinerary
{
    int id;
    vi cities;
};

/**
 * Finds the immediate next city on this ticket after 'current_city'.
 * Returns -1 if current_city is not found or is the last stop on the ticket.
 */
int find_next_city_on_route(const Ticket& t, int current_city, int start_pos = 0) {
  int n = t.cities.size();
    
  // Scan at most 10 cities:
  for(int i = start_pos; i < n - 1; ++i) {
    if(t.cities[i] == current_city) {
      return t.cities[i + 1]; // The next city on the flight
    }
  }
  return -1; // End of the ticket route
}

bool is_the_first_city_on_route(const Ticket& t, int city) {
  auto it = std::find_if(t.cities.begin(), t.cities.end(), [city](int c) { return c == city; });
  return it == t.cities.begin();
}

struct State
{
    /**
     * 1. current_city (Current Location)
     * ----------------------------------
     * The ID of the airport where the traveler is currently standing.
     * Starts at itinerary[0].
     */
    int current_city;

    /**
     * 2. itinerary_idx (Itinerary Checkpoint Progress)
     * ------------------------------------------------
     * The index of the NEXT city in the target itinerary that needs to be reached.
     *   - Range: 0 to itinerary.size()
     *   - Goal Reached when: itinerary_idx == itinerary.size()
     */
    int itinerary_idx;

    int last_ticket;

    int node_pool_idx;

    /**
     * 4. travel_cost (Accumulated Monetary Cost g(n))
     * -----------------------------------------------
     * Total dollars spent on tickets so far.
     * This is the objective function to minimize in Dijkstra.
     */
    int travel_cost;

    /**
     * 5. Priority Queue Min-Heap Comparator
     * -------------------------------------
     * Inverts '<' using 'travel_cost > other.travel_cost' so that 
     * std::priority_queue pops the CHEAPEST route first.
     * 
     * Tie-breaker: If costs are equal, prefer FEWER tickets used!
     */
    bool operator < (const State& other) const {
      return travel_cost > other.travel_cost; // Min-cost first
    }
};

// Global or per-testcase City ID Mapper
std::unordered_map<int, int> city_to_id;
vi id_to_city;


int get_id(int raw_city) {
    auto it = city_to_id.find(raw_city);
    if (it != city_to_id.end()) return it->second;
    int id = id_to_city.size();
    city_to_id[raw_city] = id;
    id_to_city.push_back(raw_city);
    return id;
}

struct Node
{
    int parent_idx;
    int last_ticket;
};


std::pair<int, std::string> get_min_cost(const std::vector<Ticket>& tickets, Itinerary& itinerary) {

  std::priority_queue<State> queue;
  vvvi cost(4000, vvi(itinerary.cities.size(), vi(tickets.size() + 2, INT32_MAX)));
  std::vector<Node> node_pool(200000, {-1, 0}); 

  // init
  int nodes_pool_idx = 0;
  queue.push({itinerary.cities.front(), 0, 0, 0, 0});

  int min_cost = -1;
  std::string tickets_in_trip;

  while(!queue.empty()) {

    State state = queue.top(); queue.pop();
    int curr_city = state.current_city;
    int curr_city_id = get_id(curr_city);
    int itinerary_idx = state.itinerary_idx;
    int travel_cost_so_far = state.travel_cost;
    int last_ticket_id = state.last_ticket;

    int curr_node_pool_idx = state.node_pool_idx;
   
    if(curr_city == itinerary.cities[itinerary_idx]) {
      itinerary_idx++;
    }

    if(itinerary_idx == (int)itinerary.cities.size()) {
      // ==========================================
      // Backtrack Tree to Reconstruct Path (O(depth))
      // ==========================================
      vi path;
      int curr = curr_node_pool_idx;
      while (~node_pool[curr].parent_idx) {
        path.push_back(node_pool[curr].last_ticket);
        curr = node_pool[curr].parent_idx; // Step up the tree!
      }

      std::reverse(path.begin(), path.end());
      for(int t : path) {
        tickets_in_trip += std::to_string(t) + " ";
      }
      tickets_in_trip.pop_back();
      min_cost = travel_cost_so_far;
      break;
    }

    if(travel_cost_so_far > cost[curr_city_id][itinerary_idx][last_ticket_id]) {
      continue;
    }

    // transition logic
    for(const auto& ticket : tickets) {
      int ident = ticket.id;
      if(ident == last_ticket_id) { // go on with the current ticket
        int next_city = find_next_city_on_route(ticket, curr_city);
        if(!~next_city) continue;
        int& cost_so_far = cost[get_id(next_city)][itinerary_idx][ident];
        if(travel_cost_so_far < cost_so_far) {
          cost_so_far = travel_cost_so_far;
          State new_state = {next_city, itinerary_idx, last_ticket_id, curr_node_pool_idx, travel_cost_so_far};
          queue.push(new_state);
        }
      } else { // drop the current ticket and start from another
        if(is_the_first_city_on_route(ticket, curr_city)) {
          int new_travel_cost = ticket.cost + travel_cost_so_far;
          int& cost_so_far = cost[curr_city_id][itinerary_idx][ident];
          if(new_travel_cost < cost_so_far) {
            cost_so_far = new_travel_cost;
            State new_state = {curr_city, itinerary_idx, ident, ++nodes_pool_idx, new_travel_cost};
            queue.push(new_state);
            node_pool[nodes_pool_idx] = {curr_node_pool_idx, ident};
          }
        }
      }
    }
  }

  return {min_cost, tickets_in_trip};
}
 

namespace algorithms::onlinejudge::advanced_topics::low_cost_air_travel
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

        int N, t_case = 0;
        while(std::cin >> N && N) {
   
          // Reset ID mapper for the new test case
          city_to_id.clear();
          id_to_city.clear();

          std::vector<Ticket> tickets(N);
          for(int i = 0; i < N; ++i) {
            int cities_n;
            std::cin >> tickets[i].cost;
            std::cin >> cities_n;
            tickets[i].id = i + 1;
            tickets[i].cities.resize(cities_n);
            for(int j = 0; j < cities_n; ++j) {
              int raw_city;
              std::cin >> raw_city;
              tickets[i].cities[j] = get_id(raw_city);
            }
          }
          int I;
          std::cin >> I;
          std::vector<Itinerary> itineraries(I);
          for(int i = 0; i < I; ++i) {
            int S;
            std::cin >> S;
            itineraries[i].id = i + 1;
            itineraries[i].cities.resize(S);
            for(int s = 0; s < S; ++s) {
              int raw_city;
              std::cin >> raw_city;
              itineraries[i].cities[s] = get_id(raw_city);
            }
          }
          t_case++;
          for(auto itinerary : itineraries) {
            std::pair<int, std::string> ans = get_min_cost(tickets, itinerary);
            printf("Case %d, Trip %d: Cost = %d\n  Tickets used: %s\n", t_case, itinerary.id, ans.first, ans.second.c_str());
          }
        }
    }
}