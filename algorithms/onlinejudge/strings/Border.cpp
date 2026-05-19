/*
───────────────────────────────────────────────────────────────
🧳 UVa 320 Border, https://onlinejudge.org/external/3/320.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


enum Direction { NORTH, EAST, SOUTH, WEST };


struct Move
{
    Direction dir;
    int dx;
    int dy;
};

using v_move = std::vector<Move>;
using v_dir = std::vector<Direction>;

v_move moves = {
    {NORTH,  0,  1}, // Moving up: Y increases by 1
    {EAST,   1,  0}, // Moving right: X increases by 1
    {SOUTH,  0, -1}, // Moving down: Y decreases by 1
    {WEST,  -1,  0}  // Moving left: X decreases by 1
};

Direction charToDir(char c) {
  if (c == 'N') return NORTH;
  if (c == 'E') return EAST;
  if (c == 'S') return SOUTH;
  return WEST; // Assuming valid input, fallback to 'W'
}

const int SIZE = 32;

struct State
{
    int x;
    int y;
    int idx;
};


void setBit(int x, int y, Direction d, std::vector<std::string>& board) {
    int sq_x = 0;
    int sq_y = 0;

    // 1. Determine the coordinates of the square's bottom-left corner
    // based on the "Right-Hand Rule"
    switch (d) {
        case EAST:  
            sq_x = x;     
            sq_y = y - 1; 
            break;
        case NORTH: 
            sq_x = x;     
            sq_y = y;     
            break;
        case WEST:  
            sq_x = x - 1; 
            sq_y = y;     
            break;
        case SOUTH: 
            sq_x = x - 1; 
            sq_y = y - 1; 
            break;
    }

    // 2. Translate Cartesian (Y goes up) to Array Index (Row goes down).
    // Cartesian Y=0 is the bottom row. In a size-32 array, the bottom row is index 31.
    int row = 31 - sq_y;
    int col = sq_x;

    // 3. Optional but highly recommended: simple bounds check to prevent segfaults
    if (row >= 0 && row < 32 && col >= 0 && col < 32) {
        board[row][col] = 'X';
    }
}


namespace algorithms::onlinejudge::strings::border
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

        int t_cases;
        int t_case = 1;
        bool is_first = true;
        scanf("%d", &t_cases);
        while(t_cases--) {
          
          if(is_first) is_first = false;
          else std::cout << std::endl;   

          int start_x;
          int start_y;
          scanf("%d %d", &start_x, &start_y);
          std::string s_path;
          std::cin >> s_path;
          s_path.pop_back();
          v_dir path;
          for(auto& c : s_path) {
            path.push_back(charToDir(c));
          }

          std::vector<std::string> board(SIZE + 1, std::string(SIZE, '.'));

          // init state
          int x = start_x;
          int y = start_y;
          int idx = 0;
          while(idx < (int)path.size()) {
            Direction next_dir = path[idx];
            for(auto& m : moves) {
              if(m.dir == next_dir) {
                int n_x = x + m.dx;
                int n_y = y + m.dy;
                setBit(x, y, m.dir, board);
                x = n_x;
                y = n_y;
                idx++;
              }
            }
          }

          printf("Bitmap #%d\n", t_case++);
          // Print from top (0) to bottom (31)
          for (int y = 0; y < 32; ++y) {
          // Note: Do NOT print spaces between characters!
          std::cout << board[y] << "\n"; 
          }
        }
    }
}