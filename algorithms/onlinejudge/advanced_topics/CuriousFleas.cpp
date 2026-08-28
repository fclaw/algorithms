/*
───────────────────────────────────────────────────────────────
🧳 UVa 11329 Curious Fleas, https://onlinejudge.org/external/113/11329.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ii = std::pair<int, int>;


constexpr int SIZE = 4;
constexpr int SIDE = 6;
constexpr int SIDE_SIZE = 4;


enum FaceIndex {
    TOP    = 0,
    NORTH  = 1, // UP
    BOTTOM = 2,
    SOUTH  = 3, // DOWN
    EAST   = 4, // RIGHT
    WEST   = 5  // LEFT
};

// 1. Physical Face Identity
enum Dots : uint8_t { ONE = 0, TWO = 1, THREE = 2, FOUR = 3, FIVE = 4, SIX = 5 };

struct Side 
{
    Dots dots;      // Which physical face is in this slot (0..5 -> 3 bits)
    bool has_flea;  // Whether this face carries a flea (0..1 -> 1 bit)
};

using Die = std::array<Side, 6>;

struct State
{
    int row;  // 0..3 (2 bits)
    int col;  // 0..3 (2 bits)

    // Stack-allocated array of 6 sides: [TOP, BOTTOM, NORTH, SOUTH, EAST, WEST]
    Die die;

    int board; // 4x4 bitmask of fleas on the board (16 bits)

    // moves
    int moves;
};

// Packs entire state into a single uint64_t for O(1) visited checks
inline uint64_t pack(const State& s) {
  uint64_t res = 0;

  // 1. Position (4 bits)
  res |= (static_cast<uint64_t>(s.row * SIZE + s.col) & 0xF);

  // 2. Board mask (16 bits)
  res |= (static_cast<uint64_t>(s.board & 0xFFFF) << SIZE);

  // 3. Die (6 sides * 4 bits = 24 bits)
  for (int i = 0; i < SIDE; ++i) {
    uint64_t side_bits = 
      (static_cast<uint64_t>(s.die[i].dots) & 0x7) | 
      (static_cast<uint64_t>(s.die[i].has_flea) << 3);
    res |= (side_bits << (20 + i * SIDE_SIZE));
  }

  return res; // Total: only 44 bits!
}


void exchange_flea(Die& die, int r, int c, int& board) {
  int cell_bit = 1 << (r * 4 + c);
  bool board_has_flea = (board & cell_bit) != 0;
  bool die_has_flea   = die[BOTTOM].has_flea;

  if(!die_has_flea && board_has_flea) {
    // 1. Flea jumps from BOARD onto DIE
    die[BOTTOM].has_flea = true;
    board &= ~cell_bit; // Clear flea from board
  } else if (die_has_flea && !board_has_flea) {
    // 2. Flea drops from DIE onto BOARD
    die[BOTTOM].has_flea = false;
    board |= cell_bit;  // Add flea to board
  }
}

void roll_up(Die& die, int r, int c, int& board) {
    Side old_top    = die[TOP];
    Side old_north  = die[NORTH];
    Side old_bottom = die[BOTTOM];
    Side old_south  = die[SOUTH];

    die[TOP]    = old_south;
    die[NORTH]  = old_top;
    die[BOTTOM] = old_north;
    die[SOUTH]  = old_bottom;

    // Flea interaction on new bottom face
    exchange_flea(die, r, c, board);
}

void roll_down(Die& die, int r, int c, int& board) {
    Side old_top    = die[TOP];
    Side old_north  = die[NORTH];
    Side old_bottom = die[BOTTOM];
    Side old_south  = die[SOUTH];

    die[TOP]    = old_north;
    die[NORTH]  = old_bottom;
    die[BOTTOM] = old_south;
    die[SOUTH]  = old_top;

    // Flea interaction on new bottom face
    exchange_flea(die, r, c, board);
}

void roll_right(Die& die, int r, int c, int& board) {
    Side old_top    = die[TOP];
    Side old_bottom = die[BOTTOM];
    Side old_east   = die[EAST];
    Side old_west   = die[WEST];

    die[TOP]    = old_west;
    die[BOTTOM] = old_east;
    die[EAST]   = old_top;
    die[WEST]   = old_bottom;

    // Flea interaction on new bottom face
    exchange_flea(die, r, c, board);
}

void roll_left(Die& die, int r, int c, int& board) {
    Side old_top    = die[TOP];
    Side old_bottom = die[BOTTOM];
    Side old_east   = die[EAST];
    Side old_west   = die[WEST];

    die[TOP]    = old_east;
    die[BOTTOM] = old_west;
    die[EAST]   = old_bottom;
    die[WEST]   = old_top;

    // Flea interaction on new bottom face
    exchange_flea(die, r, c, board);
}

// 0: Up (North), 1: Right (East), 2: Down (South), 3: Left (West)
void roll(Die& die, int dir, int r, int c, int& board) {
    switch (dir) {
        case 0: roll_up(die, r, c, board); break;
        case 1: roll_right(die, r, c, board); break;
        case 2: roll_down(die, r, c, board); break;
        case 3: roll_left(die, r, c, board); break;
    }
}

// Index:        0 (UP)   1 (RIGHT)  2 (DOWN)   3 (LEFT)
const int dr[] = { -1,       0,        1,         0   };
const int dc[] = {  0,       1,        0,        -1   };

bool in_board(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; };


std::string get_min_moves(int board, const ii& die_pos) {

  std::queue<State> queue;
  std::unordered_set<uint64_t> visited;
  
  // init
  Die die = {{
        {ONE, false}, 
        {THREE, false}, 
        {FOUR, false}, 
        {SIX, false}, 
        {TWO, false}, 
        {FIVE, false}
      }};
  State init = {die_pos.first, die_pos.second, die, board, 0};
  queue.push(init);
  visited.insert(pack(init));  

  int min_moves = -1;

  while(!queue.empty()) {
    State state = queue.front(); queue.pop();
    int row = state.row;
    int col = state.col;
    Die die = state.die;
    int board = state.board;
    int moves = state.moves;

    // all fleas are on the sides
    if(!__builtin_popcount(board)) {
      min_moves = moves;
      break;
    }

    for(int dir = 0; dir <= 3; ++dir) {
      int nr = row + dr[dir];
      int nc = col + dc[dir];
      if(in_board(nr, nc)) {
        int new_board = board;
        Die new_die = die;
        roll(new_die, dir, nr, nc, new_board);
        State new_state = {nr, nc, new_die, new_board, 1 + moves};
        uint64_t key = pack(new_state);
        if(!visited.count(key)) {
          visited.insert(key);
          queue.push(new_state);
        } 
      }
    }
     
  }

  return min_moves == -1 ? "impossible" : std::to_string(min_moves);

}



namespace algorithms::onlinejudge::advanced_topics::curious_fleas
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
        std::cin >> t_cases;
        while(t_cases--) {
          int board = 0;
          ii die_pos;
          char cell;
          for(int r = 0; r < SIZE; ++r) {
            for(int c = 0; c < SIZE; ++c) {
              std::cin >> cell;
              if (cell == 'X') {
                int bit = r * SIZE + c;
                board |= (1 << bit);
              } else if (cell == 'D') {
                die_pos.first = r;
                die_pos.second = c;
              }
            }
          }
          printf("%s\n", get_min_moves(board, die_pos).c_str());
        }
    }
}