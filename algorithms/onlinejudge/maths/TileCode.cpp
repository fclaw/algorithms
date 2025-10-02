/*
───────────────────────────────────────────────────────────────
🧳 UVa 1224 Tile Code, derive formula from small instances, https://onlinejudge.org/external/12/1224.pd, rt: s
   https://oeis.org/A090597, a(n) = -a(n-1) + 5(a(n-2) + a(n-3)) - 2(a(n-4) + a(n-5)) - 8(a(n-6) + a(n-7))
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;
using vi = std::vector<int>;
using vull = std::vector<ull>;

constexpr int MAX_N = 30;


enum TileShape {
  DOMINO_1x2,
  DOMINO_2x1,
  SQUARE_2x2
};

using v_tile_shape = std::vector<TileShape>;

struct Layout
{
    int domino_1x2 = 0;
    int domino_2x1 = 0;
    int square_2x2 = 0;
    vi occupied_cells;
    v_tile_shape shape_sequence; // The sequence of tiles placed, e.g., {V, S, V};
    // The comparison operator for use in std::set, std::map, etc.
    // It must be a const member function.
    bool operator < (const Layout& other) const {
      vi sorted_this_cells = this->occupied_cells;
      vi sorted_other_cells = other.occupied_cells;
      v_tile_shape this_shapes = this->shape_sequence;
      v_tile_shape other_shapes = other.shape_sequence;
      std::sort(sorted_this_cells.begin(), sorted_this_cells.end());
      std::sort(sorted_other_cells.begin(), sorted_other_cells.end());
      // std::tie creates a tuple of references to the members.
      // The comparison is then done lexicographically on these tuples.
      // The order of members inside std::tie defines the comparison priority.
      // std::vector already knows how to compare itself lexicographically,
      // so this works seamlessly.
      auto lhs = std::tie(domino_1x2, domino_2x1, square_2x2, sorted_this_cells, this_shapes);
      auto rhs = std::tie(other.domino_1x2, other.domino_2x1, other.square_2x2, sorted_other_cells, other_shapes);
      return lhs > rhs;
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
    new_layout.square_2x2 = layout.square_2x2;
    new_layout.occupied_cells = layout.occupied_cells;
    new_layout.shape_sequence = layout.shape_sequence;
    return new_layout;
}


bool is_mirrored_helper(const Layout& layout_A, const Layout& layout_B) {
  if(layout_A.shape_sequence.size() != layout_B.shape_sequence.size()) {
    return false;
  }

  // Create a reversed copy of A's shape sequence.
  v_tile_shape reversed_A_seq = layout_A.shape_sequence;
  std::reverse(reversed_A_seq.begin(), reversed_A_seq.end());

  // Check if the reversed sequence is identical to B's sequence.
  return reversed_A_seq == layout_B.shape_sequence;
}

bool is_mirrored(const Layout& layout, const std::set<Layout>& layouts) {
  bool is_mirrored = false;
  for(const Layout& other : layouts)
    is_mirrored |= is_mirrored_helper(layout, other);
  return is_mirrored;
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


// The helper function from before
int get_next_column_major_index(int current_idx, int R, int C) {
  // Note: This function needs to handle the starting condition.
  // If current_idx is -1, it should return the first cell's index.
  if (current_idx < 0) {
    return 0; // The first cell is always (0,0) -> index 0
  }

  int r = current_idx / C;
  int c = current_idx % C;
  r++;
  if (r >= R) {
    r = 0;
    c++;
  }
  if (c >= C) {
    return -1; // End condition
  }
  return r * C + c;
}


ull backtrack(int start_cell, int used, int R, int C, Layout& layout, std::set<Layout>& layouts) {
  if(__builtin_popcount(used) == R * C) {
    if(!layouts.count(layout) &&
       !is_mirrored(layout, layouts)) {
      layouts.insert(layout);
      return 1;
    } else return 0;
  }

  ull ways = 0;
  for(int c = start_cell; c != -1; c = get_next_column_major_index(c, R, C)) {
    if(is_cell_free(layout, c)) {
      for(TileShape shape : {DOMINO_1x2, DOMINO_2x1, SQUARE_2x2}) {
        vi occupied_cells = place_tile(shape, c, R, C);
        if(!occupied_cells.empty()) {
          bool is_free = true;
          Layout prev_layout = save(layout);
          int new_used = used;
          for(int cell : occupied_cells) {
            if(is_cell_free(layout, cell)) {
              layout.occupied_cells.push_back(cell);
              new_used |= (1 << cell);
            } else {
              is_free = false;
              break;
            }
          }
          if(is_free) {
            switch(shape) {
              case DOMINO_1x2: layout.domino_1x2++; break;
              case DOMINO_2x1: layout.domino_2x1++; break;
              case SQUARE_2x2: layout.square_2x2++; break;
            }
            layout.shape_sequence.push_back(shape);
            ways += backtrack(get_next_column_major_index(c, R, C), new_used, R, C, layout, layouts);
            layout = prev_layout;
          }
        }
      }
    }
  }
  return ways;
}


namespace algorithms::onlinejudge::maths::tile_code
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
        for(int i = 2; i <= 7; i++) {
          std::set<Layout> layouts;
          Layout layout;
          dp[i] = backtrack(0, 0, 2, i, layout, layouts);
        }

        for(int i = 8; i <= MAX_N; i++)
          dp[i] = -dp[i - 1] + 5 * (dp[i - 2] + dp[i - 3]) - 2 * (dp[i - 4] + dp[i - 5]) - 8 * (dp[i - 6] + dp[i - 7]);

        int n, t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          scanf("%d", &n);
          printf("%llu\n", dp[n]);
        }
    }
}