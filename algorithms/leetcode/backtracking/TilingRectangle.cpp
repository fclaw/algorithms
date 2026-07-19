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


bool is_occupied(int size, const vi& occupied, int p_idx) {
    int r = p_idx / M;
    int c = p_idx % M;

    // Check if the square exceeds grid boundaries
    if (r + size > N || c + size > M) {
        return true;
    }

    // Check for collisions inside the square
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int idx = (r + i) * M + (c + j);
            if (occupied[idx] != 0) {
                return true;
            }
        }
    }

    return false;
}

vi fill_in_occupied(int size, const vi& occupied, int p_idx) {
    vi new_occupied = occupied;
    int r = p_idx / M;
    int c = p_idx % M;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int idx = (r + i) * M + (c + j);
            new_occupied[idx] = 1; // Mark as occupied
        }
    }

    return new_occupied;
}


vi add_points(int size, const vi& points, int p_idx) {
    int r = p_idx / M;
    int c = p_idx % M;

    vi new_points;

    // 1. Remove existing points covered by the new square
    for (int q_idx : points) {
        int qr = q_idx / M;
        int qc = q_idx % M;

        if (qr >= r && qr < r + size && qc >= c && qc < c + size) {
            continue; // Exclude
        }
        new_points.push_back(q_idx);
    }

    // Helper lambda to check if point is already in the list
    auto contains = [](const vi& pts, int pt) {
        return std::find(pts.begin(), pts.end(), pt) != pts.end();
    };

    // 2. Add right candidate if within boundary
    if (c + size < M) {
        int right_idx = r * M + (c + size);
        if (!contains(new_points, right_idx)) {
            new_points.push_back(right_idx);
        }
    }

    // 3. Add bottom candidate if within boundary
    if (r + size < N) {
        int bottom_idx = (r + size) * M + c;
        if (!contains(new_points, bottom_idx)) {
            new_points.push_back(bottom_idx);
        }
    }

    // 4. Sorting 1D indices ascending naturally sorts them by row, then by column
    std::sort(new_points.begin(), new_points.end());

    return new_points;
}


int backtrack(int max_squares, const vi& occupied, const vi& insertion_points) {
    
    if (insertion_points.empty()) {
        return 0;
    }

    int ans = MAX;
    for (int square = 1; square <= max_squares; ++square) {
      for(int p_idx : insertion_points) {
        if (!is_occupied(square, occupied, p_idx)) {
          vi new_occupied = fill_in_occupied(square, occupied, p_idx);
          vi new_insertion_points = add_points(square, insertion_points, p_idx);      
          int curr_ans = backtrack(max_squares, new_occupied, new_insertion_points);
          ans = std::min(ans, 1 + curr_ans);
        }
      }
    }

    return ans;
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
          vi occupied_cells(N * M, 0);
          vi insertion_points = {0};
          std::cout << backtrack(max_squares, occupied_cells, insertion_points) << std::endl;
        }
    }
}