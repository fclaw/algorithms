/*
───────────────────────────────────────────────────────────────
🧳 Protecting the Collection, https://open.kattis.com/problems/protectingthecollection, rt: s
───────────────────────────────────────────────────────────────
*/


#include "../../onlinejudge/debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vvvvi = std::vector<vvvi>;


// 1. Cardinal Directions (Clockwise: 0, 1, 2, 3)
enum Dir { 
    NORTH = 0, 
    EAST  = 1, 
    SOUTH = 2, 
    WEST  = 3 
};

// 2. Mirror Orientations
enum Mirror_Orientation {
    NONE  = 0, // '.' Empty floor
    NW_SE = 1, // '\' Mirror running from North-West to South-East
    NE_SW = 2  // '/' Mirror running from North-East to South-West
};

/**
 * Returns the new direction after reflecting off a mirror.
 */
inline Dir reflect(Dir d, Mirror_Orientation m) {
    if (m == NE_SW) { // '/' Mirror
        switch (d) {
            case NORTH: return EAST;
            case EAST:  return NORTH;
            case SOUTH: return WEST;
            case WEST:  return SOUTH;
        }
    } else if (m == NW_SE) { // '\' Mirror
        switch (d) {
            case NORTH: return WEST;
            case WEST:  return NORTH;
            case SOUTH: return EAST;
            case EAST:  return SOUTH;
        }
    }
    return d; // No mirror (passes straight through)
}

Mirror_Orientation char_to_mirror(char c) {
    if (c == '/')  return NE_SW;
    if (c == '\\') return NW_SE;
    return NONE;
}


const std::vector<ii> dir_to_vec = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool in_room(int r, int c, int N) { return r >= 0 && r < N && c >= 0 && c < N; };


using vmo = std::vector<Mirror_Orientation>;
using vvmo = std::vector<vmo>;


// 0: Unvisited (-1), 1: Visiting/False (Cycle Guard), 2: Solved True
// Flat array or static memory for 2000x2000:
// State index = (((r * N + c) * 4 + dir) * 2) + has_aux_mirror
int8_t cache[2005][2005][4][2];

bool can_laser_reach_sensor(ii cell, Dir dir, bool has_aux_mirror, int target_row, const vvmo& room, int N);

bool step_forward(int curr_r, int curr_c, Dir curr_dir, bool aux_used, int N, int target_row, const vvmo& room) {
  ii vec = dir_to_vec[curr_dir];
  int nr = curr_r + vec.first;
  int nc = curr_c + vec.second;

  // CHECK SENSOR HIT: Exits through East wall at target_row moving EAST!
  if (curr_dir == EAST && 
      curr_r == target_row && 
      nc == N) {
    return true;
  }

  // Hit outer room walls without hitting sensor
  if (!in_room(nr, nc, N)) {
    return false;
  }

  return can_laser_reach_sensor({nr, nc}, curr_dir, aux_used, target_row, room, N);
}

bool can_laser_reach_sensor(ii cell, Dir dir, bool has_aux_mirror, int target_row, const vvmo& room, int N) {

  int r = cell.first;
  int c = cell.second;

  if(~cache[r][c][dir][has_aux_mirror]) {
    return cache[r][c][dir][has_aux_mirror] == 1;
  }

  // Mark as 0 (visiting / assumed false) to break any infinite mirror cycles!
  cache[r][c][dir][has_aux_mirror] = 0;


  Mirror_Orientation m = room[r][c];
  // ==========================================
  // CASE 1: Cell already has an existing mirror
  // ==========================================
  if(m) {
    Dir new_dir = reflect(dir, m);
    if(step_forward(r, c, new_dir, has_aux_mirror, N, target_row, room)) {
      return (cache[r][c][dir][has_aux_mirror] = 1);
    }
  // ==========================================
  // CASE 2: Empty floor '.'
  // ==========================================
  } else {
  
    // Option A: Just pass straight through without adding a mirror
    if(step_forward(r, c, dir, has_aux_mirror, N, target_row, room)) {
      return (cache[r][c][dir][has_aux_mirror] = 1);
    }

     // Option B: Install a new mirror (only if we haven't used our 1 mirror yet!)
    if(!has_aux_mirror) {
       // Try installing '\' (NW_SE)
      Dir dir_backslash = reflect(dir, NW_SE);
      if (step_forward(r, c, dir_backslash, true, N, target_row, room)) {
        return (cache[r][c][dir][has_aux_mirror] = 1);
      }

      // Try installing '/' (NE_SW)
      Dir dir_slash = reflect(dir, NE_SW);
      if (step_forward(r, c, dir_slash, true, N, target_row, room)) {
        return (cache[r][c][dir][has_aux_mirror] = 1);
      }
    }
  }

  return (cache[r][c][dir][has_aux_mirror] = 0);
}


namespace algorithms::kattis::dp::protecting_collection
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

        int N, c, r;
        while(while_read(N, c, r)) {
          --r; --c;
          char cell;
          vvmo room(N, vmo(N, NONE));
          for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
              std::cin >> cell;
              room[i][j] = char_to_mirror(cell);
            }
          }
          ii start = {0, c};
          std::memset(cache, -1, sizeof cache);
          printf("%s\n", can_laser_reach_sensor(start, SOUTH, false, r, room, N) ? "YES" : "NO"); 
        }
    }
}