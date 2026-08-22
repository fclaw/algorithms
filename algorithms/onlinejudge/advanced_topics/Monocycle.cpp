/*
───────────────────────────────────────────────────────────────
🧳 UVa 10047 The Monocycle, https://onlinejudge.org/external/100/10047.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vvvvi = std::vector<vvvi>;

constexpr int inf = std::numeric_limits<int>::max();
constexpr int MAX_M = 25;
constexpr int MAX_N = 25;


// The 4 cardinal directions the monocycle can face.
// Turning left/right modifies this value by (+3) % 4 or (+1) % 4.
enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

// { {delta_row, delta_col}, Direction }
const std::unordered_map<Direction, ii> 
  dirs4 = {
    {NORTH, {-1,  0}}, // Row - 1 (Up)
    {EAST, { 0,  1}}, // Col + 1 (Right)
    {SOUTH, { 1,  0}}, // Row + 1 (Down)
    {WEST, { 0, -1}}  // Col - 1 (Left)
  };


// The 5 colors on the wheel rim. 
// Moving forward 1 square rotates the wheel to the next color: (colour + 1) % 5.
// Problem Rule: The monocycle starts with GREEN touching the ground
// and MUST end at the target with GREEN touching the ground.
enum Colour { GREEN = 0, BLACK = 1, RED = 2, BLUE = 3, WHITE = 4 };

struct State
{
    /**
     * 1. travel_tm (Time elapsed / Cost)
     * ----------------------------------
     * The total time (in seconds) taken to reach this exact state from the start.
     * Every action takes exactly 1 second:
     *   - Moving forward 1 block  -> +1 sec
     *   - Turning 90 degrees Left -> +1 sec
     *   - Turning 90 degrees Right-> +1 sec
     * This is the cost value we want to minimize (Dijkstra's g(n)).
     */
    int travel_tm;

    /**
     * 2. row & 3. col (Spatial Position)
     * -----------------------------------
     * The current (r, c) grid coordinates of the monocycle on the map.
     * Constraints: 
     *   - 0 <= row < R, 0 <= col < C
     *   - grid[row][col] != '#' (cannot move into obstacles)
     */
    int row;
    int col;

    /**
     * 4. direction (Facing Angle)
     * ---------------------------
     * The direction the cyclist is currently facing (NORTH, EAST, SOUTH, or WEST).
     * Necessary because:
     *   - If we "Move Forward", this dictates which neighbor cell (dr, dc) we enter.
     *   - A full 180-degree turn takes 2 seconds (two 90-degree turns).
     */
    Direction direction;

    /**
     * 5. colour (Wheel Rotation State)
     * --------------------------------
     * Which segment of the 5-color wheel is currently in contact with the ground.
     * Necessary because:
     *   - Reaching target (T_row, T_col) is NOT enough.
     *   - The cycle must finish with 'GREEN' touching the ground.
     *   - Visiting (row, col) with BLUE is fundamentally a different state than 
     *     visiting (row, col) with GREEN.
     */
    Colour colour;

    /**
     * Priority Queue Comparator (Min-Heap)
     * ------------------------------------
     * C++ `std::priority_queue` is a MAX-HEAP by default (pops the largest element).
     * By inverting the operator using `travel_tm > other.travel_tm`, we convert 
     * it into a MIN-HEAP so Dijkstra always processes the state with the 
     * SMALLEST elapsed time first.
     */
    bool operator < (const State& other) const { 
      return travel_tm > other.travel_tm; 
    }
};

struct Move 
{
    int row;
    int col;
    Direction dir;
    Colour colour;
};


int N, M;

bool in_grid(int r, int c) { return r >= 0 && r < N && c >= 0 && c < M; }

std::string get_min_time_required(const vi& grid, ii start, ii end) {

  int min_time_required = inf;
  vvvvi time(MAX_M + 1, vvvi(MAX_N + 1, vvi(4, vi(5, inf))));
  std::priority_queue<State> queue;

  State init = {0, start.first, start.second, NORTH, GREEN };
  time[start.first][start.second][NORTH][GREEN] = 0;
  queue.push(init);
   
  while(!queue.empty()) {
    
    State state = queue.top(); queue.pop();
    int r = state.row;
    int c = state.col;
    Direction dir = state.direction;
    Colour colour = state.colour;
    int time_so_far = state.travel_tm;

    if(r == end.first && 
       c == end.second && 
       colour == GREEN) {  
      min_time_required = time_so_far;
      break;
    }

    // pruning
    if(time_so_far > time[r][c][dir][colour]) {
      continue;
    }

    Colour next_col = static_cast<Colour>((colour + 1) % 5); 
    std::vector<Move> moves;

    // 1. TURN RIGHT (+1 clockwise)
    Direction right_dir = static_cast<Direction>((dir + 1) % 4);
    moves.push_back({r, c, right_dir, colour});

    // 2. TURN LEFT (-1 counter-clockwise -> +3 mod 4)
    Direction left_dir = static_cast<Direction>((dir + 3) % 4);
    moves.push_back({r, c, left_dir, colour});

    // 3. MOVE FORWARD
    int nr = r + dirs4.at(dir).first;
    int nc = c + dirs4.at(dir).second;
    if(in_grid(nr, nc)) {
      moves.push_back({nr, nc, dir, next_col});
    }

    for(Move move : moves) {
      int& next_time_so_far = time[move.row][move.col][move.dir][move.colour];
      if(!(grid[move.row] & (1 << move.col)) &&
         1 + time_so_far < next_time_so_far) {
        int travel_tm = 1 + time_so_far;
        next_time_so_far = travel_tm;
        queue.push({next_time_so_far, move.row, move.col, move.dir, move.colour});
      }
    }
  }

  std::string ans;
  if(min_time_required == inf) {
    ans = "destination not reachable";
  } else {
    ans = "minimum time = " + std::to_string(min_time_required) + " sec";
  }
  return ans;
}

namespace algorithms::onlinejudge::advanced_topics::monocycle
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

        
        int t_case = 1;
        bool is_first_case = true;
        while(std::cin >> N >> M && N && M) {

          if(is_first_case) {
            is_first_case = false;
          } else {
            std::cout << std::endl;
          }


          vi grid(N);
          char cell;
          ii start, end;
          for(int r = 0; r < N; ++r) {
            int row = 0;
            for(int c = 0; c < M; ++c) {
              std::cin >> cell;
              if(cell == 'S') {
                start = {r, c};
              } else if (cell == 'T') {
                end = {r, c};
              } else {
                if(cell == '#') { // obstacle
                  row |= (1 << c);
                }
              }
            }
            grid[r] = row;
          }

          printf("Case #%d\n%s\n", t_case++, get_min_time_required(grid, start, end).c_str());
        }
    }
}