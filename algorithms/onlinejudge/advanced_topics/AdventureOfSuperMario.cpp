/*
───────────────────────────────────────────────────────────────
🧳 UVa 10269 Adventure of Super Mario, https://onlinejudge.org/external/102/10269.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;


struct State
{
    /**
     * 1. settlement (Current Node / Location ID)
     * -----------------------------------------
     * The ID of the place Mario is currently located in:
     *   - 1 ... A       : Villages (Safe for intermediate super-runs)
     *   - A + 1 ... A+B : Castles  (Contain traps; cannot super-run through!)
     * 
     * Start: Castle (A + B)
     * Goal : Village 1
     */
    int settlement;

    /**
     * 2. super_run_left (Layer Dimension in Layered Graph)
     * ----------------------------------------------------
     * The number of Magic Boot charges remaining (0 to K).
     * 
     * Transitions:
     *   - Normal Walk : Stays in the SAME layer (super_run_left unchanged)
     *   - Super-Run   : Drops DOWN to the next layer (super_run_left - 1)
     */
    int super_run_left;

    /**
     * 3. time (Accumulated Path Cost / Distance g(n))
     * -----------------------------------------------
     * The total travel time in seconds accumulated from Castle (A + B).
     * This is the value we want to minimize in Dijkstra.
     */
    int time;

    /**
     * 4. Priority Queue Min-Heap Comparator
     * -------------------------------------
     * Inverts the default '<' operator using 'time > other.time' so that 
     * `std::priority_queue<State>` pops the state with the SMALLEST travel time first.
     */
    bool operator < (const State& other) const {
      return time > other.time; 
    }
};

int get_min_time_required(const vvii& network, int villages_n, int castles_n, int allowed_max_dist, int super_run) {

  int SIZE = villages_n + castles_n;
  vvi dist_village_only(SIZE, vi(SIZE, INT32_MAX));
  for(int i = 0; i < SIZE; ++i) {
    for(ii o : network[i]) {
      dist_village_only[i][o.first] = o.second;
    }
  }
  
  // Floyd-Warshall using ONLY Villages as intermediate nodes:
  for(int k = 0; k < villages_n; ++k) {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        if(dist_village_only[i][k] != INT32_MAX && 
           dist_village_only[k][j] != INT32_MAX) {
          int t = dist_village_only[i][k] + dist_village_only[k][j];
          dist_village_only[i][j] = std::min(dist_village_only[i][j], t);
        }
      }
    }
  }

  std::priority_queue<State> queue;
  vvi time(SIZE, vi(super_run + 1, INT32_MAX));

  int start = SIZE - 1;
  int end = 0;
  // init
  queue.push({start, super_run, 0});
  time[start][super_run] = 0;
 
  int min_time = INT32_MAX;

  while(!queue.empty()) {
    State state = queue.top(); queue.pop();
    int curr_settlement = state.settlement;
    int super_run_left = state.super_run_left;
    int time_so_far = state.time;
    
    if(curr_settlement == end) {
      min_time = std::min(min_time, time_so_far);
      break;
    }

    // prune
    if(time_so_far > time[curr_settlement][super_run_left]) {
      continue;
    }

    // ==========================================
    // 1. NORMAL WALK
    // ==========================================
    for(ii o : network[curr_settlement]) {
      int s = o.first;
      int t = o.second;
      int next_t = time_so_far + t;
      int& s_time = time[s][super_run_left];
      if(next_t < s_time) {
        s_time = next_t;
        queue.push({s, super_run_left, next_t});
      }
    }

    // ==========================================
    // 2. USE SUPER-RUN
    // ==========================================
    if (super_run_left > 0) {
      for(int s = 0; s < SIZE; ++s) {
        if(s == curr_settlement) continue;
        int t = dist_village_only[curr_settlement][s];
        if(t != INT32_MAX && 
           t <= allowed_max_dist) {
          int new_super_run_left = super_run_left - 1;
          int& s_time = time[s][new_super_run_left];
          if(time_so_far < s_time) {
            s_time = time_so_far;
            queue.push({s, new_super_run_left, time_so_far});
          }
        }
      }
    }
  }

  return min_time;
}


namespace algorithms::onlinejudge::advanced_topics::adventure_of_super_Mario
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

        int t_cases;
        std::cin >> t_cases;
        while(t_cases--) {
          int villages_n;
          int castles_n;
          int roads_n;
          int allowed_max_dist; 
          int super_run;
          while_read(
            villages_n, 
            castles_n, 
            roads_n, 
            allowed_max_dist, 
            super_run);
          vvii network(villages_n + castles_n);
          int from, to, length;
          for(int r = 0; r < roads_n; ++r) {
            std::cin >> from >> to >> length;
            --from; --to;
            network[from].push_back({to, length});
            network[to].push_back({from, length});
          }
          printf("%d\n", get_min_time_required(network, villages_n, castles_n, allowed_max_dist, super_run));
        }
    }
}