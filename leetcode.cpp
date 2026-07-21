#include <bits/stdc++.h>




using vb = std::vector<bool>;
using vvb = std::vector<vb>;

int N, M;

// Checks if a square of a given size can fit at (r, c) without collisions
bool is_occupied(int size, const vvb& occupied, int r, int c) {
  if(r + size > N || 
     c + size > M) {
    return true;
  }

  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if(occupied[r + i][c + j]) {
        return true;
       }
    }
  }
  return false;
}

// Marks/unmarks cells as occupied (val = 1 to place, 0 to backtrack)
void update_grid(int size, vvb& occupied, int r, int c, bool is_occupied) {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      occupied[r + i][c + j] = is_occupied;
    }
  }
}

void backtrack(int max_squares, int r, int c, vvb& occupied, int curr_squares, int& sol) {
  // Base Case: Successfully tiled past the last row
  if(r == N) {
    sol = std::min(sol, curr_squares);
    return;
  }

  // Calculate the next sequential cell in row-major order (O(1))
  int next_r = (c + 1 == M) ? r + 1 : r;
  int next_c = (c + 1 == M) ? 0 : c + 1;

  // If the current cell is already covered, skip it
  if(occupied[r][c] != 0) {
    backtrack(max_squares, next_r, next_c, occupied, curr_squares, sol);
    return;
  }

  if(curr_squares + 1 >= sol) {
   return; 
  }

  // Try placing different square sizes at (r, c)
  for(int square = max_squares; square >= 1; --square) {
    if(r + square <= N && c + square <= M) {
      if(!is_occupied(square, occupied, r, c)) {
                    
        // Place the square
        update_grid(square, occupied, r, c, true);                
        // Next sequential point after placing this square
        int next_next_r = (c + square == M) ? r + 1 : r;
        int next_next_c = (c + square == M) ? 0 : c + square;
        // Recurse
        backtrack(max_squares, next_next_r, next_next_c, occupied, curr_squares + 1, sol);
        // Backtrack
        update_grid(square, occupied, r, c, false);
      }
    }
  }
}


int main(int argc, char* argv[])
{
    std::cin >> N >> M;
    vvb occupied(N, vb(M, false));
    int sol = N * M;
    backtrack(std::min(N, M), 0, 0, occupied, 0, sol);
    std::cout << sol << std::endl;
}