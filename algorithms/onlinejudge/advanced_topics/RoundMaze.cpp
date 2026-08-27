/*
───────────────────────────────────────────────────────────────
🧳 UVa 985 Round and Round Maze, https://onlinejudge.org/external/9/985.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using vvvb = std::vector<vvb>;


constexpr int DIR = 4;

// Clockwise Direction Enum: 0: North, 1: East, 2: South, 3: West
// Rotating clockwise by 90 degrees is simply: (d + 1) % 4
enum Dir { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

using v_dir = std::vector<Dir>;
using vv_dir = std::vector<v_dir>;
using Maze = std::vector<vv_dir>;

// { {delta_row, delta_col}, Direction }
const std::unordered_map<Dir, ii>
  dirs4 = {
    {NORTH, {-1,  0}}, // Row - 1 (Up)
    {EAST, { 0,  1}}, // Col + 1 (Right)
    {SOUTH, { 1,  0}}, // Row + 1 (Down)
    {WEST, { 0, -1}}  // Col - 1 (Left)
  };


struct State 
{
    /**
     * 1. row & 2. col (Spatial Position)
     * -----------------------------------
     * Current square coordinates on the R x C maze grid.
     * Start: (0, 0), Exit: (R - 1, C - 1).
     */
    int row;
    int col;

    /**
     * 3. time (Elapsed Time in Seconds)
     * ---------------------------------
     * Total seconds elapsed from start (0, 0).
     * Since each step takes 1 time unit, 'time' is also the distance g(n).
     * 
     * The rotation phase of all maze plates at this moment is:
     *   phase = time % 4;
     */
    int time;
};

int R, C;


bool in_maze(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; };


std::string get_min_time_required(const Maze& maze) {

  std::queue<State> queue;
  vvvb visited(R, vvb(C, vb(DIR, false)));
  // init
  queue.push({0, 0, 0});
  const ii target = {R - 1, C - 1};

  int min_time_required = INT32_MAX;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int row = state.row;
    int col = state.col;
    int time_elapsed = state.time;

    if(row == target.first && 
       col == target.second) {
      min_time_required = time_elapsed;
      break;
    }

    for(Dir d : maze[row][col]) {
      d = static_cast<Dir>((d + time_elapsed) % DIR);
      int next_row = row + dirs4.at(d).first;
      int next_col = col + dirs4.at(d).second;
      if(in_maze(next_row, next_col)) {
        int new_time = 1 + time_elapsed;
        int next_phase = new_time % DIR; // (0, 1, 2, or 3)
        if(!visited[next_row][next_col][next_phase]) {
          visited[next_row][next_col][next_phase] = true;
          queue.push({next_row, next_col, new_time});
        }
      }
    }
  }

  return min_time_required == INT32_MAX ? "no path to exit" : std::to_string(min_time_required);
}


namespace algorithms::onlinejudge::advanced_topics::round_maze
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

        while(std::cin >> R >> C) {
          Maze maze(R, vv_dir(C));
          std::string cell;
          for(int idx = 0; idx < R * C - 1; ++idx) {
            int r = idx / C;
            int c = idx % C;
            std::cin >> cell;
            v_dir dirs;
            for(char d : cell) {
              if(d == 'N') {
                dirs.push_back(NORTH);
              } else if (d == 'E') {
                dirs.push_back(EAST);
              } else if (d == 'S') {
                dirs.push_back(SOUTH);
              } else {
                dirs.push_back(WEST);
              }
            }
            maze[r][c] = dirs;
          }
          printf("%s\n", get_min_time_required(maze).c_str());
        }
    }
}