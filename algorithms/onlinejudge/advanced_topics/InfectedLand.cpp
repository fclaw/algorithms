/*
───────────────────────────────────────────────────────────────
🧳 UVa 1253 Infected Land, https://onlinejudge.org/external/12/1253.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;


int SIZE;

struct State
{
    /**
     * 1. vehicle_row & 2. vehicle_col (Vehicle Position)
     * --------------------------------------------------
     * The current 2D grid coordinates (r, c) of the anti-virus vehicle '@'.
     * Boundaries: 0 <= vehicle_row < N, 0 <= vehicle_col < N (N <= 5).
     */
    int vehicle_row;
    int vehicle_col;

    /**
     * 3. infected_area (Grid Virus Distribution)
     * ------------------------------------------
     * An N x N matrix representing the infection state of each square:
     *   - 1 : Square is INFECTED ('#')
     *   - 0 : Square is CLEAN ('.')
     */
    vvi infected_area;

    /**
     * 4. steps (Path Length / Distance g(n))
     * --------------------------------------
     * The total number of vehicle moves made so far from the initial setup.
     * This is an unweighted BFS where each turn costs exactly 1 step.
     */
    int steps;
};

/**
 * Checks if the goal condition is met:
 * Returns true if ALL cells on the grid are clean (0 virus cells left).
 */
bool is_area_virus_free(const vvi& area) {
  for(const auto& row : area) {
    for (int cell : row) {
      if (cell == 1) { // Found an active infected cell '#'
        return false;
      }
    }
  }
  return true; // Completely virus-free! GOAL REACHED! 🏁
}

// Packs (vehicle_row, vehicle_col, area) into a unique integer ID
int pack_state(int vr, int vc, const vvi& area) {
    int N = area.size();
    int mask = 0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (area[r][c] == 1) {
                mask |= (1 << (r * N + c));
            }
        }
    }
    // Combine vehicle position (0..24) with the 25-bit mask
    return (vr * N + vc) * (1 << 25) + mask;
}

// 8 Direction deltas: horizontal, vertical, and diagonal
const int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

bool is_vehicle_in_area(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; };


/**
 * Simulates Conway's Game of Life virus evolution simultaneously across the grid.
 * 
 * @param curr_area  The old virus grid snapshot (1 = infected '#', 0 = clean '.')
 * @param vr, vc     The new coordinates where the vehicle '@' just moved to.
 * @return           The newly evolved N x N virus grid.
 */
vvi apply_decease_spread(const vvi& curr_area, int vr, int vc) {
    int N = curr_area.size();
    vvi next_area(N, vi(N, 0)); // Fresh new board

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            
            // 1. RULE: The vehicle's cell is PROTECTED & IMMUNE (always clean 0)
            if (r == vr && c == vc) {
                next_area[r][c] = 0;
                continue;
            }

            // 2. Count 8 infected neighbors using ONLY the curr_area snapshot
            int k = 0;
            for (int d = 0; d < 8; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                    // Vehicle counts as an infected neighbor (+1)
                    if (nr == vr && nc == vc) {
                        k++;
                    }
                    // Actual '#' infected cell counts as +1
                    else if (curr_area[nr][nc] == 1) {
                        k++;
                    }
                }
            }

            // 3. Apply Conway's Game of Life Rules:
            if (curr_area[r][c] == 1) {
                // Infected cell survives if it has 2 or 3 neighbors
                if (k == 2 || k == 3) {
                    next_area[r][c] = 1; 
                }
            } else {
                // Clean cell becomes infected if it has EXACTLY 3 neighbors
                if (k == 3) {
                    next_area[r][c] = 1; 
                }
            }
        }
    }

    return next_area;
}


int min_steps_required(const vvi& area, int vehicle_row, int vehicle_col) {

  std::queue<State> queue;
  std::unordered_set<int> visited;
  
  // init
  queue.push({vehicle_row, vehicle_col, area, 0});
  visited.insert(pack_state(vehicle_row, vehicle_col, area));
  int min_steps = -1;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int v_r = state.vehicle_row;
    int v_c = state.vehicle_col;
    vvi curr_area = state.infected_area;
    int steps_so_far = state.steps;


    if(is_area_virus_free(curr_area)) {
       min_steps = steps_so_far;
       break;
    }

    for(int d = 0; d < 8; ++d) {
      int next_v_r = v_r + dr[d];
      int next_v_c = v_c + dc[d];
      if(is_vehicle_in_area(next_v_r, next_v_c) &&  // in bound and virus free
         !curr_area[next_v_r][next_v_c]) {
        vvi next_area = apply_decease_spread(curr_area, next_v_r, next_v_c);
        int state_idx = pack_state(next_v_r, next_v_c, next_area);
        if(!visited.count(state_idx)) {
          visited.insert(state_idx);
          queue.push({next_v_r, next_v_c, next_area, 1 + steps_so_far});
        }
      }
    }

  }

  return min_steps;
}

namespace algorithms::onlinejudge::advanced_topics::infected_land
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

        while(std::cin >> SIZE && SIZE) {
          char cell;
          int vehicle_row = 0, vehicle_col = 0;
          vvi infected_area(SIZE, vi(SIZE));
          for(int r = 0; r < SIZE; ++r) {
            for(int c = 0; c < SIZE; ++c) {
              std::cin >> cell;
              if(cell == '#') {
                infected_area[r][c] = 1;
              } else if(cell == '@') {
                vehicle_row = r;
                vehicle_col = c;
              }
            } 
          }
          printf("%d\n", min_steps_required(infected_area, vehicle_row, vehicle_col));
        }
    }
}
