/*
───────────────────────────────────────────────────────────────
🧳 UVa 11792 Krochanska is Here!, rt: s

Problem Summary:
Given a set of train lines, each consisting of a sequence of stations,
identify the "important" station from which the average shortest time 
to all other important stations is minimised.

--------------------------------------------------------
Key Observations:
- Time to travel between two **adjacent stations** is fixed at **2 units**.
- A station may appear in multiple lines (i.e., it is a junction).
- Movement along a line is sequential; however, at junctions,
  we may switch lines at **zero time cost**.

--------------------------------------------------------
Approach:
1. **Input Parsing & Graph Construction**
   - Read all lines and build an adjacency list.
   - Track which stations appear in multiple lines;
     these are considered "important stations."

2. **Model the Graph**
   - Each station has multiple *line contexts* (i.e., same station, different line).
   - Transitions:
     - Adjacent station on the same line → cost = 2
     - Same station on a different line → cost = 0

3. **Use 0-1 BFS**
   - Each BFS state includes (station, line).
   - Maintain a visited matrix: `visited[line][station]`.
   - Use a deque:
     - Line change → push to front (cost 0)
     - Step to adjacent → push to back (cost 2)

4. **Run BFS from Each Important Station**
   - For each important station:
     - Start BFS from all line contexts where it appears.
     - Track shortest distances to all other important stations.
     - Compute the average time.

5. **Find the Station with Minimal Average Time**
   - Return the station with the lowest average time to others.
   - If multiple stations tie, pick the one with the lowest number.

--------------------------------------------------------
Complexity:
- Time: O(M * K), where M is the number of lines, K the max stations per line
- Space: Efficient due to bounded limits (≤1000 stations and lines)
───────────────────────────────────────────────────────────────
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




struct State
{
    int station; // number of station in the line
    int travel_time; // travel time to this station
};


namespace algorithms::onlinejudge::graph::krochanska
{
    /** https://onlinejudge.org/external/117/11792.pdf */
    int t_cases, V, lines;
    double do_bfs(
      int source,
      std::queue<State>& queue, 
      tools::vvi& visited,
      const tools::vvi& map, 
      const tools::Graph<int>& network)
    {
        // BFS to find the average time to all junctions
        // queue contains (station, line, travel_time)
        // visited keeps track of visited stations on each line
        // map contains the adjacency list of the graph
        tools::vi times(V, 0);
        while(!queue.empty()) {
          State state = queue.front(); queue.pop();
          int station = state.station;
          int travel_time = state.travel_time;

          bool is_junction = map[station].size() > 1;
          if(is_junction && station != source) {
            if(times[station] == 0)
              times[station] = travel_time; // First time visiting this junction
            else times[station] = std::min(times[station], travel_time);
          }
          for(const auto& n : network[station]) {
            int next_station = n.node;
            int line_id = n.value;
            if(!visited[next_station][line_id]) {
              visited[next_station][line_id] = 1; // Mark as visited
              queue.push({next_station, travel_time + 1});
            }
          }
        }
        double total_time = 0.0;
        for(int i = 0; i < V; ++i) {
          if(times[i] > 0)
            total_time += times[i];
        }
        return total_time;
    }
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
          while_read(V, lines);
          std::cin.ignore();
          tools::vvi junctions(V); // Track which lines each station belongs to
          std::string s;
          tools::Graph<int> network(V);
          loop(lines, [&](int line) {
            std::getline(std::cin, s);
            std::istringstream iss(s);
            int curr, prev = tools::sentinel;
            while(iss >> curr && curr) {
              --curr; // Convert to 0-based index
              if(prev != tools::sentinel) {
                network[prev].push_back(tools::Node<int>{curr, line});
                network[curr].push_back(tools::Node<int>{prev, line});
              }
              prev = curr;
              junctions[curr].push_back(line);
            }
          });

          // Find all junctions (stations with more than one line) 
          int junctions_num = 0;
          for(const auto& p : junctions) {
            if(p.size() > 1) {
              ++junctions_num; // Count only junctions
            }
          }
          

          int best_station = -1;
          double best_avg_time = std::numeric_limits<double>::max();
          for(int v = 0 ; v < V; ++v) {
            if(junctions[v].size() == 1) continue; // Skip non-j
            tools::vvi visited(V, tools::vi(lines, 0));
            std::queue<State> queue;
            for(int line_id : junctions[v]) {
              visited[v][line_id] = 1; // Mark as visited
              // Start BFS from this station on the given line
              queue.push({v, 0});
            }
            double total_time = do_bfs(v, queue, visited, junctions, network);
            double avg_time = total_time / junctions_num; // Average time to all junctions
            if(avg_time < best_avg_time) {
              best_avg_time = avg_time;
              best_station = v;
            } else {
              if(avg_time ==
                best_avg_time && 
                v < best_station)
                best_station = v; // Prefer the lower numbered station
            }
          }
          printf("Krochanska is in: %d\n", best_station == -1 ? -1 : best_station + 1);
        }
    }
}