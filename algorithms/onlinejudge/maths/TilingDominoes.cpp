/*
───────────────────────────────────────────────────────────────
🧳 UVa 11270 Tiling Dominoes, https://onlinejudge.org/external/112/11270.pdf, rt: s
───────────────────────────────────────────────────────────────
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