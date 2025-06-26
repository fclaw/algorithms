/*
───────────────────────────────────────────────────────────────
🧳 UVa 314 Robot, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "tools/bfs.cpp"

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
#include <unordered_set>
#include <queue>


// For 4-directional movement (up, right, down, left)
const std::vector<std::pair<int, int>> dirs_4 = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };


enum Direction { North, East, South, West, None };

struct State 
{
    std::pair<int, int> pos;
    Direction d;
    int time;
};


constexpr int MAX = 51;
constexpr int D = 4;

bool visited[MAX][MAX][D];
bool obstacle[MAX][MAX];


Direction read(const std::string& s)
{
    if(s == "west") return West;
    if(s == "east") return East;
    if(s == "north") return North;
    if(s == "south") return South;
    return None;
}

enum Rotate { Right, Left };

Direction rotateLeft(Direction d) { return  static_cast<Direction>((d + 1) % 4); }
Direction rotateRight(Direction d) { return static_cast<Direction>((d + 3) % 4); } // same as (d - 1 + 4) % 4

Direction rotate(Rotate r, Direction d)
{
    if(r == Left) return rotateLeft(d);
    else return rotateRight(d);
}

std::pair<int, int> dirToDelta(Direction d) 
{
    switch (d) {
        case North: return {-1, 0};
        case South: return {1, 0};
        case West:  return {0, -1};
        case East:  return {0, 1};
        default:    return {0, 0}; // None or invalid
    }
}

std::pair<int, int> moveForward(const std::pair<int, int>& pos, Direction d, int steps) {
    auto diff = dirToDelta(d);
    int dr = diff.first;
    int dc = diff.second;
    std::pair<int, int> newPos = {
        pos.first + steps * dr,
        pos.second + steps * dc
    };
    return newPos;
}

bool isFree(int x, int y) 
{
    return !obstacle[x - 1][y - 1] &&
           !obstacle[x - 1][y] &&
           !obstacle[x][y - 1] &&
           !obstacle[x][y];
}

namespace algorithms::onlinejudge::graph::robot
{
    /** https://onlinejudge.org/external/3/314.pdf */
    int R, C;
    bool in_bounds(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }
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
         
        while(while_read(R, C) && R && C) {
          std::memset(obstacle, false, sizeof obstacle);
          std::memset(visited, false, sizeof visited);
          loop(R, [&](int r) {
            loop(C, [&](int c) {
              while_read(obstacle[r][c]);
             });
          });

          int source_r, source_c, sink_r, sink_c;
          std::string d_s;
          while_read(source_r, source_c, sink_r, sink_c, d_s);
          Direction d = read(d_s);
          
          bool is_valid = true;
          if(!isFree(source_r, source_c)) is_valid = false;

          std::queue<State> queue;
          queue.push({{source_r, source_c}, d, 0});
          int min_time = -1;
          while(!queue.empty() && is_valid) {
            State s = queue.front(); queue.pop();
            int r = s.pos.first;
            int c = s.pos.second;
            Direction d = s.d;
            if(r == sink_r && c == sink_c) 
            {  min_time = s.time; break; };
            visited[r][c][d] = true;
            for(int j = 0; j <= 1; ++j) {
              Rotate rt = static_cast<Rotate>(j);
              Direction nd = rotate(rt, d);
              if(!visited[r][c][nd]) {
                visited[r][c][nd] = true;
                queue.push({{r, c}, nd, s.time + 1});
              }
            }

            for(int step = 1; step <= 3; ++step) {
              auto new_pos = moveForward(s.pos, d, step);
              if(in_bounds(new_pos.first, new_pos.second) &&
                 isFree(new_pos.first, new_pos.second)) {
                if(!visited[new_pos.first][new_pos.second][d]) {          
                  visited[new_pos.first][new_pos.second][d] = true;
                  queue.push({new_pos, d, s.time + 1});
                }
               } else break;
            }
          }
          std::cout << min_time << std::endl;
        }
    }
}