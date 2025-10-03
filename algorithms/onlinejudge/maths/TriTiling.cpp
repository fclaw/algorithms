/*
───────────────────────────────────────────────────────────────
🧳 UVa 10918 TriTiling, https://onlinejudge.org/external/109/10918.pdf, the approach is similar to 01224 (Tile Code), 
   https://github.com/fclaw/algorithms/commit/04be3ae9b89e097694db5f320eea91cf330ae0e3, rt: s
   https://oeis.org/A001835: a(n) = 4*a(n-1) - a(n-2), with a(0) = 1, a(1) = 1
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using ull = unsigned long long;
using ll = long long;
using vi = std::vector<int>;
using vull = std::vector<ull>;

constexpr int MAX_N = 30;


enum TileShape {
  DOMINO_1x2,
  DOMINO_2x1
};

std::array<TileShape, 2> tile_shapes = {DOMINO_1x2, DOMINO_2x1};

using v_tile_shape = std::vector<TileShape>;

struct Layout
{
    int domino_1x2 = 0;
    int domino_2x1 = 0;
    vi occupied_cells = {};
    v_tile_shape shape_sequence = {}; // The sequence of tiles placed, e.g., {V, S, V};
    // The comparison operator for use in std::set, std::map, etc.
    // It must be a const member function.
    bool operator < (const Layout& other) const {
      v_tile_shape this_shapes = this->shape_sequence;
      v_tile_shape other_shapes = other.shape_sequence;
      return this_shapes > other_shapes;
    }
};

bool is_cell_free(const Layout& layout, int cell) {
  return std::find(layout.occupied_cells.begin(), layout.occupied_cells.end(), cell) == layout.occupied_cells.end();
}

bool in_bounds(int x, int y, int R, int C) { return 0 <= x && x < R && 0 <= y && y < C; }


Layout save(const Layout& layout) {
    Layout new_layout;
    new_layout.domino_1x2 = layout.domino_1x2;
    new_layout.domino_2x1 = layout.domino_2x1;
    new_layout.occupied_cells = layout.occupied_cells;
    new_layout.shape_sequence = layout.shape_sequence;
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


ull backtrack(int start_cell, ll used, int R, int C, Layout& layout, std::set<Layout>& layouts) {
  if(__builtin_popcount(used) == R * C) {
    if(!layouts.count(layout)) {  
      layouts.insert(layout);
      return 1;
    } else return 0;
  }

  ull ways = 0;
  for(int c = start_cell; c < R * C; ++c) {
    if(is_cell_free(layout, c)) {
      for(TileShape shape : tile_shapes) {
        vi occupied_cells = place_tile(shape, c, R, C);
        if(!occupied_cells.empty()) {
          bool is_free = true;
          Layout prev_layout = save(layout);
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
            switch(shape) {
              case DOMINO_1x2: layout.domino_1x2++; break;
              case DOMINO_2x1: layout.domino_2x1++; break;
            }
            layout.shape_sequence.push_back(shape);
            ways += backtrack(c + 1, new_used, R, C, layout, layouts);
            layout = prev_layout;
          }
        }
      }
    }
  }
  return ways;
}


namespace algorithms::onlinejudge::maths::tri_tiling
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

       vull dp(MAX_N + 1);
       dp[0] = 1;
       dp[1] = 1;
       for(int i = 2; i <= MAX_N; ++i) {
         dp[i] = 4 * dp[i - 1] - dp[i - 2];
       }

       vull layouts(MAX_N + 1);
       layouts[0] = 1;
       int idx = 2;
       for(int i = 2; i <= MAX_N; i+= 2)
         layouts[i] = dp[idx++];

       int n;
       while(scanf("%d", &n) == 1 && n >= 0) {
         printf("%llu\n", layouts[n]);
       }
    }
}