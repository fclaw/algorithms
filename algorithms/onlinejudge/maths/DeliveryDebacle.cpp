/*
───────────────────────────────────────────────────────────────
🧳 UVa 11310 Delivery Debacle, https://onlinejudge.org/external/113/11310.pdf, rt: s
   https://oeis.org/A127864, Number of tilings of a 2 X n board with 1 X 1 and L-shaped tiles (where the L-shaped tiles cover 3 squares).
───────────────────────────────────────────────────────────────
1 -> 1
2 -> 5
3 -> 11
4 -> 33
5 -> 87
6 -> 241
7 -> 655
8 -> 1793
a(n) = a(n-1) + 4*a(n-2) + 2*a(n-3)
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int R = 2;
constexpr int MAX_ROW = 40;


using ull = unsigned long long;
using vll = std::vector<ull>;
using vi = std::vector<int>;
using vii = std::vector<vi>;
using vvii = std::vector<vii>;
using ull = unsigned long long;

// Using a type alias for clarity
using Point = std::pair<int, int>;
using Orthogonals = std::array<Point, 2>;
using DirectionInfo = std::pair<Point, Orthogonals>;


std::array<DirectionInfo, 4> directions = {{
  // Index 0: UP
  { {-1, 0}, { { {0, -1}, {0, 1} } } }, // Orthogonals: Left, Right
  // Index 1: DOWN
  { {1, 0},  { { {0, 1}, {0, -1} } } }, // Orthogonals: Right, Left
  // Index 2: LEFT
  { {0, -1}, { { {-1, 0}, {1, 0} } } }, // Orthogonals: Up, Down
  // Index 3: RIGHT
  { {0, 1},  { { {1, 0}, {-1, 0} } } }  // Orthogonals: Down, Up
}};

bool in_bounds(int r, int c, int R, int C) {
  return r >= 0 && r < R && c >= 0 && c < C;
}


vii make_lshapes(int idx, int R, int C) {
  vii lshapes;

  // 1. Correctly convert the 1D index to 2D coordinates
  int r = idx / C;
  int c = idx % C;

  // Iterate through the 4 primary directions (Up, Down, Left, Right)
  for(const auto& dir_info : directions) {
    Point primary_dir = dir_info.first;
        
    // 2. Calculate the "center" or "corner" of the L-shape
    int center_r = r + primary_dir.first;
    int center_c = c + primary_dir.second;

    // Check if the center point is within the grid bounds
    if(!in_bounds(center_r, center_c, R, C))
      continue; // This L-shape is invalid, try the next primary direction
        
    // At this point, we have a valid 2-cell line: (r,c) -> (center_r, center_c)
    // Now, we need to add the third point by branching off the center point.
    Orthogonals perpendicular_dirs = dir_info.second;
        
    // 3. Iterate through the two perpendicular directions to form the L
    for(const auto& perp_dir : perpendicular_dirs) {
      int end_r = center_r + perp_dir.first;
      int end_c = center_c + perp_dir.second;
            
      // Check if the third point is also in bounds
      if(in_bounds(end_r, end_c, R, C)) {
      // If all three points are valid, create the L-shape
        vi lshape;
        lshape.push_back(idx);                      // Original point
        lshape.push_back(center_r * C + center_c);  // Center point
        lshape.push_back(end_r * C + end_c);        // End point        
        lshapes.push_back(lshape);
      }
    }
  }
  return lshapes;
}


bool is_free(int idx, const vii& shapes) {
    for(const auto& shape : shapes) {
        if(std::find(shape.begin(), shape.end(), idx) != shape.end()) {
          return false;
        }
    }
    return true;
}

bool is_unique_solution(const vii& shapes, const vvii& solutions) {
  vii tmp = shapes;
  for(auto& shape : tmp) std::sort(shape.begin(), shape.end());
  std::sort(tmp.begin(), tmp.end());
  for(const auto& sol : solutions) {
    if(tmp == sol) return false;
  }
  return true;
}


ull backtrack(int idx, int R, int C, int used, vii& shapes, vvii& solutions) {
  if(__builtin_popcount(used) == R * C) {
    if(is_unique_solution(shapes, solutions)) {
      for(auto& shape : shapes)
        std::sort(shape.begin(), shape.end());
      std::sort(shapes.begin(), shapes.end());
      solutions.push_back(shapes);
      return 1;
    } else return 0;
  }

  ull ways = 0;
  for(int i = idx; i < R * C; i++) {
    if(!is_free(i, shapes)) continue;
    vii cakes = make_lshapes(i, R, C);
    cakes.insert(cakes.begin(), vi{i});
    for(auto& cake : cakes) {
      bool is_valid = true;
      for(int p : cake) {
        if(!is_free(p, shapes)) {
          is_valid = false;
          break;
        }
      }
      if(!is_valid) continue;
      int new_used = used;
      for(int p : cake) new_used |= (1 << p);
      shapes.push_back(cake);
      ways += backtrack(i + 1, R, C, new_used, shapes, solutions);
      shapes.pop_back(); 
    }
  }
  return ways;
}


namespace algorithms::onlinejudge::maths::delivery_debacle
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

        vll dp(MAX_ROW + 1);
        for(int i = 1; i <= 3; ++i) {
          vii shapes;
          vvii solutions;
          dp[i] = backtrack(0, R, i, 0, shapes, solutions);
        }
        for(int i = 4; i <= MAX_ROW; i++) {
          dp[i] = dp[i - 1] + 4 * dp[i - 2] + 2 * dp[i - 3];
        }

        int t_cases;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int C;
          scanf("%d", &C);
          printf("%llu\n", dp[C]);
        }
    }
}