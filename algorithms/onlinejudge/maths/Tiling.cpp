/*
───────────────────────────────────────────────────────────────
🧳 UVa 10359 Tiling, https://onlinejudge.org/external/103/10359.pdf, derive the formula, bigint, rt: s
  https://oeis.org/A001045: Jacobsthal sequence (or Jacobsthal numbers): a(n) = a(n-1) + 2*a(n-2), with a(0) = 0, a(1) = 1; also a(n) = nearest integer to 2^n/3.
───────────────────────────────────────────────────────────────
*/


#include "../debug.h"
#include "../../aux.h"
#include "utility/big_integer.cpp"
#include <bits/stdc++.h>



namespace bg = algorithms::onlinejudge::maths::utility::big_integer;

constexpr int ROWS = 2;
constexpr int MAX_DP = 252;

enum TileShape {
  DOMINO_1x2,
  DOMINO_2x1,
  SQUARE_2x2
};

std::array<TileShape, 3> tile_shapes = {DOMINO_1x2, DOMINO_2x1, SQUARE_2x2};

using vi = std::vector<int>;
using ull = unsigned long long;
using ll = long long;
using v_tile_shape = std::vector<TileShape>;
using v_bg = std::vector<bg::bigint>;



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

    case SQUARE_2x2:
    {
        // This tile occupies the 2x2 block starting at (r, c).
        // We only need to check the bottom-right corner to validate the whole placement.
        if (in_bounds(r + 1, c + 1, R, C)) {
          occupied_cells.push_back(r * C + c);            // Top-left (r, c)
          occupied_cells.push_back(r * C + (c + 1));      // Top-right (r, c+1)
          occupied_cells.push_back((r + 1) * C + c);      // Bottom-left (r+1, c)
          occupied_cells.push_back((r + 1) * C + (c + 1)); // Bottom-right (r+1, c+1)
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

namespace algorithms::onlinejudge::maths::tiling
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

        bg::bigint factor = bg::bigint(2);
        v_bg dp(MAX_DP + 1);
        dp[0] = bg::bigint(0);
        dp[1] = bg::bigint(1);
        for(int i = 2; i < MAX_DP; ++i) {
          dp[i] = dp[i - 1] + factor * dp[i - 2];
        }

        int c;
        while(scanf("%d", &c) == 1) {
          // Layout layout;
          // printf("%llu\n", backtrack(0, 0, ROWS, c, layout));
          printf("%s\n", dp[c + 1].getRawRep().c_str());
        } 
    }
}