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
      tools::vi& visited,
      const tools::vb& is_junction, 
      const tools::Graph<>& network)
    {
        // BFS to find the average time to all junctions
        // queue contains (station, line, travel_time)
        // visited keeps track of visited stations on each line
        // map contains the adjacency list of the graph
        tools::vi times(V, -1);
        times[source] = 0; // Start from the source station
        while(!queue.empty()) {
          State state = queue.front(); queue.pop();
          int station = state.station;
          int travel_time = state.travel_time;

          if(is_junction[station]) {
            if(!(~times[station])) 
              times[station] = 2 * travel_time;
          }

          for(const auto& n : network[station]) {
            int next = n.node;
            if(!visited[next]) {
              visited[next] = 1; // Mark as visited
              queue.push({next, travel_time + 1});
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
          tools::vvi counter(V); // Track which lines each station belongs to
          tools::Graph<> network(V); 
          int junctions_num = 0;
          tools::vb is_junction(V, false);
          for(int line = 0; line < lines; ++line) {
            int curr, prev = tools::sentinel;
            while(while_read(curr) && --curr >= 0) {
              if(prev != tools::sentinel) {
                network[prev].push_back(tools::mkDefNode(curr));
                network[curr].push_back(tools::mkDefNode(prev));
              }
              prev = curr;

              // Detect junctions on the fly
              if (!counter[curr].empty() &&
                  counter[curr].back() != line) {
                if (!is_junction[curr]) {
                  is_junction[curr] = true;
                  ++junctions_num;
                }
              }

              counter[curr].push_back(line);
            }
          }

          int best_station = -1;
          double best_avg_time = std::numeric_limits<double>::max();
          for(int v = 0 ; v < V; ++v) {
            if(counter[v].size() <= 1) continue; // Skip non-junctions
            tools::vi visited(V);
            std::queue<State> queue;
            queue.push({v, 0}); // Start BFS from the current station
            visited[v] = 1; // Mark the starting station as visited
            double total_time = do_bfs(v, queue, visited, is_junction, network);
            double avg_time = total_time / junctions_num; // Average time to all junctions
            if(avg_time < best_avg_time) {
              best_avg_time = avg_time;
              best_station = v;
            } else if(avg_time == best_avg_time)
              best_station = std::min(best_station, v); // Prefer the lower numbered station
          }
          printf("Krochanska is in: %d\n", best_station == -1 ? -1 : best_station + 1);
        }
    }
}