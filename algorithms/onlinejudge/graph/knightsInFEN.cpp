/*
───────────────────────────────────────────────────────────────
🧳 UVa 10422 Knights in FEN, rt: s
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
#include <cctype>


constexpr int SIZE = 5;
constexpr int MOVES = 8;
constexpr int THRESHOLD = 11;

typedef std::pair<int, int> pii;

enum Cell
{
    White,
    Black,
    Blank
};


Cell touchstone[SIZE * SIZE] = 
  {Black, Black, Black, Black, Black, // level 1
   White, Black, Black, Black, Black, // level 2
   White, White, Blank, Black, Black, // level 3
   White, White, White, White, Black, // level 4
   White, White, White, White, White
  };

void swap(const pii& pos_k, const pii& pos_b, uint64_t& board)
{
    int idx_k = pos_k.first * SIZE + pos_k.second;
    int idx_b = pos_b.first * SIZE + pos_b.second;

    int shift_k = 2 * idx_k;
    int shift_b = 2 * idx_b;

    // Extract 2-bit values
    uint64_t val_k = (board >> shift_k) & 0b11;
    uint64_t val_b = (board >> shift_b) & 0b11;

    // Clear both positions
    board &= ~(0b11ULL << shift_k);
    board &= ~(0b11ULL << shift_b);

    // Swap values
    board |= (val_b << shift_k);
    board |= (val_k << shift_b);
}

uint64_t encode_board(Cell board[SIZE * SIZE]) {
    uint64_t code = 0;
    for (int i = 0; i < SIZE * SIZE; ++i)
      code |= ((uint64_t)board[i] << (2 * i));
    return code;
}

struct State
{
    pii blank_pos;
    int steps;
    uint64_t footprint;
};

const int dx[MOVES] = { -2, -1, 1, 2,  2,  1, -1, -2 };
const int dy[MOVES] = {  1,  2, 2, 1, -1, -2, -2, -1 };


namespace algorithms::onlinejudge::graph::knights_in_fen
{
    /** https://onlinejudge.org/external/104/10422.pdf */
    int t_cases;
    bool in_board(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; }
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

        uint64_t encoded_touchstone = encode_board(touchstone);  
        while_read(t_cases);
        std::cin.ignore();
        Cell init_board[SIZE * SIZE];
        std::memset(init_board, White, sizeof init_board);
        pii blank_pos = {-1, -1};  // To store blank position
        while(t_cases--) {
          std::string s;
          for(int r = 0; r < SIZE; ++r) {
            std::getline(std::cin, s);
            for(int c = 0; c < SIZE; ++c) {
              int idx = r * SIZE + c;  
              if(std::isdigit(s[c])) {
                int v = s[c] - '0';
                Cell cell = static_cast<Cell>(v);
                init_board[idx] = cell;
              } else if(std::isspace(s[c])) {
                init_board[idx] = Blank;
                blank_pos = {r, c};
              }
            }
          }  

          std::unordered_set<uint64_t> visited;
          std::queue<State> queue;

          int min_steps = -1;
          uint64_t encoded_init = encode_board(init_board);
          visited.insert(encoded_init);
          queue.push({blank_pos, 0, encoded_init});
          while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            pii blank_pos = state.blank_pos;
            int steps = state.steps;
            uint64_t fp = state.footprint;
            if(steps >= THRESHOLD) {
              break;
            }
            if(fp == encoded_touchstone) {
              min_steps = steps; break; 
            }
            for(int m = 0; m < MOVES; ++m) {
              int nr = blank_pos.first + dx[m];
              int nc = blank_pos.second + dy[m];
              if(in_board(nr, nc)) {
                uint64_t tmp_fp = fp;
                swap({nr, nc}, blank_pos, tmp_fp);
                if(!visited.count(tmp_fp)) {
                  visited.insert(tmp_fp);
                  queue.push({{nr, nc}, steps + 1, tmp_fp});
                }
              }
            }
          }
          min_steps == -1 ? printf("Unsolvable in less than %d move(s).\n", THRESHOLD) : printf("Solvable in %d move(s).\n", min_steps);
        }
    }
}