/*
───────────────────────────────────────────────────────────────
🧳 https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/description/?envType=problem-list-v2&envId=backtracking, rt: s
───────────────────────────────────────────────────────────────
*/

// #include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




const int MAX = (int)1e9;

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;


int N, M;

bool is_occupied(int size, const vvi& occupied, const ii& p) {
    int r = p.first;
    int c = p.second;
    int N = occupied.size();
    int M = N > 0 ? occupied[0].size() : 0;

    // Check if the square exceeds grid boundaries
    if (r + size > N || c + size > M) {
        return true;
    }

    // Check for collisions inside the square
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (occupied[r + i][c + j] != 0) {
                return true;
            }
        }
    }

    return false;
}


// In-place modification: Marks cells as occupied
void place_square(int size, vvi& occupied, const ii& p) {
    int r = p.first;
    int c = p.second;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            occupied[r + i][c + j] = 1;
        }
    }
}

// In-place modification: Unmarks cells (Backtracks)
void unplace_square(int size, vvi& occupied, const ii& p) {
    int r = p.first;
    int c = p.second;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            occupied[r + i][c + j] = 0;
        }
    }
}


vii add_points(int size, const vii& points, const ii& p, const vvi& occupied) {
    int r = p.first;
    int c = p.second;
    int N = occupied.size();
    int M = N > 0 ? occupied[0].size() : 0;
    
    vii new_points;

    // 1. Remove existing points covered by the new square
    for (const auto& q : points) {
        int qr = q.first;
        int qc = q.second;

        if (qr >= r && qr < r + size && qc >= c && qc < c + size) {
            continue; // Exclude
        }
        new_points.push_back(q);
    }

    auto contains = [](const vii& pts, const ii& pt) {
        return std::find(pts.begin(), pts.end(), pt) != pts.end();
    };

    // 2. Add right candidate if within boundary and NOT a continuous vertical edge from above
    if (c + size < M) {
        bool is_vertical_continuation = false;
        if (r - 1 >= 0) {
            // If the cell to the left of the boundary above is occupied,
            // and the cell to the right of the boundary above is empty/out of bounds,
            // then this is a continuous straight vertical edge from above.
            bool left_above_occupied = (occupied[r - 1][c + size - 1] != 0);
            bool right_above_empty = (occupied[r - 1][c + size] == 0);
            if (left_above_occupied && right_above_empty) {
                is_vertical_continuation = true;
            }
        }

        if (!is_vertical_continuation) {
            ii right_candidate = {r, c + size};
            if (!contains(new_points, right_candidate)) {
                new_points.push_back(right_candidate);
            }
        }
    }

    // 3. Add bottom candidate if within boundary and NOT a continuous horizontal edge from the left
    if (r + size < N) {
        bool is_horizontal_continuation = false;
        if (c - 1 >= 0) {
            // If the cell above the boundary to the left is occupied,
            // and the cell below the boundary to the left is empty/out of bounds,
            // then this is a continuous straight horizontal edge from the left.
            bool above_left_occupied = (occupied[r + size - 1][c - 1] != 0);
            bool below_left_empty = (occupied[r + size][c - 1] == 0);
            if (above_left_occupied && below_left_empty) {
                is_horizontal_continuation = true;
            }
        }

        if (!is_horizontal_continuation) {
            ii bottom_candidate = {r + size, c};
            if (!contains(new_points, bottom_candidate)) {
                new_points.push_back(bottom_candidate);
            }
        }
    }

    // 4. Sort the points to maintain a consistent search order
    std::sort(new_points.begin(), new_points.end());

    return new_points;
}


void backtrack(int max_squares, vvi& occupied, const vii& insertion_points, int curr_squares, int& sol) {

  if(insertion_points.empty()) {
    sol = std::min(sol, curr_squares);
    return;
  }


  if(curr_squares + 1 >= sol) {
    return;
  }

  for(int square = max_squares; square >= 1; --square) {
    for(const auto& p : insertion_points) {
      if(!is_occupied(square, occupied, p)) {
        // 1. Place the square directly in the referenced grid
        place_square(square, occupied, p);
        
        // 2. Generate the next insertion points locally
        vii new_insertion_points = add_points(square, insertion_points, p, occupied);
        
        // 3. Recurse (passing grid by reference, and new points by reference)
        backtrack(max_squares, occupied, new_insertion_points, 1 + curr_squares, sol);
        
        // 4. Backtrack (restore the referenced grid for the next iteration)
        unplace_square(square, occupied, p);
      }
    }
  }
}

namespace algorithms::leetcode::backtracking::tiling_rectangle
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

        while(std::cin >> N >> M) {
          int max_squares = std::min(N, M);
          vvi occupied_cells(N, vi(M, 0));
          vii insertion_points = {{0, 0}};
          int sol = N * M;
          backtrack(max_squares, occupied_cells, insertion_points, 0, sol);
          std::cout << sol << std::endl;
        }
    }
}