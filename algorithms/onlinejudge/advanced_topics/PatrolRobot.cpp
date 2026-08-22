/*
───────────────────────────────────────────────────────────────
🧳 UVa 1600 Patrol Robot, https://onlinejudge.org/external/16/1600.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;


constexpr int inf = std::numeric_limits<int>::max();
constexpr int MAX_M = 20;
constexpr int MAX_N = 20;
constexpr int MAX_K = 20;


// { {delta_row, delta_col}, Direction }
const vii
  dirs4 = {
    {-1,  0}, // Row - 1 (Up)
    { 0,  1}, // Col + 1 (Right)
    { 1,  0}, // Row + 1 (Down)
    { 0, -1}  // Col - 1 (Left)
  };


struct State
{
    /**
     * 1. row & 2. col (Spatial Coordinates)
     * -------------------------------------
     * The current 2D grid position of the robot on the M x N map.
     * Boundaries: 0 <= row < M, 0 <= col < N.
     * Start is typically (0, 0) and Destination is (M - 1, N - 1).
     */
    int row;
    int col;

    /**
     * 3. energy_left / consecutive_k (Consecutive Obstacle Quota)
     * -----------------------------------------------------------
     * Represents how many MORE consecutive obstacle squares ('1's) 
     * the robot can traverse without landing on an empty square ('0').
     *
     * CRITICAL PROBLEM RULE:
     * - This is NOT a total budget for the whole run!
     * - It only limits CONSECUTIVE obstacles.
     * 
     * State Transitions:
     *   - Stepping onto an empty cell ('0'):
     *       -> 'energy_left' RESETS back to maximum 'k'.
     *   - Stepping onto an obstacle ('1'):
     *       -> 'energy_left' DECREASES by 1.
     *       -> If 'energy_left' drops below 0, the state is INVALID/pruned.
     */
    int energy_left; 

    /**
     * 4. moves (Cost / Step Count)
     * ----------------------------
     * The total number of steps taken from the start cell (0, 0) to this state.
     * Each step into an adjacent cell (Up, Down, Left, Right) adds exactly +1 move.
     * This is the value to minimize.
     */
    int moves; 

    /**
     * 5. Priority Queue Comparator (Min-Heap)
     * ---------------------------------------
     * Inverts the default `<` operator so that `std::priority_queue<State>` 
     * behaves as a MIN-HEAP, popping the state with the FEWEST moves first.
     * 
     * Note: Since every move costs exactly 1 unit, a standard `std::queue<State>` 
     * (unweighted BFS) also works and is slightly faster (O(1) pop vs O(log N)).
     */
    bool operator < (const State& other) const { 
      return moves > other.moves; 
    }
};


int N, M;

bool in_grid(int r, int c) { return r >= 0 && r < N && c >= 0 && c < M; }

int get_min_moves_required(const vi& grid, int k) {

  vvvi move(MAX_M + 1, vvi(MAX_N + 1, vi(MAX_K + 1, inf)));
  std::priority_queue<State> queue;

  State init = {0, 0, k, 0};
  move[0][0][k] = 0;
  queue.push(init);
   
  int min_moves_required = -1;

  while(!queue.empty()) {
    
    State state = queue.top(); queue.pop();
    int r = state.row;
    int c = state.col;
    int energy_left = state.energy_left;
    int moves_so_far = state.moves;

    // goal
    if(r == N - 1 && 
       c == M - 1) {
      min_moves_required = moves_so_far;
      break;
    }

    if(moves_so_far > move[r][c][energy_left] ||
       ((grid[r] & (1 << c)) && energy_left < 0)) {
      continue;
     }

     for(ii d : dirs4) {
       int nr = r + d.first;
       int nc = c + d.second;
       if(!in_grid(nr, nc)) continue;
        
       int new_energy = energy_left;
       if((grid[nr] & (1 << nc))) {
          new_energy--;
       } else {
         new_energy = k;
       }

       int& old_moves = move[nr][nc][new_energy];
       int new_moves_so_far = 1 + moves_so_far;
       if(new_moves_so_far < old_moves) {
         old_moves = new_moves_so_far;
         queue.push({nr, nc, new_energy, new_moves_so_far});  
       }
     }

  }
  
  return min_moves_required;
}

namespace algorithms::onlinejudge::advanced_topics::patrol_robot
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
          int k;
          int cell;
          std::cin >> N >> M >> k;
          vi grid(N);
          for(int r = 0; r < N; ++r) {
            int row = 0;
            for(int c = 0; c < M; ++c) {
              std::cin >> cell;
              if(cell == 1) {
                row |= (1 << c);
              }
            }
            grid[r] = row;
          }
          printf("%d\n", get_min_moves_required(grid, k));
        }
    }
}