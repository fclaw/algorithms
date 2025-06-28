/*
───────────────────────────────────────────────────────────────
🧳 UVa 439 Knight Moves, rt: s
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



constexpr int SIZE = 8;
constexpr int MOVES = 8;

const int dx[MOVES] = { -2, -1, 1, 2,  2,  1, -1, -2 };
const int dy[MOVES] = {  1,  2, 2, 1, -1, -2, -2, -1 };

const std::unordered_map<char, int> board_layout = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};

bool board[SIZE][SIZE];

struct State
{
    int r;
    int c;
    int moves;
};

 bool in_bounds(int r, int c) { return r >= 0 && r < SIZE && c >= 0 && c < SIZE; }

namespace algorithms::onlinejudge::graph::knight_moves
{
    /** https://onlinejudge.org/external/4/439.pdf */
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
        
        std::string from, to;
        while(while_read(from, to)) {
          std::memset(board, false, sizeof board);
          int source_r = board_layout.at(from[0]);
          int source_c = (from[1] - '0') - 1;
          int sink_r = board_layout.at(to[0]);
          int sink_c = (to[1] - '0') - 1;
          board[source_r][source_c] = true;
          std::queue<State> queue;
          queue.push({source_r, source_c, 0});
          int min_moves = 0;
          while(!queue.empty()) {
            State state = queue.front(); queue.pop();
            if(state.r == sink_r && state.c == sink_c)
            { min_moves = state.moves; break; }
            for(int m = 0; m < MOVES; ++m) {
              int nr = state.r + dx[m];
              int nc = state.c + dy[m];
              if(in_bounds(nr, nc) && !board[nr][nc]) {
                board[nr][nc] = true;
                queue.push({nr, nc, state.moves + 1});
              }
            }
          }
          printf("To get from %s to %s takes %d knight moves.\n", from.c_str(), to.c_str(), min_moves);
        }
    }
}