/*
───────────────────────────────────────────────────────────────
🧳 UVa 10500 Robot maps, https://onlinejudge.org/external/105/10500.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


enum Cell {Empty, Obstacle};

using v_cell = std::vector<Cell>;
using vv_cell = std::vector<v_cell>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using ii = std::pair<int, int>;
using vii = std::vector<ii>;

// NORTH: row - 1, EAST: col + 1, SOUTH: row + 1, WEST: col - 1
vii dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool check_bounds(int r, int c, int N, int M) {
  return r >= 0 && r < N && c >= 0 && c < M;
}

// Corrected 1D indexing: nr * M + nc (where M is width)
#define INDEX(N, r, c) ((r) * N  + (c))

void printWarehouse(int N, int M, const vii& empty_cells, const vii& obstacle_cells) {
    // 1. Initialize a temporary 2D char grid with '?'
    std::vector<std::vector<char>> grid(N, std::vector<char>(M, '?'));

    // 2. Map the sets back onto the grid
    // Based on your image: 'O' for empty, 'X' for obstacles
    for (auto const& p : empty_cells) {
        grid[p.first][p.second] = '0';
    }
    for (auto const& p : obstacle_cells) {
        grid[p.first][p.second] = 'X';
    }

    // 3. Construct the horizontal separator line: |---|---|...|
    std::string horizontal_border = "|";
    for (int j = 0; j < M; ++j) {
        horizontal_border += "---|";
    }

    // 4. Print the grid with ASCII borders
    for (int r = 0; r < N; ++r) {
        // Print the top border of the current row
        std::cout << horizontal_border << "\n";
        
        // Print the content line
        std::cout << "|";
        for (int c = 0; c < M; ++c) {
            std::cout << " " << grid[r][c] << " |";
        }
        std::cout << "\n";
    }
    
    // Print the absolute bottom border
    std::cout << horizontal_border << std::endl;
}

bool is_adjacent(const ii& a, const ii& b) {
  for(auto [dr, dc] : dir) {
    if(a.first + dr == b.first && 
       a.second + dc == b.second) {
      return true;
    }
  }
  return false;
}


void robotExplore(int r, int c, int N, int M, vvb& inspected, 
                  vii& empty_cells, vii& obstacle_cells, 
                  const vv_cell& layout, int& moves, ii& last_visted_cell) {
    

    // try making a move
    for(auto [dr, dc] : dir) {
      int nr = r + dr;
      int nc = c + dc;

      if(!check_bounds(nr, nc, N, M)) continue;


      // Read sensors in order: NORTH, EAST, SOUTH, WEST
      if(layout[nr][nc] == Obstacle) {
        obstacle_cells.push_back({nr, nc});
      } else {
        empty_cells.push_back({nr, nc});
      } 

      if(layout[nr][nc] == Empty && 
         !inspected[nr][nc] && 
         is_adjacent(last_visted_cell, {nr, nc})) {

        inspected[nr][nc] = true;
        // Physical Move: "Move to the first unvisited free cell"
        // This is the "Movement" the problem is likely counting.
        moves++;
        // Repeat the process from the new cell (Recursion)
        last_visted_cell = {nr, nc};
        robotExplore(nr, nc, N, M, inspected, empty_cells, obstacle_cells, layout, moves, last_visted_cell);
      }
    }
}


namespace algorithms::onlinejudge::strings::robot_maps
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

        // ..
        int N, M, start_r, start_c;
        while(scanf("%d %d", &N, &M) && N && M) {
          
          std::cout << std::endl;


          scanf("%d %d", &start_r, &start_c);
          --start_r;
          --start_c;
          vv_cell layout(N, v_cell(M, Empty));
          for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
              char c;
              scanf(" %c", &c);
              if(c == 'X') {
                layout[i][j] = Obstacle;
              }
            }
          }

          vvb inspected(N, vb(M, false));
          inspected[start_r][start_c] = true;
          vii empty_cells;
          empty_cells.push_back({start_r, start_c});
          vii obstacle_cells;
          int moves = 0;
          ii last_visted_cell = {start_r, start_c};
          robotExplore(start_r, start_c, N, M, inspected, empty_cells, obstacle_cells, layout, moves, last_visted_cell);
          
          // print warehouse
          printWarehouse(N, M, empty_cells, obstacle_cells);
          printf("\nNUMBER OF MOVEMENTS: %d\n", moves);
        }
    }
}