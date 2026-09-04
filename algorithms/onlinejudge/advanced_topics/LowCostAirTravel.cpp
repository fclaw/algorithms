/*
───────────────────────────────────────────────────────────────
🧳 UVa 1048 Low Cost Air Travel, https://onlinejudge.org/external/10/1048.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <cassert>


using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


constexpr int MAX_CITY_IDX = 200;
constexpr int MAX_NODE_IDX = 1000; // Maximum number of nodes in the backtracking tree (ticket purchase history)


struct Ticket
{
    int id;        // Ticket ID (1-based: 1, 2, ..., N) required for output!
    int cost;      // Ticket price in dollars
    vi cities;     // Ordered sequence of airports: e.g. {1, 4, 3}
};


struct Itinerary
{
    int id; // Itinerary ID (1-based: 1, 2, ..., I) required for output!
    vi cities; // Ordered sequence of airports to visit: e.g. {1, 3, 4}
};


struct State
{
    /**
     * 1. current_city (Current Location)
     * ----------------------------------
     * The ID of the airport where the traveler is currently standing.
     * Starts at itinerary[0].
     */
    int current_city_id;

    /**
     * 2. itinerary_idx (Itinerary Checkpoint Progress)
     * ------------------------------------------------
     * The index of the NEXT city in the target itinerary that needs to be reached.
     *   - Range: 0 to itinerary.size()
     *   - Goal Reached when: itinerary_idx == itinerary.size()
     */
    int itinerary_idx;

    /**
     * 3. last_ticket_id (Active Flight Ticket Mode)
     * ---------------------------------------------
     * Stores the ID (1 to N) of the ticket currently being used for travel.
     * Starts at -1 (or 0) before any ticket is purchased.
     * 
     * Role in Dijkstra:
     *   - If last_ticket_id != -1: 
     *       The traveler is currently in-flight on this ticket. They can advance 
     *       to the next city along this ticket's route for $0 cost!
     *   - Serves as the 3rd dimension in the cost table:
     *       cost[current_city][itinerary_idx][last_ticket_id]
     *       distinguishing whether you arrived at a city on Ticket #1 vs Ticket #2.
     */
    int last_ticket_id;

    /**
     * 4. node_pool_idx (Backtracking Tree Pointer)
     * --------------------------------------------
     * The index in the global `node_pool` array pointing to the chain of tickets 
     * purchased to reach this state.
     * 
     * Role in Path Reconstruction:
     *   - Acts as a pointer in an append-only tree: node_pool[idx] = {parent_idx, ticket_id}.
     *   - When a NEW ticket is bought, a new node is allocated:
     *       node_pool[++nodes_pool_idx] = {curr.node_pool_idx, new_ticket_id};
     *   - When an intermediate flight leg is flown, this index is simply carried over 
     *     (no new tickets are added to the history).
     *   - At the goal, we trace parent_idx back to -1 to extract the exact list 
     *     of ticket IDs in O(depth) time with zero vector copying in the queue!
     */
    int node_pool_idx;

    /**
     * 5. travel_cost (Accumulated Monetary Cost g(n))
     * -----------------------------------------------
     * Total dollars spent on tickets so far.
     * This is the objective function to minimize in Dijkstra.
     */
    int travel_cost;

    int ticket_pos; // Index in ticket.cities (0, 1, 2... 9)

    /**
     * 6. Priority Queue Min-Heap Comparator
     * -------------------------------------
     * Inverts '<' using 'travel_cost > other.travel_cost' so that 
     * std::priority_queue pops the CHEAPEST route first.
     */
    bool operator < (const State& other) const {
      return travel_cost > other.travel_cost; // Min-cost first
    }
};

// Global or per-testcase City ID Mapper
std::unordered_map<int, int> city_to_id;
vi id_to_city;
int unique_city_counter;


int get_id(int raw_city) {
    auto it = city_to_id.find(raw_city);
    if (it != city_to_id.end()) return it->second;
    city_to_id[raw_city] = unique_city_counter++;
    id_to_city.push_back(raw_city);
    return city_to_id.at(raw_city);
}

