/*
───────────────────────────────────────────────────────────────
🧳 UVa 11270 Tiling Dominoes, https://onlinejudge.org/external/112/11270.pdf, rt: s
───────────────────────────────────────────────────────────────
 * --- Problem Analysis for UVa 11270 - Tiling Dominoes ---
 *
 * STATUS: Not solved yet. This problem has been identified as requiring advanced
 * techniques beyond standard DP, and has been "put on ice" pending further study.
 * This comment documents the investigation and the path to a future solution.
 *
 * --- THE PROBLEM ---
 * The goal is to count the number of ways to perfectly tile a general m x n grid
 * with 2x1 dominoes. The constraints (m, n <= 100) make this a computationally
 * hard problem.
 *
 * --- PHASE 1: ATTEMPTED STRATEGIES & WHY THEY FAILED ---
 *
 * 1.  INITIAL HYPOTHESIS: Discover a sequence via backtracking.
 *     - A backtracking solver was written to exhaustively find all tilings for
 *       small grids (e.g., 2x2, 2x4, 4x4).
 *     - RESULT: The backtracking was astronomically slow. It could only solve
 *       trivial cases (like 2x2=2, 4x4=36) and timed out indefinitely for anything
 *       larger, like 6x6.
 *     - CONCLUSION: It is computationally infeasible to generate a sequence long
 *       enough to be uniquely identified by the OEIS using this method. The standard
 *       "discover, identify, optimize" pipeline is defeated.
 *
 * 2.  SECOND HYPOTHESIS: Divide and Conquer.
 *     - An attempt was made to solve a 4x4 grid by breaking it into two 2x4 subproblems.
 *     - The number of ways to tile a 4x4 is 36. The number for a 2x4 is 5.
 *     - `5 * 5 = 25`, which is not 36.
 *     - CONCLUSION: The subproblems are not independent. Vertical dominoes can cross
 *       the boundary between the subgrids, creating "interlocking" tilings that a
 *       simple multiplication cannot account for.
 *
 * --- PHASE 2: IDENTIFYING THE TRUE NATURE OF THE PROBLEM ---
 *
 * This problem is a well-known, difficult challenge in both combinatorics and
 * computer science. It belongs to a specific class of "Advanced DP".
 *
 * 1.  THE CORRECT TECHNIQUE: Dynamic Programming with Profile (or "Broken Profile DP").
 *     - The flaw in simple DP is that `dp[i][j]` doesn't carry enough information.
 *       The solution for a column depends on how tiles from the *previous* column
 *       are protruding into the *current* column.
 *     - The state must therefore encode the "profile" of the boundary between the
 *       tiled and untiled sections of the grid.
 *
 * 2.  THE DP STATE: `dp[column][mask]`
 *     - `column`: The current column we are trying to tile.
 *     - `mask`: A bitmask of length 'm' (number of rows). The i-th bit is 1 if the
 *       cell (i, column) is already occupied by a horizontal domino from the
 *       previous column, and 0 otherwise.
 *
 * 3.  THE TRANSITIONS:
 *     - The transitions are complex. A recursive helper function is needed to fill
 *       the current column, row by row. It must respect the incoming 'mask' and
 *       generate the 'mask' for the next column based on the placement of new
 *       horizontal dominoes.
 *
 * --- PHASE 3: THE PATH FORWARD ---
 *
 * This problem is being set aside until the prerequisite techniques are mastered.
 *
 * 1.  PREREQUISITE: Master standard "DP with Bitmask" problems.
 *     - Problems like UVa 10911 (Forming Quiz Teams) teach the fundamentals of using
 *       a bitmask to represent a subset and writing the recursive transitions.
 *
 * 2.  NEXT STEP: Study "Profile DP" tutorials.
 *     - Once standard bitmask DP is comfortable, specific tutorials on tiling
 *       problems with profile DP can be studied to understand the state representation
 *       and the complex recursive transitions.
 *
 * 3.  THE MATHEMATICAL CONTEXT (For curiosity):
 *     - The closed-form solution is known as the Kasteleyn formula, which involves
 *       multiplying eigenvalues of the graph's adjacency matrix and is related to
 *       calculating the Pfaffian. This is graduate-level mathematics and is not
 *       the intended solution path for a programming contest. The intended path is
 *       the Profile DP.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



enum TileShape {
  DOMINO_1x2,
  DOMINO_2x1
};

std::array<TileShape, 2> tile_shapes = {DOMINO_1x2, DOMINO_2x1};

using vi = std::vector<int>;
using ull = unsigned long long;
using ll = long long;
using v_tile_shape = std::vector<TileShape>;


struct Layout { vi occupied_cells = {}; };


bool is_cell_free(const Layout& layout, int cell) {
  return std::find(layout.occupied_cells.begin(), layout.occupied_cells.end(), cell) == layout.occupied_cells.end();
}

void rollback(vi& occupied_cells, vi& new_occupied_cells) {
  while(!new_occupied_cells.empty()) {
    int cell = occupied_cells.back();
    occupied_cells.pop_back();
    std::erase(new_occupied_cells, cell);
  }
}


bool in_bounds(int x, int y, int R, int C) { return 0 <= x && x < R && 0 <= y && y < C; }


Layout save(const Layout& layout) {
    Layout new_layout;
    new_layout.occupied_cells = layout.occupied_cells;
    return new_layout;
}

vi place_tile(TileShape shape, int cell, int R, int C) {
  // Convert the 1D index 'cell' to 2D (row, column) coordinates.
  int r = cell / C; // The row of the top-left corner
  int c = cell % C; // The column of the top-left corner
  vi occupied_cells;

  switch (shape) {
    case DOMINO_1x2: // Vertical Domino (1 column wide, 2 rows tall)
    {
        // This tile occupies cells (r, c) and (r+1, c).
        if (in_bounds(r + 1, c, R, C)) {
          occupied_cells.push_back(r * C + c);        // Cell at (r, c)
          occupied_cells.push_back((r + 1) * C + c);  // Cell at (r+1, c)
        }
        break;
    }

    case DOMINO_2x1: // Horizontal Domino (2 columns wide, 1 row tall)
    {
        // This tile occupies cells (r, c) and (r, c+1).
        if (in_bounds(r, c + 1, R, C)) {
          occupied_cells.push_back(r * C + c);        // Cell at (r, c)
          occupied_cells.push_back(r * C + (c + 1));  // Cell at (r, c+1)
        }
        break;
    }
  }
  return occupied_cells; // Will be empty if the tile placement was out of bounds
}


ull backtrack(int start_cell, ll used, int R, int C, Layout& layout) {
  if(__builtin_popcountll(used) == (ll)(R * C)) {
    return 1;
  }

  ull ways = 0;
  for(int c = start_cell; c < R * C; ++c) {
    if(is_cell_free(layout, c)) {
      for(TileShape shape : tile_shapes) {
        vi occupied_cells = place_tile(shape, c, R, C);
        if(!occupied_cells.empty()) {
          bool is_free = true;
          ll new_used = used;
          for(int cell : occupied_cells) {
            if(is_cell_free(layout, cell)) {
              layout.occupied_cells.push_back(cell);
              new_used |= (1LL << cell);
            } else {
              is_free = false;
              break;
            }
          }
          if(is_free) {
            ways += backtrack(c + 1, new_used, R, C, layout);
            rollback(layout.occupied_cells, occupied_cells);
          }
        }
      }
    }
  }
  return ways;
}

namespace algorithms::onlinejudge::maths::tiling_dominoes
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


        int r, c;
        while(scanf("%d %d", &r, &c) == 2) {
          Layout layout;
          printf("%llu\n", backtrack(0, 0, r, c, layout));
        } 
    }
}