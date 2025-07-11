/*
───────────────────────────────────────────────────────────────
🧳 UVa 633 A Chess Knight, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <set>
#include <queue>
#include <array>



constexpr int M = 3;

using pii = std::pair<int, int>;
using vpii = std::vector<pii>;
using vab = std::vector<std::array<bool, M>>;
using vvab = std::vector<vab>;


enum Move { Knight, Bishop, Teleport };

struct State
{
    pii pos;
    Move move;
    int moves;
};


bool in_board(int r, int c, int N) { return r >= 1 && r <= N && c >= 1 && c <= N; }

vpii makeKnightMoves(
  const pii& pos, 
  int N, 
  const std::set<pii>& obstacles) {
  vpii moves;
  const int dy[8] = { -2, -1, 1, 2,  2,  1, -1, -2 };
  const int dx[8] = {  1,  2, 2, 1, -1, -2, -2, -1 };
  for(int i = 0; i < 8; ++i) {
    int ny = pos.first + dy[i];
    int nx = pos.second + dx[i];
    if(in_board(ny, nx, N) && 
       !obstacles.count({ny, nx})) {
        moves.push_back({ny, nx});
    }
  }
  return moves; 
}

vpii makeBishopMoves(
  const pii& pos, 
  int N, 
  const std::set<pii>& obstacles) {
  vpii moves;
  const int factor = 2;
  const int dy[4] = { 1,  1, -1, -1 };
  const int dx[4] = { -1, 1,  1, -1 };
  for(int i = 0; i < 4; ++i) {
    int ny = pos.first + factor * dy[i];
    int nx = pos.second + factor * dx[i];
    if(in_board(ny, nx, N) && 
       !obstacles.count({ny, nx})) {
        moves.push_back({ny, nx});
    }
  }
  return moves;
}

vpii makeTeleportMoves(
  const pii& pos, 
  int N, 
  const std::set<pii>& obstacles) {
  vpii moves;
  int x = pos.second;
  int y = pos.first;

  // The formula for mirror reflection across an axis is:
  // new_coord = (size + 1) - old_coord
  // For a board from 1 to 2N, this is (2N + 1) - old_coord.
  int reflection_sum = N + 1;

  // 1. Calculate teleportation across the vertical axis of symmetry.
  //  The y-coordinate remains the same.
  int teleport_x = reflection_sum - x;
  pii vertical_teleport_dest = {y, teleport_x};
  if(in_board(y, teleport_x, N) && 
     !obstacles.count(vertical_teleport_dest)) {
    moves.push_back(vertical_teleport_dest);
  }

  // 2. Calculate teleportation across the horizontal axis of symmetry.
  // The x-coordinate remains the same.
  int teleport_y = reflection_sum - y;
  pii horizontal_teleport_dest = {teleport_y, x};
  if(in_board(teleport_y, x, N) && 
     !obstacles.count(horizontal_teleport_dest)) {
    moves.push_back(horizontal_teleport_dest);
  }

  return moves;
}


namespace algorithms::onlinejudge::graph::dynamic_knight
{
    /** https://onlinejudge.org/external/6/633.pdf */
    int N;
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while(while_read(N) && N) {
          N *= 2;
          pii start, end;
          while_read(start);
          while_read(end);
          pii obs;
          std::set<pii> obstacles;
          while(while_read(obs) && 
                obs.first && 
                obs.second) {
            obstacles.insert(obs);
          }
           
          int min_moves = -1;
          vvab visited(N + 1, vab(N + 1, {false, false, false}));
          std::queue<State> queue;
          
          // The first move can be of any type. Add all three possibilities to the queue.
          // Note: We don't have a "previous move" for the first step.
          // We can model this by saying the first move brings us TO the start square.
          // A simpler way is to handle the first move generation separately.

          // Generate all possible FIRST moves from 'start' position
          vpii knight_destinations = makeKnightMoves(start, N, obstacles);
          vpii bishop_destinations = makeBishopMoves(start, N, obstacles);
          vpii teleport_destinations = makeTeleportMoves(start, N, obstacles);

          // Add initial states for a Knight move
          for(const auto& dest : knight_destinations) {
            if(!visited[dest.first][dest.second][Knight]) {
              visited[dest.first][dest.second][Knight] = true;
              queue.push({dest, Knight, 1}); // This is the 1st move
            }
          }
          // Add initial states for a Bishop move
          for(const auto& dest : bishop_destinations) {
            if(!visited[dest.first][dest.second][Bishop]) {
              visited[dest.first][dest.second][Bishop] = true;
              queue.push({dest, Bishop, 1});
            }
          }
          // Add initial states for a Teleport move
          for(const auto& dest : teleport_destinations) {
            if(!visited[dest.first][dest.second][Teleport]) {
              visited[dest.first][dest.second][Teleport] = true;
              queue.push({dest, Teleport, 1});
            }
          }

          // Special case: start == end
          if(start == end) {
            min_moves = 0;
          } else {
            // --- SINGLE UNIFIED BFS LOOP ---
            while (!queue.empty()) {
              State state = queue.front(); queue.pop();
              pii curr_pos = state.pos;
              Move last_move = state.move;
              int curr_moves = state.moves;

              if(curr_pos == end) {
                min_moves = curr_moves;
                break; // Found the shortest path, can exit the loop
              }

              // --- Generate next moves based on last_move ---
                
              // Try Knight moves if last move wasn't Knight
              if(last_move != Knight) {
                vpii next_moves = makeKnightMoves(curr_pos, N, obstacles);
                for(const auto& dest : next_moves) {
                  if(!visited[dest.first][dest.second][Knight]) {
                    visited[dest.first][dest.second][Knight] = true;
                    queue.push({dest, Knight, curr_moves + 1});
                  }
                }
              }

              // Try Bishop moves if last move wasn't Bishop
              if(last_move != Bishop) {
                vpii next_moves = makeBishopMoves(curr_pos, N, obstacles);
                for(const auto& dest : next_moves) {
                  if(!visited[dest.first][dest.second][Bishop]) {
                    visited[dest.first][dest.second][Bishop] = true;
                    queue.push({dest, Bishop, curr_moves + 1});
                  }
                }
              }

              // Try Teleport moves if last move wasn't Teleport
              if(last_move != Teleport) {
                vpii next_moves = makeTeleportMoves(curr_pos, N, obstacles);
                for(const auto& dest : next_moves) {
                  if(!visited[dest.first][dest.second][Teleport]) {
                    visited[dest.first][dest.second][Teleport] = true;
                    queue.push({dest, Teleport, curr_moves + 1});
                  }
                }
              }
            }
          }

          std::cout << (min_moves == -1 ? "Solution doesn't exist" : "Result : " + std::to_string(min_moves)) << std::endl;
        }
    }
}