// Node structure for the backtracking tree
struct Node
{
    int parent_idx; // Index of the parent node in the node_pool (or -1 for root)
    int last_ticket; // The ticket ID used to reach this node from its parent
};

// Function to find the minimum cost itinerary
std::pair<int, std::string> get_min_cost(const std::vector<Ticket>& tickets, Itinerary& itinerary) {

  std::priority_queue<State> queue;
  vvvi cost(MAX_CITY_IDX, vvi(itinerary.cities.size(), vi(tickets.size() + 2, INT32_MAX)));
  std::vector<Node> node_pool(MAX_NODE_IDX, {-1, 0}); 

  // init
  int nodes_pool_idx = 0;
  queue.push({itinerary.cities.front(), 0, 0, 0, 0, 0});

  int min_cost = -1;
  std::string tickets_in_trip;

  while(!queue.empty()) {

    State state = queue.top(); queue.pop();
    int curr_city_id = state.current_city_id;
    int itinerary_idx = state.itinerary_idx;
    int travel_cost_so_far = state.travel_cost;
    int last_ticket_id = state.last_ticket_id;
    int curr_ticket_pos = state.ticket_pos;

    int curr_node_pool_idx = state.node_pool_idx;
 
    assert((curr_node_pool_idx < MAX_NODE_IDX) && "Exceeded node pool size. Increase MAX_NODE_IDX.");


    if(curr_city_id == itinerary.cities[itinerary_idx]) {
      ++itinerary_idx;
    }

    if(itinerary_idx == (int)itinerary.cities.size()) {
      min_cost = travel_cost_so_far;
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
        tickets_in_trip += " " + std::to_string(t);
      }
      break;
    }

    // Prune states that are already worse than the best known cost to reach this city and itinerary index with the same last ticket
    if(travel_cost_so_far > cost[curr_city_id][itinerary_idx][last_ticket_id]) {
      continue;
    }

    // ============================================================================
    // DIJKSTRA TRANSITION LOGIC (The 2-Phase Ticket State Machine)
    // ============================================================================
    for(const auto& ticket : tickets) {
      int ident = ticket.id;
      // ------------------------------------------------------------------------
      // CASE 1: IN-FLIGHT LEG (Continue flying on the currently active ticket)
      // ------------------------------------------------------------------------
      if(ident == last_ticket_id) { // go on with the current ticket
        int next_ticket_pos = curr_ticket_pos + 1;
        if(next_ticket_pos < (int)ticket.cities.size()) {
          int next_city_id = ticket.cities[next_ticket_pos];
          // Flying an intermediate leg on an already-purchased ticket costs $0!
          int& cost_so_far = cost[next_city_id][itinerary_idx][ident];
          if(travel_cost_so_far < cost_so_far) {
            cost_so_far = travel_cost_so_far;
            // Notice: curr_node_pool_idx is unchanged because we are still using 
            // the SAME ticket (we only add a new node to the pool upon purchase!)
            State new_state = {next_city_id, itinerary_idx, last_ticket_id, curr_node_pool_idx, travel_cost_so_far, next_ticket_pos};
            queue.push(new_state);
          }
        }
      // ------------------------------------------------------------------------
      // CASE 2: NEW TICKET PURCHASE (Drop previous ticket, buy & board a new one)
      // ------------------------------------------------------------------------
      } else { // drop the current ticket and start from another
        // Airline Rule: You can ONLY buy a ticket if you are physically 
        // standing at its first departure city (ticket.cities.front())!
        if(ticket.cities.front() == curr_city_id) {
          int new_travel_cost = ticket.cost + travel_cost_so_far;
          int& cost_so_far = cost[curr_city_id][itinerary_idx][ident];
          // Relax edge in Dijkstra:
          if(new_travel_cost < cost_so_far) {
            cost_so_far = new_travel_cost;
            State new_state = {curr_city_id, itinerary_idx, ident, ++nodes_pool_idx, new_travel_cost, 0};
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
          unique_city_counter = 0;

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
            printf("Case %d, Trip %d: Cost = %d\n  Tickets used:%s\n", t_case, itinerary.id, ans.first, ans.second.c_str());
          }
        }
    }
}