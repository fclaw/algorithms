/*
───────────────────────────────────────────────────────────────
🧳 UVa 928 Eternal Truths, https://onlinejudge.org/external/9/928.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>

 

using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using vvvb = std::vector<vvb>;


// { {delta_row, delta_col}, Direction }
const vii
  dirs4 = {
    {-1,  0}, // Row - 1 (Up)
    { 0,  1}, // Col + 1 (Right)
    { 1,  0}, // Row + 1 (Down)
    { 0, -1}  // Col - 1 (Left)
  };



// The ritual step length cycle: 1 -> 2 -> 3 -> 1 -> 2 -> 3...
// Stored as 0-indexed (0 = Jump 1, 1 = Jump 2, 2 = Jump 3)
enum Step { ONE = 0, TWO = 1, THREE = 2 };

struct State
{
    /**
     * 1. row & 2. col (Spatial Position)
     * -----------------------------------
     * The current 2D cell coordinates (r, c) on the maze grid.
     * Range: 0 <= row < R, 0 <= col < C.
     */
    int row;
    int col;

    /**
     * 3. step (Current Ritual Jump Size)
     * ----------------------------------
     * Indicates the length of the NEXT move that MUST be taken:
     *   - ONE   (0): Must jump exactly 1 chamber in a straight line.
     *   - TWO   (1): Must jump exactly 2 chambers in a straight line.
     *   - THREE (2): Must jump exactly 3 chambers in a straight line.
     * 
     * Next step length transitions cyclically: 
     *   next_step = static_cast<Step>((curr.step + 1) % 3);
     */
    Step step;

    /**
     * 4. moves / distance (Cost function g(n))
     * ----------------------------------------
     * The total number of jumps/moves taken from the Start (S) to reach this state.
     * In an unweighted BFS, each jump (whether of size 1, 2, or 3) counts as +1 move.
     */
    int moves;

    /**
     * ⚠️ OPTIONAL FIELD: direction
     * ----------------------------
     * In this problem, direction is STATELESS between moves because:
     *   - Once you land on a cell, you can freely pick ANY of the 4 directions 
     *     for your next move.
     *   - Facing direction does NOT carry over to restrict future turns.
     * Therefore, 'direction' does NOT need to be stored in the visited table!
     */
    // Direction direction; // Not strictly needed in the state space
};

int R, C;

bool in_grid(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }

bool is_move_allowed(int s_row, int s_col, int e_row, int e_col, const std::unordered_set<ii>& walls) {
// 1. Must be in a straight line (cannot move diagonally)
    if (s_row != e_row && s_col != e_col) {
        return false;
    }

    // 2. Compute unit step direction: -1, 0, or +1
    int dr = (e_row > s_row) - (e_row < s_row);
    int dc = (e_col > s_col) - (e_col < s_col);

    int curr_r = s_row;
    int curr_c = s_col;

    // 3. Walk step-by-step from start to destination
    while (curr_r != e_row || curr_c != e_col) {
        curr_r += dr;
        curr_c += dc;

        // Bounds check
        if (curr_r < 0 || curr_r >= R || curr_c < 0 || curr_c >= C) {
            return false;
        }

        // Wall check (cannot jump through or land on walls)
        if (walls.count({curr_r, curr_c})) {
            return false;
        }
    }

    return true; // All chambers along the path are clean!
}


std::string get_min_moves_required(const std::unordered_set<ii>& walls, ii start, ii end) {

  std::queue<State> queue;
  vvvb visited(R + 1, vvb(C + 1, vb(3, false)));
  queue.push({start.first, start.second, ONE, 0});
  visited[start.first][start.second][ONE] = true;
  int min_moves = INT32_MAX;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int row = state.row;
    int col = state.col;
    Step step = state.step;
    int moves = state.moves;
    int coeff = static_cast<int>(step) + 1;
    
    if(row == end.first && 
       col == end.second) {
      min_moves = std::min(min_moves, moves);
      continue;
    }

    for(ii d : dirs4) {
      int nr = row + d.first * coeff;
      int nc = col + d.second * coeff;
      if(is_move_allowed(row, col, nr, nc, walls)) {
        Step nstep = static_cast<Step>((step + 1) % 3);
        if(!visited[nr][nc][nstep]) {
          State new_state = {nr, nc, nstep, moves + 1};
          visited[nr][nc][nstep] = true;
          queue.push(new_state);
        }
      }
    }
  }


  std::string ans;
  if(min_moves == INT32_MAX) {
    ans = "NO";
  } else {
    ans = std::to_string(min_moves);
  }
  return ans;
}

namespace algorithms::onlinejudge::advanced_topics::eternal_truths
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
          std::cin >> R >> C;
          ii start, end;
          char el;
          std::unordered_set<ii> walls;
          for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
              std::cin >> el;
              if(el == 'S') {
                 start = {r, c};
              } else if(el == 'E') {
                end = {r, c};
              } else if(el == '#') {
                walls.insert({r, c});
              }
            }
          }
          printf("%s\n", get_min_moves_required(walls, start, end).c_str());
        }
    }
}
